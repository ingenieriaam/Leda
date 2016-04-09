#include "../include/adcdacDrv.h"


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
    fractional idx_frec_fund;
    int i=0;
    char init = 0;
    char nota;


    // Configure Oscillator to operate the device at 40MIPS
    // Fosc = Fin*M/(N1*N2), Fcy=Fosc/2
    // Fosc = 7.37M*43/(2*2)=79.22Mhz for ~40MIPS input clock
    PLLFBD=41;                              // M=43
    CLKDIVbits.PLLPOST=0;                   // N1=2
    CLKDIVbits.PLLPRE=0;                    // N2=2
    OSCTUN=0;                               // Tune FRC oscillator, if FRC is used
    
    CORCONbits.IF = 0;                      // CORCON<0> = 0 (para MPY-assembler en modo fractional)
    
    RCONbits.SWDTEN=0;                      // Deshabilita Watch Dog Timer

    // Clock switch to incorporate PLL
    __builtin_write_OSCCONH(0x01);          // Initiate Clock Switch to
                                                    // FRC with PLL (NOSC=0b001)
    __builtin_write_OSCCONL(0x01);          // Start clock switching
    while (OSCCONbits.COSC != 0b001);       // Wait for Clock switch to occur

    // Wait for PLL to lock
    while(OSCCONbits.LOCK!=1) {};

    initTmr3();                             // Initialize the Timer to generate sampling event for ADC


    i=0;
        
    while(1)       // Loop Endlessly - Execution is interrupt driven
    {
                
    }


    return 0;
}

