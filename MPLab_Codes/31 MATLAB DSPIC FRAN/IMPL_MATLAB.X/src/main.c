#include <p33Fxxxx.h>
#include "../h/dsp.h"
#include "../h/adcdacDrv.h"


//Prototipos

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
	
	
   	//initAdc();              					// Initialize the A/D converter to convert Channel 4
	//initDma0();									// Initialize the DMA controller to buffer ADC data in conversion order
	//initDma1();
	//initDac(); 									// Initialize the D/A converter
	initTmr3();									// Initialize the Timer to generate sampling event for ADC

        fractional BufferA[NUMSAMP];
//        extern fractional delayline[LENGTHECO];			// Ping pong buffer D
	//extern fractional delayline[LENGTHECO];			// Ping pong buffer D
//        unsigned int paso = 0;

        BufferA[0] = 1;
        BufferA[1] = 2;
        BufferA[2] = 8;
        BufferA[3] = 3;
        BufferA[4] = 4;
        int Index=0;
        //----------------------------------
        while (1)               					// Loop Endlessly - Execution is interrupt driven
        {
            //assembly_loopback(&BufferC[0],&BufferA[0],NUMSAMP);
            VectorMax(NUMSAMP,&BufferA[0],&Index);
        }
        return 0;

}

