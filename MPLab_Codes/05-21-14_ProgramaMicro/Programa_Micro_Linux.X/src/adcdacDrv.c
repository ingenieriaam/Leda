/**********************************************************************
* © 2008 Microchip Technology Inc.
*
* FileName:        adcdacDrv.c
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
**********************************************************************/


#include <p33Fxxxx.h>
#include "dsp.h"
#include "../h/adcdacDrv.h"
                    
fractional BufferA[NUMSAMP] __attribute__((space(dma)));	// Ping-pong buffer A
fractional BufferB[NUMSAMP] __attribute__((space(dma)));	// Ping-pong buffer B
fractional BufferC[NUMSAMP] __attribute__((space(dma)));	// Ping-pong buffer C
fractional BufferD[NUMSAMP] __attribute__((space(dma)));	// Ping-pong buffer D
fractional delayline[LENGTHECO];


/*=============================================================================
initAdc() is used to configure A/D to convert channel 4 on Timer event. 
It generates event to DMA on every sample/convert sequence.  
=============================================================================*/
void initAdc(void)
{	
	AD1CON1bits.FORM = 3;			// Data Output Format: Signed Fraction (Q15 format)
	AD1CON1bits.SSRC = 2;			// Sample Clock Source: GP Timer starts conversion
	AD1CON1bits.ASAM = 1;			// ADC Sample Control: Sampling begins immediately after conversion
	AD1CON1bits.AD12B = 1;			// 12-bit ADC operation

	AD1CON2bits.CHPS = 0;			// Converts CH0
    
	AD1CON3bits.ADRC = 0;			// ADC Clock is derived from Systems Clock
	AD1CON3bits.ADCS = 3;			// ADC Conversion Clock Tad=Tcy*(ADCS+1)= (1/40M)*4 = 100ns 
						// ADC Conversion Time for 12-bit Tc=14*Tad = 1.4us 
				
	AD1CON1bits.ADDMABM = 1; 		// DMA buffers are built in conversion order mode
	AD1CON2bits.SMPI = 0;			// SMPI must be 0


        //AD1CHS0: A/D Input Select Register
        AD1CHS0bits.CH0SA = 0;			// MUXA +ve input selection (AN0) for CH0
	AD1CHS0bits.CH0NA = 0;			// MUXA -ve input selection (Vref-) for CH0

        //AD1PCFGH/AD1PCFGL: Port Configuration Register
	AD1PCFGL=0xFFFF;
        AD1PCFGLbits.PCFG0 = 0;			// AN0 as Analog Input

        IFS0bits.AD1IF = 0;			// Clear the A/D interrupt flag bit
        IEC0bits.AD1IE = 0;			// Do Not Enable A/D interrupt
        AD1CON1bits.ADON = 1;			// Turn on the A/D converter
}

/*=============================================================================
initDac() is used to configure D/A. 
=============================================================================*/
void initDac(void)
{
	// Configuracion nueva
	ACLKCONbits.SELACLK = 0;		// FRC w/ Pll as Clock Source 
	ACLKCONbits.AOSCMD = 0;			// Auxiliary Oscillator Disabled
	ACLKCONbits.ASRCSEL = 0;		// Auxiliary Oscillator is the Clock Source
	ACLKCONbits.APSTSCLR = 7;		// FRC divide by 1 

	DAC1STATbits.LOEN = 1;                  // Left Channel DAC Output Enabled
	DAC1STATbits.LITYPE = 1;                // Left Channel Interrupt if FIFO is Empty
	
        DAC1CONbits.AMPON = 0;                  // Amplifier is Disabled During Sleep/Idle Modes

	DAC1CONbits.DACFDIV = 13;                // Divide High Speed Clock by DACFDIV+1
                                                // 5: 103.16KHz  76: 8.038KHz 13: 44.211KHz 23: 25KHz
	
	DAC1CONbits.FORM = 1;                   // Data Format is signed (2?s complement)
	DAC1CONbits.DACEN = 1;                  // DAC1 Module Enabled

	
}

/*=============================================================================
_DAC1RInterrupt(): ISR name is chosen from the device linker script.
=============================================================================*/
/*
void __attribute__((interrupt, no_auto_psv)) _DAC1RInterrupt(void)
{
	IFS4bits.DAC1RIF = 0; 			// Clear Right Channel Interrupt Flag 	 
	_LATA0=1;
}
*/

