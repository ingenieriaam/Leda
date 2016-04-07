/* 
 * File:   funciones_pre_assembler.h
 * Author: Usuario
 *
 * Created on 11 de junio de 2014, 11:44
 */

#ifndef FUNCIONES_PRE_ASSEMBLER_H
#define	FUNCIONES_PRE_ASSEMBLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "../h/p33Fxxxx.h"
#include "dsp.h"
#include "../h/adcdacDrv.h"
#include "libpic30.h"
#include <p33Fxxxx.h>

fractional* C_assembly_loopback(void);
fractional* C_assembly_ruido(void);
fractional* C_assembly_distorsion(void);
fractional* C_assembly_overdrive(void);
fractional* C_assembly_flanger(void);
fractional* C_assembly_flanger_triang(void);
fractional* C_assembly_delaylineinit(void);
fractional* C_assembly_FFT_Prueba_1(void);
fractional* C_assembly_FFT_Prueba_2(void);


#ifdef	__cplusplus
}
#endif

#endif	/* FUNCIONES_PRE_ASSEMBLER_H */

