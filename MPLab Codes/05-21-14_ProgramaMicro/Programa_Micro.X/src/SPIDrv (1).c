/* 
 * File:   SPIDrv.c
 * Author: dplab
 *
 * Created on May 7, 2014, 4:44 PM
 */

#include <p33Fxxxx.h>

void Init_SPI(void)
{

	// setup the SPI peripheral
	SPI2STAT = 0x0;  // disable the SPI module (just in case)
	SPI2CON1 = 0x0161;	// FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
	SPI2CON1bits.CKE = 0x01;
	SPI2CON1bits.CKP = 0x00;
	SPI2STAT = 0x8000; // enable the SPI module

}

/*
 * 
 */


