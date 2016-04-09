/**********************************************************************
* © 2008 Microchip Technology Inc.
*
* FileName:        adcdacDrv.h
* Dependencies:    Other (.h) files if applicable, see below
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
#ifndef __ADCDRV1_H__
#define __ADCDRV1_H__

#include <p33EP256MU806.h>
#include "dsp.h"


// ************* DEFINES ************* //

// Sampling Control
#define Fosc                79227500
#define Fcy                 (Fosc/2)
#define Fs                  44211                   // 103160 //8038 //44211 //25000 // //Hz
#define SAMPPRD             (Fcy/Fs)-1
#define FSAMP               22050
#define MIN_FREC            2
#define LENGTHECO           2560
#define CANT_M              6                       // Cantidad de armonicos que analizo hacia abajo a partir del maximo
#define NUMSAMP             256                     // Cantidad de muestras del buffer de entrada de ping pong
#define NUMSAMP_DURACION    4*NUMSAMP               // Cantidad de muestras del buffer
#define NUMSAMP_DETECCION   8*NUMSAMP               // Cantidad de muestras del buffer
#define N_DPDT              103                     // Cantidad de muestras del buffer de la DPDT
#define INV_NUMSAMP         ((fractional) 0x0080)   // inversa de NUMSAMP: 0x0080 = 1/256; 0x0010 = 1/2048
#define PISO_COEF           ((fractional) 0x1000)   // coeficiente para el piso de ruido


// ************* CONSTANTES ************* //

extern const fractional _numeros_div[CANT_M];
extern const fractional _window[NUMSAMP];
extern unsigned char DmaBuffer;
extern char flag_DMA;

extern fractional in[NUMSAMP_DETECCION];

extern fractional BufferA[NUMSAMP] __attribute__((space(dma)));	// Ping-pong buffer A
extern fractional BufferB[NUMSAMP] __attribute__((space(dma)));	// Ping-pong buffer B

extern const fractional _base_DPDT_real[NUMSAMP][CANT_M]; 
extern const fractional _base_DPDT_imag[NUMSAMP][CANT_M];


// ************* FUNCIONES EN C ************* //

void DPDT(fractional *real_in, fractional *imag_in, fractional *real_out, fractional *imag_out);

void Get_buffer_in(char *cont);

void init_vectors(char num_bloque);

void initTmr3(void);

void piso_ruido();

void init_next_vectors();

char Duracion();

void init_pitch_vector(char *num_bloque);

    /* Encuentra la frecuencia fundamental
     *
     * fft_y: vector que contiene el eje y de la fft
     *
     * return: frecuencia fundamental
     */
fractional FindPitch();


// ************* FUNCIONES EN ASSEMBLER ************* //

    /* Genera un vector con el modulo de cada elemento del vector de entrada
     *
     * numElems:        Cantidad de elementos del vector
     * vect_out:        vector de salida
     * vect_in:         vector de entrada
     */
char asm_VectorMod(int numElems, fractional *vect_out, fractional *vect_in);

    /* Calcula la duracion de la nota
     *
     * fft_actual:      vector que contiene el eje y de la fft del bloque actual
     * fft_anterior:    vector que contiene el eje y de la fft del bloque anterior
     * piso_ruido:      nivel de piso de ruido
     *
     * return:          Flag de la duracion de la nota
     */
char asm_duracion(fractional *fft_actual, fractional *fft_anterior, fractional piso_ruido);

    /* Calcula la integral (discreta) del vector de entrada
     *
     * numElems:        Cantidad de elementos del vector
     * vector_in:       Vector el cual se quiere integrar      
     * 
     * return:      Devuelve la suma de todos los elementos del vector
     */
fractional asm_VectorInt(int numElems, fractional *vector);
    
    /* Devuelve un vector de los indices de las posibles frecuencias fundamentales
     *
     * vec_out:     Direccion del vector de salida
     * max_idx:     Indice del armonico de maxima amplitud
     * vec_invN:    Direccion del vector que contiene la inversa de los numeros naturales (asm_inverse_numbervec_findpitch)
     */
void asm_frec_posibles_armonicos(int *vec_out, fractional max_idx, const fractional *vec_invN);

    /* Calcula el nivel de piso de ruido
     *
     * fft_y: vector que contiene el eje y de la fft
     * coeficiente: coeficiente del piso de ruido al que multiplica
     *
     * return: piso de ruido
     */
fractional asm_piso_ruido(fractional *fft_y, fractional coeficiente);

    /* Calcula los indices de todos los maximos relativos
     *
     * maxrel_x:    vector de salida
     * fft_y:       vector que contiene el eje y de la fft
     * piso:        nivel de piso de ruido
     *
     * return: cantidad de maximos relativos
     */
int asm_maximos_relativos(int *maxrel_x, fractional *fft_y, fractional piso);

fractional FrecFundamental(fractional* maxrel_x,fractional* Ffund);

    /* Devuelve 1/numero
     *
     * numero:  Numero (entero) del que se quiere calcular la inversa
     *
     * return:  1/numero (en fractional)
     */
fractional asm_inverse_number(int numero);

    /* Calcula na inversa de los numeros naturales
     * 
     * inv_vector[n] = 1/(n-1); con n = 0, 1, 2, ..., (CANT_M - 1)
     */
void asm_inverse_numbervec_findpitch(fractional *inv_vector);


#endif

