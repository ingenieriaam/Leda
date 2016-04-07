/* 
 * File:   header_funciones_pre_assembler.h
 * Author: Usuario
 *
 * Created on 11 de junio de 2014, 13:31
 */

#ifndef HEADER_FUNCIONES_PRE_ASSEMBLER_H
#define	HEADER_FUNCIONES_PRE_ASSEMBLER_H

#ifdef	__cplusplus
extern "C" {
#endif



//extern fractional* FIR ( int numSamps, fractional* dstSamps,fractional* srcSamps,FIRStruct* filter);
//extern fractional* assembly_loopback(fractional* dst,fractional* src,int numSamps);   //prototipo funcion asembly
//extern fractional* eco(fractional* dst,fractional* src,fractional* delayline,int numSamps);   //prototipo funcion asembly
extern fractional* assembly_loopback(fractional* ,fractional* ,unsigned int);   //prototipo funcion asembly
extern fractional* assembly_ruido(fractional* ,fractional* ,unsigned int);   //prototipo funcion asembly
extern fractional* assembly_distorsion(fractional* ,fractional* ,unsigned int);   //prototipo funcion asembly
extern fractional* assembly_overdrive(fractional* ,fractional* ,unsigned int);
extern fractional* assembly_flanger(fractional*, fractional*, unsigned int, fractional*, unsigned int, fractional*);
extern fractional* assembly_flanger_triang(fractional*, fractional*, unsigned int, fractional*, unsigned int);
extern fractional* assembly_delaylineinit(void);
extern fractional* assembly_fft_test(fractional* ,unsigned int, fractcomplex*, fractcomplex*);


extern fractional* assembly_complex_in(fractcomplex* ,fractional* ,unsigned int);   //prototipo funcion asembly
extern fractional* assembly_complex_out(fractional* ,fractcomplex* ,unsigned int);   //prototipo funcion asembly


extern fractional BufferA[NUMSAMP];			// Ping pong buffer A
extern fractional BufferB[NUMSAMP];			// Ping pong buffer B
extern fractional BufferC[NUMSAMP];			// Ping pong buffer C
extern fractional BufferD[NUMSAMP];			// Ping pong buffer D

extern unsigned int DmaBuffer;				// DMA flag



#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_FUNCIONES_PRE_ASSEMBLER_H */

