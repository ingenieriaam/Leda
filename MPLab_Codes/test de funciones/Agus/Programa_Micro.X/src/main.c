/**********************************************************************
* © 2008 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33Fxxxx
* Compiler:        MPLAB® C30 v3.02 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
* ADDITIONAL NOTES:
* Code Tested on:
* 16-Bit 28-Pin Starter board with dsPIC33FJ128GP802 device 
**********************************************************************/

#include <p33Fxxxx.h>
#include "dsp.h"
#include "../h/adcdacDrv.h"
#include <stdlib.h>
#include <math.h>


//Prototipos
//extern fractional* FIR ( int numSamps, fractional* dstSamps,fractional* srcSamps,FIRStruct* filter);
extern void assembly_loopback(fractional* ,fractional* ,unsigned int);
extern void overdrive_num(fractional* ,fractional* ,fractional);
extern void overdrive_dem(fractional* ,fractional* ,fractional);
extern void overdrive_DIV(fractional*,fractional* ,fractional*);
extern void pasa_bajos(float,fractional,fractional,fractional,fractional,fractional,fractional,fractional);

// Internal FRC Oscillator
_FOSCSEL(FNOSC_FRC);							// FRC Oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_NONE); 
												// Clock Switching is enabled and Fail Safe Clock Monitor is disabled
												// OSC2 Pin Function: OSC2 is Clock Output
												// Primary Oscillator Mode: Disabled

_FWDT(FWDTEN_OFF);              				// Watchdog Timer Enabled/disabled by user software
												// (LPRC can be disabled by clearing SWDTEN bit in RCON register

int main (void)
{
	// Configure Oscillator to operate the device at 40MIPS
	// Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
	// Fosc= 7.37M*43/(2*2)=79.22Mhz for ~40MIPS input clock
	PLLFBD=41;									// M=43
	CLKDIVbits.PLLPOST=0;						// N1=2
	CLKDIVbits.PLLPRE=0;						// N2=2
	OSCTUN=0;									// Tune FRC oscillator, if FRC is used

        CORCONbits.SATA = 1;
        CORCONbits.SATB = 1;

	// Disable Watch Dog Timer
	RCONbits.SWDTEN=0;

	// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x01);				// Initiate Clock Switch to
												// FRC with PLL (NOSC=0b001)
	__builtin_write_OSCCONL(0x01);				// Start clock switching
	while (OSCCONbits.COSC != 0b001);			// Wait for Clock switch to occur

	// Wait for PLL to lock
	while(OSCCONbits.LOCK!=1) {};
	
	
   	initAdc();              					// Initialize the A/D converter to convert Channel 4
	initDma0();									// Initialize the DMA controller to buffer ADC data in conversion order
	initDma1();
//        initDma2();
	initDac(); 									// Initialize the D/A converter 
	initTmr3();									// Initialize the Timer to generate sampling event for ADC

	extern fractional BufferA[NUMSAMP];			// Ping pong buffer A
	extern fractional BufferB[NUMSAMP];			// Ping pong buffer B
	extern fractional BufferC[NUMSAMP];			// Ping pong buffer C
	extern fractional BufferD[NUMSAMP];			// Ping pong buffer D
//	extern fractional BufferE[NUMSAMP];			// Ping pong buffer E
//	extern fractional BufferF[NUMSAMP];			// Ping pong buffer F
        
	extern unsigned int DmaBuffer;				// DMA flag
	extern int flag;					// Flag
        fractional num[NUMSAMP],dem[NUMSAMP];


    while (1)              					// Loop Endlessly - Execution is interrupt driven
    { 		
		if(flag) 
		{            
		//------------ OVERDRIVE EN C -----------------

                        if(DmaBuffer == 1)
                        {
                                 overdrive_num(&num[0],&BufferA[0],NUMSAMP);
                                 overdrive_dem(&dem[0],&BufferA[0],NUMSAMP);
                                 overdrive_DIV(&BufferC[0],&num[0],&dem[0]);

                        }
                         else
                         {
                                    overdrive_num(&num[0],&BufferB[0],NUMSAMP);
                                    overdrive_dem(&dem[0],&BufferB[0],NUMSAMP);
                                    overdrive_DIV(&BufferD[0],&num[0],&dem[0]);
                         }

			flag = 0;
		}		
	}
    
	return 0;

}

