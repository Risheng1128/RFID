/**
  ******************************************************************************
  * @file    main.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a example of read uid of card
  ******************************************************************************
  */
#include "../Inc/myuart.h"
#include "../Inc/RFID.h"

int main (void){
    UNO_stdio_set();
    SPI_Set();
    RFID_Set();

	printf("--------------------START------------------------\n");
    while(1){
		while(!IsNewCardPresent());		
		while(!ReadCardSerial());
		printf("A new card detected\n");
        for(uint8_t i = 0; i < 4;i++){
			printf("data[%d] = %x\n",i,data.uidByte[i]);
		}
		PICC_HaltA();
		PCD_StopCrypto1();
    }
}