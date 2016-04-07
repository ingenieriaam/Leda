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


//Prototipos
//extern fractional* FIR ( int numSamps, fractional* dstSamps,fractional* srcSamps,FIRStruct* filter);
//extern fractional* assembly_loopback(fractional* dst,fractional* src,int numSamps);   //prototipo funcion asembly
//extern fractional* eco(fractional* dst,fractional* src,fractional* delayline,int numSamps);   //prototipo funcion asembly
extern fractional* assembly_ruido(fractional* ,fractional* ,unsigned int);   //prototipo funcion asembly
extern fractional* assembly_puertaruido(fractional* ,fractional* ,unsigned int);   //prototipo funcion asembly
extern fractional* assembly_distorsion(fractional* ,fractional* ,unsigned int);   //prototipo funcion asembly
//extern fractional* assembly_overdrive(fractional* ,fractional* ,unsigned int);
extern fractional* assembly_overdrivemediaonda(fractional* ,fractional* ,unsigned int);
//extern fractional* assembly_overdrive3(fractional* ,fractional* ,unsigned int);
extern fractional* assembly_eco(fractional* ,fractional* ,fractional* ,unsigned int);
extern fractional* assembly_eco_xdata(fractional* ,fractional* ,unsigned int);
extern fractional* assembly_loopback(fractional* ,fractional* ,unsigned int);
extern fractional* cero(fractional* ,fractional* ,unsigned int);
extern fractional* assembly_xdata_init(void);
extern fractional* assembly_xdata_init_BitReversed(void);
//FIR Struct
//extern FIRStruct LowPassFilter;


//Macros for Configuration Fuse Registers:
//Invoke macros to set up  device configuration fuse registers.
//The fuses will select the oscillator source, power-up timers, watch-dog
//timers etc. The macros are defined within the device
//header files. The configuration fuse registers reside in Flash memory.



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
	initDac(); 									// Initialize the D/A converter 
	initTmr3();									// Initialize the Timer to generate sampling event for ADC

	extern fractional BufferA[NUMSAMP];			// Ping pong buffer A
	extern fractional BufferB[NUMSAMP];			// Ping pong buffer B
	extern fractional BufferC[NUMSAMP];			// Ping pong buffer C
	extern fractional BufferD[NUMSAMP];			// Ping pong buffer D
//        extern fractional delayline[LENGTHECO];			// Ping pong buffer D
	//extern fractional delayline[LENGTHECO];			// Ping pong buffer D
