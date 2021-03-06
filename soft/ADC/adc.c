/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 系列 AD转换中断方式举例----------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/* 如果要在文章中应用此代码,请在文章中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

//本示例在Keil开发环境下请选择Intel的8058芯片型号进行编译
//若无特别说明,工作频率一般为11.0592MHz

#include "../proj/src/sys.h"
#include "STC15.H"
#include "intrins.h"
#include "adc.h"

/*----------------------------
读取ADC结果
----------------------------*/
u16 GetADCResult(u8 ch)
{
	u16 tmp =0;
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
	Delay(20); 
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC
	tmp = ADC_RES;
	tmp = tmp + ADC_RESL;
    return tmp;                 //返回ADC结果
}

/*----------------------------
初始化ADC
----------------------------*/
void InitADC()
{
	P1M1=0x0c;        //仅ADC2/P12和ADC3/P13高阻输入
  P1M0=0x00;        //注意CCP1/P10和CCP0/P11不能为高阻输入
  P1ASF=0x0c;        //ADC2及ADC3为A/D转换通道
	
	//CLK_DIV |=0x00 ;	//	ADC_RES[1:0], ADC_RESL[7:0]
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC上电并延时
}

void Delay(u16 n)
{
    u16 x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}
