/**
  ******************************************************************************
  * @file    myuart.h
  * @author  Ri-Sheng Chen
  * @brief   This file contains UART setting functions definition
  ******************************************************************************
  */

#ifndef _MYLIB_H_
#define _MYLIB_H_

#define F_CPU 16000000UL
#define UART_BAUD 9600
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*  functions definition  */
void UNO_stdio_set(void);
int stdio_putchar(char c, FILE *stream);
int stdio_getchar(FILE *stream);

#endif /* end of _MYLIB_H */