
typedef unsigned int u32;
typedef int s32;
typedef unsigned char u8;
typedef signed char s8;

extern void uart_init(u32 );
extern void uart_tx(u8);
extern u8 uart_rx(void);

extern void delay_sec(unsigned int);
extern void delay_ms(unsigned int);

extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_cgram(void);

extern void init_interrupt(void);
extern volatile int flag2,flag1,pairflag;
extern unsigned char temp,flag;