//        unsigned int paso = 0;
        
	extern unsigned int DmaBuffer;				// DMA flag
	extern int flag;					// Flag
 	
        fractional prueba[10];
        prueba[0] = 0x3000;
        prueba[1] = 0x0001;
        prueba[2] = 0xFFFF;
        prueba[3] = 0x7FFF;
        prueba[4] = 0x8000;
        prueba[5] = 0xF001;
        prueba[6] = 0x3FFF;
        prueba[7] = 0x4000;
        prueba[8] = 0x9001;
        prueba[9] = 0x8001;

	//int i;
 	
	//Configura el DMA para buferear el ADC
	//Luego en el siguiente for saca las muestras por el DAC a mano sin DMA...
    
	//FIRDelayInit(&LowPassFilter);

        //PARA LOS DISTINTOS ECOS-----------
        //assembly_xdata_init();
        assembly_xdata_init_BitReversed();
        //----------------------------------
    while (1)               					// Loop Endlessly - Execution is interrupt driven
    {
        //flag = 1;
		if(flag) 
		{            
			
			/*
			//ASSEMBLY INSTRUCTION TEST
   		    if(DmaBuffer == 0)
				 assembly_test(256, &BufferC[0],&BufferA[0], &LowPassFilter); 
			else
				 FIR(256, &BufferD[0],&BufferB[0], &LowPassFilter); 
			//*/			 
			


			/*
			//FIR
                        if(DmaBuffer == 0)
				 FIR(256, &BufferC[0],&BufferA[0], &LowPassFilter); 
			else
				 FIR(256, &BufferD[0],&BufferB[0], &LowPassFilter); 
			//*/
			

			/*
			//LOOP BACK EN C
			for( i = 0; i < NUMSAMP; i++)
			{
			  if(DmaBuffer == 0)
					BufferC[i] = BufferA[i];		// Load the DAC buffer with data
			  else
			    	        BufferD[i] = BufferB[i];		// Load the DAC buffer with data
			}
		    
			
			*/


                        /*
                        //Noise Gate
                        if(DmaBuffer == 0)
                                        assembly_ruido(&BufferC[0],&BufferA[0],NUMSAMP);
			else
					assembly_ruido(&BufferD[0],&BufferB[0],NUMSAMP);
                        */

                        /*
                        //Noise Gate Nueva
                        if(DmaBuffer == 0)
                                        assembly_puertaruido(&BufferC[0],&BufferA[0],NUMSAMP);
			else
					assembly_puertaruido(&BufferD[0],&BufferB[0],NUMSAMP);
                        */


                        //DISTOR 1.0
                        /*
                        if(DmaBuffer == 1)
                                        assembly_distorsion(&BufferC[0],&BufferA[0],NUMSAMP);
			else
					assembly_distorsion(&BufferD[0],&BufferB[0],NUMSAMP);

                        */


                        //OVERDRIVE
                        /*
                        if(DmaBuffer == 1)
                                        assembly_overdrivemediaonda(&BufferC[0],&BufferA[0],NUMSAMP);
                         else
                                        assembly_overdrivemediaonda(&BufferD[0],&BufferB[0],NUMSAMP);
                        */
                        //chequeo de cero
                        /*
                        if(DmaBuffer == 1)
                                        cero(&BufferC[0],&BufferA[0],NUMSAMP);
                         else
                                        cero(&BufferD[0],&BufferB[0],NUMSAMP);
                        */


                        //ECO
                        /*
                        if(DmaBuffer == 1){


                                        assembly_eco(&BufferC[0],&BufferA[0],&delayline[NUMSAMP*paso],NUMSAMP);
                                        paso++;
                                        if(paso==10) paso = 0;
			}
			else{
					assembly_eco(&BufferD[0],&BufferB[0],&delayline[NUMSAMP*paso],NUMSAMP);
                                        paso++;
                                        if(paso==10) paso = 0;
                        }
			*/

                        //XDATA CON ECO
                        //*
                        if(DmaBuffer == 1)
                                        assembly_eco_xdata(&BufferC[0],&BufferA[0],NUMSAMP);
                         else
                                        assembly_eco_xdata(&BufferD[0],&BufferB[0],NUMSAMP);
                        //*/

			/*
			//LOOP BACK EN ASSEMBLER
			
			for( i = 0; i < 100; i++) //Pequeño delay..
			Nop();
			if(DmaBuffer == 0){
					
					assembly_loopback(&BufferC[0],&BufferA[0],NUMSAMP);
					
			else
					assembly_loopback(&BufferD[0],&BufferB[0],NUMSAMP);
			
			*/
                        /*
                        if(DmaBuffer == 1)
                                        assembly_loopback(&BufferC[0],&BufferA[0],NUMSAMP);
                         else
                                        assembly_loopback(&BufferD[0],&BufferB[0],NUMSAMP);
                         */
			

			/*
			//-------- LOOP ORIGINAL SIN DMA -----------
			
			for(i = 0; i < NUMSAMP; i++)
			{
				while(DAC1STATbits.REMPTY != 1);// Wait for D/A conversion
				if(DmaBuffer == 0)
					DAC1RDAT = BufferA[i];		// Load the DAC buffer with data
				else
					DAC1RDAT = BufferB[i];		// Load the DAC buffer with data
			}
			*/	
			flag = 0;
		}		
	}
    
	return 0;

}

