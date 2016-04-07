#include "../h/funciones_pre_assembler.h"
#include "../h/header_funciones_pre_assembler.h"

#include "../h/fft.h"
#include "../h/Flanger.h"

#include "math.h"


fractional* C_assembly_loopback()
{
    if(DmaBuffer == 1)
        assembly_loopback(&BufferC[0], &BufferA[0], NUMSAMP);
    else
        assembly_loopback(&BufferD[0], &BufferB[0], NUMSAMP);

    return 0x0000;
}

fractional* C_assembly_ruido()
{
    //Noise Gate

    if(DmaBuffer == 0)
        assembly_ruido(&BufferC[0],&BufferA[0],NUMSAMP);
    else
        assembly_ruido(&BufferD[0],&BufferB[0],NUMSAMP);

    return 0x0000;
}

fractional* C_assembly_distorsion()
{
    //DISTORSION 1.0

    if(DmaBuffer == 1)
        assembly_distorsion(&BufferC[0],&BufferA[0],NUMSAMP);
    else
        assembly_distorsion(&BufferD[0],&BufferB[0],NUMSAMP);

    return 0x0000;
}

fractional* C_assembly_overdrive()
{
    //OVERDRIVE

    if(DmaBuffer == 1)
        assembly_overdrive(&BufferC[0],&BufferA[0],NUMSAMP);
    else
        assembly_overdrive(&BufferD[0],&BufferB[0],NUMSAMP);

    return 0x0000;
}

fractional* C_assembly_flanger()
{

    return 0x0000;
}

fractional* C_assembly_flanger_triang()
{
//    //FLANGER TRIANGULAR 1.0
//
//    static int flanger_paso = FLANGER_PASOS-1;
//    static fractional DELAY_LINE[LENGHTDELAY];
//    static fractional DELAY_LINE_WET[LENGHTDELAY];
//
//    //VectorCopy:
//        //Program words: 13
//        //Cycles: 17 + 3(numElements)
//
//    if(DmaBuffer == 1)
//    {
//        assembly_flanger_triang(&BufferC[0], &BufferA[0], NUMSAMP, &DELAY_LINE[0], flanger_paso*NUMSAMP);
//        //VectorCopy(NUMSAMP, &DELAY_LINE_WET[flanger_paso*NUMSAMP], BufferC);
//    }
//    else
//    {
//        assembly_flanger_triang(&BufferD[0], &BufferB[0], NUMSAMP, &DELAY_LINE[0], flanger_paso*NUMSAMP);
//        //VectorCopy(NUMSAMP, &DELAY_LINE_WET[flanger_paso*NUMSAMP], BufferD);
//    }
//
//    flanger_paso--;
//    if(flanger_paso < 0) flanger_paso = FLANGER_PASOS-1;
//
    return 0x0000;
}

fractional* C_assembly_delaylineinit()
{

    return 0x0000;
}


extern void init_twiddleFactor(fractcomplex *twiddleFactors_real);
fractional* C_assembly_FFT_test()
{
    static fractcomplex twiddleFactors[FFT_BLOCK_LENGTH/2];
    static fractcomplex complex_output_vector[NUMSAMP];

    int i;

    static int init = 1;
    if(init)
    {
        init_twiddleFactor(twiddleFactors);
        init = 0;
    }

    if(DmaBuffer == 1)
    {
        assembly_fft_test(&BufferC[0],&BufferA[0],NUMSAMP, &twiddleFactors[0], complex_output_vector);
    }
    else
    {
        assembly_fft_test(&BufferD[0],&BufferB[0],NUMSAMP, &twiddleFactors[0], complex_output_vector);
    }

    for(i = NUMSAMP-1; i >= 0; i--)
    {
        BufferC[i] = sqrt(complex_output_vector[i].imag*complex_output_vector[i].imag + complex_output_vector[i].real*complex_output_vector[i].real);
    }

    return 0x0000;
}