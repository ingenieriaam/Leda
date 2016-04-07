/* 
 * File:   Flanger.h
 * Author: Usuario
 *
 * Created on 24 de abril de 2014, 14:03
 */

#include "../h/p33Fxxxx.h"
#include "dsp.h"

#ifndef FLANGER_H
#define	FLANGER_H

#define FLANGER_PASOS   20

#define LENGHTDELAY   NUMSAMP*FLANGER_PASOS
#define LENGHTFLANGER   NUMSAMP*FLANGER_PASOS
								// (LPRC can be disabled by clearing SWDTEN bit in RCON register
//extern fractional ENTRADA[LENGHTFLANGER];
//extern fractional FLANGER[LENGHTFLANGER];

void Init_flanger();

#endif	/* FLANGER_H */

