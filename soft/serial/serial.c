#include "../proj/src/sys.h"
#include "STC15.H"
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

#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9位可变波特率,校验位初始为0
#endif

    T2L = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器

    ES = 1;                     //使能串口1中断
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

char serial_ReciveData()
{
	while ( ~RI );
	RI=0;
	return SBUF;
}


/*----------------------------
发送串口数据
----------------------------*/
void serial_SendData(char dat)
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
        serial_SendData(*s++);         //发送当前字符
    }
}