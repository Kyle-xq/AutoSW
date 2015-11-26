#include "reg51.h"
#include "infred.h"

void infred_init (void )
{
	//�������ж�
	//IE |= 0x80 ;
	//��������ܽ�
	ACC = P_SW1;
    ACC &= ~(CCP_S0 | CCP_S1);      //CCP_S0=0 CCP_S1=0
    P_SW1 = ACC;                    //(P1.2/ECI, P1.1/CCP0, P1.0/CCP1, P3.7/CCP2)
	//
	CCON = 0;                       //��ʼ��PCA���ƼĴ���
                                    //PCA��ʱ��ֹͣ
                                    //���CF��־
                                    //���ģ���жϱ�־
	
    CMOD = 0x08;                    //����PCAʱ��Դ SYS_CLK
                                    //��ֹPCA��ʱ������ж�
	//PCA_PWM0 = 0x00;                //PCAģ��0������8λPWM
    //CCAP0H = CCAP0L = 0x80;         //PWM0��ռ�ձ� ((100H-80H)/100H)
	
    CCAPM0 = 0x4C;                  //PCAģ��0Ϊ16λ��������ģʽ
	//CCAP0L = 0x07;					//����38KHz Fclk20Mhz/2/38Khz = 267 = 0x107
	//CCAP0H = 0x01;
	
	CCF0=0;
	
	CL = 0;                         //��λPCA�Ĵ���
    CH = 0;sss
	CR = 0;                         //PCA��ʱ��ֹͣ����
	//EA = 1 ;
}

char infred_send_bit (char n)
{
	int len_high;
	int cnt = 0;
	//T38KHz
	int t_38khz ;
	t_38khz = T38KHz ;
	CCAP0L = t_38khz;					//����38KHz Fclk20Mhz/2/38Khz = 267 = 0x107
	CCAP0H = t_38khz>>8;
	t_38khz +=  T38KHz ;
	
	CR = 1;                         //PCA��ʱ����ʼ����
	
	switch ( n )
	{
		case 0: len_high = INFRED_BIT_0;break; 
		case 1: len_high = INFRED_BIT_1; break; 
		default: len_high = INFRED_BIT_START; break; 
	}
	
	//���͸�����;;;'
	do {
		
		while(~CCF0);
		CCF0=0;
		CCAP0L = t_38khz;					//����38KHz Fclk20Mhz/2/38Khz = 267 = 0x107
		CCAP0H = t_38khz>>8;
		t_38khz +=  T38KHz ;
		cnt ++;
	}while(cnt < len_high);
	CR = 0;  
	//���͵�����
	for(cnt=0;cnt<2000;cnt++);
	
	return 1 ;
}

//���ͣ��¡������ȷ���λ
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
	infred_send_bit(2); //���Ϳ�ʼλ
	for ( i=0;i<len;i++) {
		infred_send_byte(*(str+i));
	}
	return 1 ;
}