/*=======================================================================================  
Timer 3 is setup to time-out every Ts secs. As a result, the module 
will stop sampling and trigger a conversion on every Timer3 time-out Ts. 
At that time, the conversion process starts and completes Tc=12*Tad periods later.
When the conversion completes, the module starts sampling again. However, since Timer3 
is already on and counting, about (Ts-Tc)us later, Timer3 will expire again and trigger 
next conversion. 
=======================================================================================*/
void initTmr3() 
{
	TMR3 = 0x0000;					// Clear TMR3
	PR3 = SAMPPRD;					// Load period value in PR3
	IFS0bits.T3IF = 0;				// Clear Timer 3 Interrupt Flag
	IEC0bits.T3IE = 0;				// Clear Timer 3 interrupt enable bit
	T3CONbits.TON = 1;				// Enable Timer 3
}

/*=============================================================================  
DMA0 configuration
 Direction: Read from peripheral address 0-x300 (ADC1BUF0) and write to DMA RAM 
 AMODE: Register indirect with post increment
 MODE: Continuous, Ping-Pong Mode
 IRQ: ADC Interrupt
 ADC stores results stored alternatively between BufferA[] and BufferB[]
=============================================================================*/
void initDma0(void)
{
	DMA0CONbits.AMODE = 0;			// Configure DMA for Register indirect with post increment
	DMA0CONbits.MODE = 2;			// Configure DMA for Continuous Ping-Pong mode

	DMA0PAD = (int)&ADC1BUF0;		// Peripheral Address Register: ADC buffer
	DMA0CNT = (NUMSAMP-1);			// DMA Transfer Count is (NUMSAMP-1)	
	
	DMA0REQ = 13;					// ADC interrupt selected for DMA channel IRQ
	
	DMA0STA = __builtin_dmaoffset(BufferA);	// DMA RAM Start Address A	
	DMA0STB = __builtin_dmaoffset(BufferB); // DMA RAM Start Address B

	IFS0bits.DMA0IF = 0;			// Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;			// Set the DMA interrupt enable bit
	
	DMA0CONbits.CHEN = 1;			// Enable DMA channel
}

/*=============================================================================
_DMA0Interrupt(): ISR name is chosen from the device linker script.
=============================================================================*/
unsigned int DmaBuffer = 0;
int flag = 0;

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	DmaBuffer ^= 1;					// Ping-pong buffer select flag
	flag = 1;						// Ping-pong buffer full flag
 	IFS0bits.DMA0IF = 0;			// Clear the DMA0 Interrupt Flag
}


/*=============================================================================  
DMA1 configuration
Direction: Read from peripheral address BUfferC y BufferD and write to DAC1RDAT
 AMODE: Register indirect with post increment
 MODE: Continuous, Ping-Pong Mode, BufferC y BufferD
 IRQ: DAC Interrupt IRQ=78 , DMA1PAD=DAC1RDAT 
 =============================================================================*/
void initDma1(void)
{
	DMA1CONbits.AMODE = 0;					// Configure DMA for Register indirect with post increment
	DMA1CONbits.MODE = 2;					// Configure DMA for Continuous Ping-Pong mode
	DMA1CONbits.DIR=1;                                      //de DPSRAM a periferico

	DMA1PAD = (volatile unsigned int)&DAC1LDAT;		// Point DMA to DAC1LDAT
	
	DMA1CNT = (NUMSAMP-1);					// DMA Transfer Count is (NUMSAMP-1)
			
	DMA1REQ = 79;                                           // Select DAC1LDAT as DMA

        //DMA1CONbits.HALF=0;                                   //Interrupcion cuando envia el bloque entero
 
	DMA1STA = __builtin_dmaoffset(BufferC);                 // DMA RAM Start Address C
	DMA1STB = __builtin_dmaoffset(BufferD);                 // DMA RAM Start Address D

	IFS0bits.DMA1IF = 0;					// Clear the DMA interrupt flag bit
        IEC0bits.DMA1IE = 1;					// Set the DMA interrupt enable bit
	DMA1CONbits.CHEN = 1;					// Enable DMA channel
}


/*=============================================================================
_DMA1Interrupt(): ISR name is chosen from the device linker script.
=============================================================================*/
//unsigned int DmaBuffer = 0;
//int flag = 0;
void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
	//DmaBuffer ^= 1;					// Ping-pong buffer select flag
	//flag = 1;						// Ping-pong buffer full flag
   	
	IFS0bits.DMA1IF = 0;			// Clear the DMA1 Interrupt Flag
    /*
	int i;
    for( i = 0; i < NUMSAMP; i++)
	{
	  if(DmaBuffer == 0)
		BufferC[i] = BufferA[i];		// Load the DAC buffer with data
	  else
		BufferD[i] = BufferB[i];		// Load the DAC buffer with data
	}
    */
}








