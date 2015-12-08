#ifndef FOSC
  #define FOSC 11059200L          //ϵͳƵ��
#endif

#ifndef BAUD
  #define BAUD 115200             //���ڲ�����
#endif

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��

#define PARITYBIT EVEN_PARITY   //����У��λ

#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

void serial_init ();
char serial_ReciveData();
void serial_SendData(char dat);
void serial_SendString(char *s);