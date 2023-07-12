#include <iostream>

#include "Uart.hpp"

#include <pthread.h>

#include <sys/time.h> 
#include <unistd.h>

using namespace std;

// 读串口线程
pthread_t id_Read;
void* thread_Read(void *arg);

// 写串口线程
pthread_t id_Write;
void* thread_Write(void *arg);

// 串口结构体
Uart uart;

int main()
{
    // uart初始化
    uart.InitSerialPort("/dev/ttyUSB0");

    // 开启读串口和写串口两个线程
    pthread_create(&id_Read, NULL, thread_Read, NULL);
    pthread_create(&id_Write, NULL, thread_Write, NULL);

    while(1)
    {

    }

    return 0;
}

// 读串口线程
void* thread_Read(void *arg)
{
    bool isAlign = false; // 获取到的串口信息是否对齐

    while(1)
    {
        // 如果获取到的串口信息没对齐，则一直堵塞直到对齐
        while(!isAlign)
        {
            printf("The Message Is Wrong. ");
            isAlign = uart.Align();
        }

        // 堵塞读取串口
        uart.ReadBuffer();

        uart.ShowReadBuff();

        // 判断头帧和尾帧是否正确
        if(!uart.IsRightData())
        {
            cout << "Wrong Message!" << endl;
            uart.ShowReadBuff();
            isAlign = false;
            continue;
        }

        if(uart.Oder() == 'S')
        {
            uint8_t flag1=0, flag2=0;
            uint16_t X=0, Y=0;
            flag1 = uart.readBuff[3], flag2 = uart.readBuff[8];
            memcpy(&X, &uart.readBuff[4], 2);
            memcpy(&Y, &uart.readBuff[6], 2);

            printf("receive flag1 %d X %d Y %d flag2 %d\n", flag1, X, Y, flag2);

        }
    }
}

// 写串口线程
void* thread_Write(void *arg)
{
    while(1)
    {
        memset(uart.writeBuff, 0, sizeof(uart.writeBuff));

        uart.writeBuff[0] = '?';
        uart.writeBuff[1] = '!';
        uart.writeBuff[2] = 'S';
        uart.writeBuff[uart_length-1] = '!';

        uint8_t flag1 = 2;
        uint16_t X = 3000;
        uint16_t Y = 2500;
        uint8_t flag2 = 3;

        uart.writeBuff[3] = flag1;
        memcpy(&uart.writeBuff[4], &X, 2);
        memcpy(&uart.writeBuff[6], &Y, 2);
        uart.writeBuff[8] = flag2;

        // 写入串口
        uart.WriteBuffer();
        uart.ShowWriteBuff();

        // 休眠100ms
        usleep(100000);
    }
}