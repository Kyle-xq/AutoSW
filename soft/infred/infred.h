#define INFRED_PIN P00
#define INFRED_BIT_LEN 239
#define INFRED_BIT_START 200
#define INFRED_BIT_1 100
#define INFRED_BIT_0 40

#define FOSC    11059200L		//ÏµÍ³ÆµÂÊ
#define T38KHz (FOSC / 2 / 38000)

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5

typedef unsigned char BYTE;
typedef unsigned int WORD;

void infred_init (void );

char infred_send_bit (char n);

char infred_send_byte (char n);

extern char infred_send (char * str , int len);//(char * pdata , int len);