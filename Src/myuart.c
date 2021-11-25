/**
  ******************************************************************************
  * @file    myuart.c
  * @author  Ri-Sheng Chen
  * @brief   This file contains UART setting functions
  ******************************************************************************
  */

#include "../Inc/myuart.h"

static FILE STDIO_BUFFER = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar, _FDEV_SETUP_RW);
// Based on ATMega328 datasheet p.184, Sending Frames with 5 to 8 Data Bit
int stdio_putchar(char c, FILE *stream) 
{
	// 超級終端機中使用CRLF('\n'+'\r')作為完整換行
	// 當使用者使用'\n'換行時需補送'\r'
    if (c == '\n') 
        stdio_putchar('\r',stream); 
	
	// 等待暫存器清空, UART0傳送資料完成時UCSR0A中UDRE0旗標會自動設為0
	// 確認暫存器空才能放入新資料 
	// ATMega328 datasheet p.184, UCSRnA
    while(!(UCSR0A&(1<<UDRE0))); 

	// 將待傳送資料放入UART0資料暫存器
    UDR0 = c;
	
    return 0; 
}

// Based on ATMega328 datasheet p.187, Receiving Frames with 5 to 8 Data Bits
int stdio_getchar(FILE *stream)
{
	int UDR_Buff;
	
	// 等待資料接收, UART0接收到資料時UCSR0A中RXC0旗標會自動設為0
	// 確認收到新資料才能從暫存器取值
	// ATMega328 datasheet p.187, UCSRnA
    while(!(UCSR0A&(1<<RXC0)));
	
	// 將UART0資料暫存器中的資料取出
	UDR_Buff = UDR0;
	
	// 將超級終端機中輸入的資料傳送回去, 否則使用scanf時被傳送到AVR的資料不會顯示在超級終端機畫面中
	stdio_putchar(UDR_Buff,stream);

	return UDR_Buff;
}

void UNO_stdio_set(void)
{
	unsigned int ubrr_data;

	// Asynchronous Normal Mode 
	ubrr_data = F_CPU/16/UART_BAUD-1;
	UBRR0H = (unsigned char)(ubrr_data>>8);
	UBRR0L = (unsigned char)ubrr_data;
	
	// UCSR0B
	// Rx Enable, Tx Enable
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	
	// UCSRnC
	// Character Size : 8-bit
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);

	// 指定printf、scanf使用的暫存區
	stdout = &STDIO_BUFFER;
	stdin = &STDIO_BUFFER;
}
