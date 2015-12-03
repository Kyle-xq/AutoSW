#define INFRED_PIN P00
#define INFRED_BIT_LEN 239
#define INFRED_BIT_START 200
#define INFRED_BIT_1 100
#define INFRED_BIT_0 40

#define FOSC    20000000L
#define T38KHz (FOSC / 2 / 38000)

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5

typedef unsigned char BYTE;
typedef unsigned int WORD;

sfr P_SW1       = 0xA2;             //���蹦���л��Ĵ���1

sfr CCON        =   0xD8;           //PCA���ƼĴ���
sbit CCF0       =   CCON^0;         //PCAģ��0�жϱ�־
sbit CCF1       =   CCON^1;         //PCAģ��1�жϱ�־
sbit CCF2       =   CCON^2;         //PCAģ��2�жϱ�־
sbit CCF3       =   CCON^3;         //PCAģ��3�жϱ�־
sbit CR         =   CCON^6;         //PCA��ʱ�����п���λ
sbit CF         =   CCON^7;         //PCA��ʱ�������־
sfr CMOD        =   0xD9;           //PCAģʽ�Ĵ���
sfr CL          =   0xE9;           //PCA��ʱ�����ֽ�
sfr CH          =   0xF9;           //PCA��ʱ�����ֽ�
sfr CCAPM0      =   0xDA;           //PCAģ��0ģʽ�Ĵ���
sfr CCAP0L      =   0xEA;           //PCAģ��0����Ĵ��� LOW
sfr CCAP0H      =   0xFA;           //PCAģ��0����Ĵ��� HIGH
sfr CCAPM1      =   0xDB;           //PCAģ��1ģʽ�Ĵ���
sfr CCAP1L      =   0xEB;           //PCAģ��1����Ĵ��� LOW
sfr CCAP1H      =   0xFB;           //PCAģ��1����Ĵ��� HIGH
sfr CCAPM2      =   0xDC;           //PCAģ��2ģʽ�Ĵ���
sfr CCAP2L      =   0xEC;           //PCAģ��2����Ĵ��� LOW
sfr CCAP2H      =   0xFC;           //PCAģ��2����Ĵ��� HIGH
sfr PCA_PWM0    =   0xf2;           //PCAģ��0��PWM�Ĵ���
sfr PCA_PWM1    =   0xf3;           //PCAģ��1��PWM�Ĵ���
sfr PCA_PWM2    =   0xf4;           //PCAģ��2��PWM�Ĵ���

void infred_init (void );

char infred_send_bit (char n);

char infred_send_byte (char n);

extern char infred_send (char * str , int len);//(char * pdata , int len);