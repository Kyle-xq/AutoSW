#ifndef FOSC
  #define FOSC 11059200L          //系统频率
#endif

#ifndef FOSC
  #define BAUD 115200             //串口波特率
#endif

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验

void serial_init ();
void serial_SendData(BYTE dat);
void serial_SendString(char *s);