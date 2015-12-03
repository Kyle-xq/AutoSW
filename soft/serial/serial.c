#include "serial.h"

void serial_init (){
	ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)
    
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
//  ACC |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
//  P_SW1 = ACC;  
//  
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
//  ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
//  P_SW1 = ACC;  


    SCON = 0x50;                //8位可变波特率 


    AUXR = 0x40;                //定时器1为1T模式
    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
    TL1 = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    TH1 = (65536 - (FOSC/4/BAUD))>>8;
    TR1 = 1;                    //定时器1开始启动
    ES = 1;                     //使能串口中断
    EA = 1;
}

/*----------------------------
UART 中断服务程序
-----------------------------*/
//void Uart() interrupt 4 using 1
//{
//    //if (RI)  //------采用查询方式，接收串口数据
//    //{
//    //    //RI = 0;                 //清除RI位
//    //    //P0 = SBUF;              //P0显示串口数据
//    //    //P22 = RB8;              //P2.2显示校验位
//    //}
//	
//    if (TI)
//    {
//        TI = 0;                 //清除TI位
//        busy = 0;               //清忙标志
//    }
//}


/*----------------------------
发送串口数据
----------------------------*/
void serial_SendData(BYTE dat)
{
    ACC = dat;                  //获取校验位P (PSW.0)
    SBUF = ACC;                 //写数据到UART数据寄存器
	while (~TI);               	//等待数据发送完成
	TI = 0;                 	//清除TI位
}

/*----------------------------
发送字符串
----------------------------*/
void serial_SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData(*s++);         //发送当前字符
    }
}