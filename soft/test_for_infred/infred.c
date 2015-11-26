#include "reg51.h"
#include "infred.h"

void infred_init (void )
{
	//开启总中断
	//IE |= 0x80 ;
	//定义输出管脚
	ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=0 CCP_S1=0
    P_SW1 = ACC;                    //(P1.2/ECI, P1.1/CCP0, P1.0/CCP1, P3.7/CCP2)
	//
	CCON = 0;                       //初始化PCA控制寄存器
                                    //PCA定时器停止
                                    //清除CF标志
                                    //清除模块中断标志
	
    CMOD = 0x08;                    //设置PCA时钟源 SYS_CLK
                                    //禁止PCA定时器溢出中断
	//PCA_PWM0 = 0x00;                //PCA模块0工作于8位PWM
    //CCAP0H = CCAP0L = 0x80;         //PWM0的占空比 ((100H-80H)/100H)
	
    CCAPM0 = 0x4C;                  //PCA模块0为16位高速脉冲模式
	//CCAP0L = 0x07;					//设置38KHz Fclk20Mhz/2/38Khz = 267 = 0x107
	//CCAP0H = 0x01;
	
	CCF0=0;
	
	CL = 0;                         //复位PCA寄存器
    CH = 0;sss
	CR = 0;                         //PCA定时器停止工作
	//EA = 1 ;
}

char infred_send_bit (char n)
{
	int len_high;
	int cnt = 0;
	//T38KHz
	int t_38khz ;
	t_38khz = T38KHz ;
	CCAP0L = t_38khz;					//设置38KHz Fclk20Mhz/2/38Khz = 267 = 0x107
	CCAP0H = t_38khz>>8;
	t_38khz +=  T38KHz ;
	
	CR = 1;                         //PCA定时器开始工作
	
	switch ( n )
	{
		case 0: len_high = INFRED_BIT_0;break; 
		case 1: len_high = INFRED_BIT_1; break; 
		default: len_high = INFRED_BIT_START; break; 
	}
	
	//发送高脉冲;;;'
	do {
		
		while(~CCF0);
		CCF0=0;
		CCAP0L = t_38khz;					//设置38KHz Fclk20Mhz/2/38Khz = 267 = 0x107
		CCAP0H = t_38khz>>8;
		t_38khz +=  T38KHz ;
		cnt ++;
	}while(cnt < len_high);
	CR = 0;  
	//发送低脉冲
	for(cnt=0;cnt<2000;cnt++);
	
	return 1 ;
}

//发送１Ｂ　，　先发高位
char infred_send_byte (char n)
{
	int i=0 ;
	do{
		if ((n>>i)&1)
		//if (1)
			infred_send_bit(0x01);
		else
			infred_send_bit(0x00);
		i++;
	}while(i<8);
	
}

extern char infred_send(char * str ,int len)
{
	int i ;
	infred_send_bit(2); //发送开始位
	for ( i=0;i<len;i++) {
		infred_send_byte(*(str+i));
	}
	return 1 ;
}