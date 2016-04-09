#include "dsp.h"
#include "../include/adcdacDrv.h"


// ********** INVERSA DE LOS NUMEROS NATURALES ************* //
// _numeros_div[n] = 1/(n-1); en fractional, con n = 0, 1, 2, ..., (CANT_M - 1)

#if CANT_M == 6
    const fractional _numeros_div[CANT_M] =
    {
        0x7FFF,
        0x4000,
        0x2AAA,
        0x2000,
        0x1999,
        0x1555
    };
#endif

#if NUMSAMP == 256
    const fractional _window[NUMSAMP] =
    {
        0x7FFF,
        0x4000,
        0x2AAA,
        0x2000,
        0x1999,
        0x1555
    };
#endif


// ********** TWIDDLE FACTORS ************* //
    
    
    


// ********** DPDT ************* //
    
    
#if NUMSAMP == 256
    #if CANT_M == 4
        const fractional _base_DPDT_real[NUMSAMP][CANT_M] =
        {
            {0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF},
            {0x4000, 0x7FFF, 0x7FFF, 0x7FFF},
        };
        
        const fractional _base_DPDT_imag[NUMSAMP][CANT_M] =
        {
            {0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF},
            {0x4000, 0x7FFF, 0x7FFF, 0x7FFF},
        };
    #endif
#endif