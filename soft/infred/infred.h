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

sfr P_SW1       = 0xA2;             //外设功能切换寄存器1

sfr CCON        =   0xD8;           //PCA控制寄存器
sbit CCF0       =   CCON^0;         //PCA模块0中断标志
sbit CCF1       =   CCON^1;         //PCA模块1中断标志
sbit CCF2       =   CCON^2;         //PCA模块2中断标志
sbit CCF3       =   CCON^3;         //PCA模块3中断标志
sbit CR         =   CCON^6;         //PCA定时器运行控制位
sbit CF         =   CCON^7;         //PCA定时器溢出标志
sfr CMOD        =   0xD9;           //PCA模式寄存器
sfr CL          =   0xE9;           //PCA定时器低字节
sfr CH          =   0xF9;           //PCA定时器高字节
sfr CCAPM0      =   0xDA;           //PCA模块0模式寄存器
sfr CCAP0L      =   0xEA;           //PCA模块0捕获寄存器 LOW
sfr CCAP0H      =   0xFA;           //PCA模块0捕获寄存器 HIGH
sfr CCAPM1      =   0xDB;           //PCA模块1模式寄存器
sfr CCAP1L      =   0xEB;           //PCA模块1捕获寄存器 LOW
sfr CCAP1H      =   0xFB;           //PCA模块1捕获寄存器 HIGH
sfr CCAPM2      =   0xDC;           //PCA模块2模式寄存器
sfr CCAP2L      =   0xEC;           //PCA模块2捕获寄存器 LOW
sfr CCAP2H      =   0xFC;           //PCA模块2捕获寄存器 HIGH
sfr PCA_PWM0    =   0xf2;           //PCA模块0的PWM寄存器
sfr PCA_PWM1    =   0xf3;           //PCA模块1的PWM寄存器
sfr PCA_PWM2    =   0xf4;           //PCA模块2的PWM寄存器

void infred_init (void );

char infred_send_bit (char n);

char infred_send_byte (char n);

extern char infred_send (char * str , int len);//(char * pdata , int len);