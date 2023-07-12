#ifndef UART_HPP
#define UART_HPP

#include <stdio.h>      /*标准输入输出定义*/
#include <stdlib.h>     /*标准函数库定义*/
#include <unistd.h>     /*Unix 标准函数定义*/
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>      /*文件控制定义*/
#include <sys/termios.h>    /*PPSIX 终端控制定义*/
#include <errno.h>      /*错误号定义*/
#include <stdint.h>

#include <string>
#include <cstring>
#include <sys/ioctl.h>

#define uart_length 10

class Uart
{
private:

int fd = -1; //串口编号
int speed_arr[2] = {B1000000, B115200}; // 波特率
int name_arr[2] = {1000000, 115200};    // 波特率

/**
 * 打开串口并返回串口设备文件描述
 * @param dev 打开串口名称
 */
void OpenPort(std::string dev);

/**
 * 设置串口
 * @param speed 波特率
 * @param flow_ctrl 数据流控制方式
 * @param databits 数据位
 * @param stopbits 停止位
 */
void SetUp(int speed, int flow_ctrl, int databits, int stopbits);

public:

uint8_t writeBuff[uart_length]; // 写串口缓冲区
uint8_t readBuff[uart_length];  // 读串口缓冲区

/**
 * 串口初始化
 * @param dev 打开串口名称
 */
void InitSerialPort(std::string dev);

/**
 * 读串口
 */
int ReadBuffer();

/**
 * 写串口
 */
int WriteBuffer();

/**
 * 打印读到的串口
 */
void ShowReadBuff();

/**
 * 打印写的串口
 */
void ShowWriteBuff();

/**
 * 对齐数据位
 * @return 是否对齐
 */
bool Align();

/**
 * 获取命令位
 * @return 命令位
 */
uint8_t Oder();

/**
 * 检验读到的数据是否正确
 * @return 读到的数据是否正确
 */
bool IsRightData();
};

#endif