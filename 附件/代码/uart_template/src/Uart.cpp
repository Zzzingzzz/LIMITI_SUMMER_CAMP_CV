#include "Uart.hpp"

/**
 * 串口初始化
 * @param dev 打开串口名称
 */
void Uart::InitSerialPort(std::string dev)
{
    printf("SerialPort Connecting ..\n");

    OpenPort(dev);

    int speed = 115200;
    int flow_ctrl = 0;
    int databits = 8;
    int stopbits = 1;
    SetUp(speed, flow_ctrl, databits, stopbits);
}

// 读串口
int Uart::ReadBuffer()
{
    memset(readBuff, 0, sizeof(readBuff));
    return read(fd, &readBuff, uart_length);
}

// 写串口
int Uart::WriteBuffer()
{
    return write(fd, &writeBuff, uart_length);
}

// 打印读到的串口
void Uart::ShowReadBuff()
{
    for(size_t i=0; i<uart_length; i++)
        printf("%x ", readBuff[i]);
    printf("\n");
}

// 打印写的串口
void Uart::ShowWriteBuff()
{
    for(size_t i=0; i<uart_length; i++)
        printf("%x ", writeBuff[i]);
    printf("\n");
}

/**
 * 对齐数据位
 * @return 是否对齐
 */
bool Uart::Align()
{
    int tmp_length = 1;
    uint8_t temp[100];

    ReadBuffer();
    while(readBuff[0] != '?' || readBuff[1] != '!' || readBuff[uart_length-1] != '!')
    {
        printf("Not Align!\n");
        ShowReadBuff();

        read(fd, &temp, tmp_length++);
        ReadBuffer();

        if(tmp_length >= 99) tmp_length = 1;
    }

    ReadBuffer();
    ShowReadBuff();

    if(readBuff[0] != '?')
    {
        printf("Wrong Head First!\n");
        return false;
    }

    if(readBuff[1] != '!')
    {
        printf("Wrong Head Second!\n");
        return false;
    }

    if(readBuff[uart_length-1] != '!')
    {
        printf("Wrong Tail!\n");
        return false;
    }

    return true;
}

/**
 * 获取命令位
 * @return 命令位
 */
uint8_t Uart::Oder()
{
    return readBuff[2];
}

/**
 * 检验读到的数据是否正确
 * @return 读到的数据是否正确
 */
bool Uart::IsRightData()
{
    if(readBuff[0] != '?' || readBuff[1] != '!' || readBuff[uart_length-1] != '!') return false; 
    return true;
}

void Uart::OpenPort(std::string dev)
{
    const char* _dev = new char[32];
    _dev = dev.c_str();

    fd = open(_dev,O_RDWR|O_NDELAY); //读写打开、使I/O变成非搁置模式
    if(fd == -1){
          printf("connect fail!\n");
          perror("Can't Open Serial Port");
          return ;
    }

    //判断串口的状态是否为阻塞状态 
    //fcntl()针对(文件)描述符提供控制.参数fd是被参数cmd操作，这里的参数指“设置文件状态标记“
    if(fcntl(fd, F_SETFL, 0) == -1 ){ //<0
		perror("fcntl failed!");
        return ;
    } else {
        printf("serial is available.\n");
    }

    int DTR_flag;
    DTR_flag = TIOCM_DTR; //TIOCM_DTR表示终端设备已经准备好
    ioctl(fd,TIOCMBIS,&DTR_flag);//Set RTS pin
    return ;
}

void Uart::SetUp(int speed, int flow_ctrl, int databits, int stopbits)
{
    struct termios options; 
    /*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options，
    该函数还可以测试配置是否正确，该串口是否可用等。
    若调用成功，函数返回值为0，若调用失败，函数返回值为1。
    */
    if(tcgetattr(fd, &options)){ 
        perror("SetupSerial error 1 "); 
        return ; 
    }

    //设置串口输入波特率和输出波特率  
	for(size_t i = 0; i < sizeof(speed_arr) / sizeof(int); i++)  {  
		if(speed == name_arr[i]){               
			cfsetispeed(&options, speed_arr[i]);   
			cfsetospeed(&options, speed_arr[i]);    
		}  
	}

    //修改控制模式，保证程序不会占用串口  
    options.c_cflag |= CLOCAL;  
    //修改控制模式，使得能够从串口中读取输入数据  
    options.c_cflag |= CREAD; 

    //设置数据流控制  
    switch(flow_ctrl){  
		case 0 ://不使用流控制  
            options.c_cflag &= ~CRTSCTS;  //默认
            break;     
		case 1 ://使用硬件流控制  
            options.c_cflag |= CRTSCTS;  
            break;  
		case 2 ://使用软件流控制  
            options.c_cflag |= IXON | IXOFF | IXANY;  
            break;  
    }

    //使用数据位掩码清空数据位设置 
    options.c_cflag &= ~CSIZE;
    //设置数据位    
    switch (databits){    
		case 5:  
            options.c_cflag |= CS5;  
            break;  
		case 6:  
            options.c_cflag |= CS6;  
            break;  
		case 7:      
            options.c_cflag |= CS7;  
            break;  
		case 8:      
            options.c_cflag |= CS8;  //默认
            break;    
		default:     
            fprintf(stderr,"Unsupported data size\n");  
            return ;   
    }

    // 设置停止位   
    switch(stopbits){    
		case 1:     
            options.c_cflag &= ~CSTOPB; break; //默认
		case 2:     
            options.c_cflag |= CSTOPB; break;
		default:     
            fprintf(stderr,"Unsupported stop bits\n");
            return ;
    } 

    //修改输出模式，原始数据输出
    options.c_oflag &= ~OPOST;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    //设置等待时间和最小接收字符  
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */    
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */  
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
    tcflush(fd,TCIFLUSH);

    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(fd,TCSANOW,&options) != 0) {
        perror("serial parameter set error!"); 
        return ; 
    }
    return ; 
}