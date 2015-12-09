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
    SCON = 0x50;                //8λ�ɱ䲨����
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif

    T2L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����

    ES = 1;                     //ʹ�ܴ���1�ж�
    EA = 1;
}

/*----------------------------
UART �жϷ������
-----------------------------*/
//void Uart() interrupt 4 using 1
//{
//    //if (RI)  //------���ò�ѯ��ʽ�����մ�������
//    //{
//    //    //RI = 0;                 //���RIλ
//    //    //P0 = SBUF;              //P0��ʾ��������
//    //    //P22 = RB8;              //P2.2��ʾУ��λ
//    //}
//	
//    if (TI)
//    {
//        TI = 0;                 //���TIλ
//        busy = 0;               //��æ��־
//    }
//}

char serial_ReciveData()
{
	while ( ~RI );
	RI=0;
	return SBUF;
}


/*----------------------------
���ʹ�������
----------------------------*/
void serial_SendData(char dat)
{
    ACC = dat;                  //��ȡУ��λP (PSW.0)
    SBUF = ACC;                 //д���ݵ�UART���ݼĴ���
	while (~TI);               	//�ȴ����ݷ������
	TI = 0;                 	//���TIλ
}

/*----------------------------
�����ַ���
----------------------------*/
void serial_SendString(char *s)
{
    while (*s)                  //����ַ���������־
    {
        serial_SendData(*s++);         //���͵�ǰ�ַ�
    }
}