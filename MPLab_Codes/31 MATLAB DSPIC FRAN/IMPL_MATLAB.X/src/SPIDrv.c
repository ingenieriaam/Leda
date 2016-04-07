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
	SPI2STAT = 0;  // disable the SPI module (just in case)



        SPI2CON1 = 0x0161;	// FRAMEN = 0, SPIFSD = 0, DISSDO = 0, MODE16 = 0; SMP = 0; CKP = 1; CKE = 1; SSEN = 0; MSTEN = 1; SPRE = 0b000, PPRE = 0b01
	SPI2CON1bits.DISSCK = 0;        //Internal SPI clock enabled
	SPI2CON1bits.DISSDO = 0;
        SPI2CON1bits.MODE16 = 1;         //word-wide communication (16 bits)
	SPI2CON1bits.SMP = 1;           //For the fastest SPI data rate possible
        SPI2CON1bits.CKE = 1;
	SPI2CON1bits.SSEN = 0;          //Slave Select Enable bit
	SPI2CON1bits.CKP = 0;
        SPI2CON1bits.MSTEN = 1;         //Master Mode Enable bit
	SPI2CON1bits.PPRE = 1;
	SPI2CON1bits.SPRE = 1;
	SPI2STATbits.SPIEN = 1; // enable the SPI module

}

/*
 * 
 */


