#include "../include/adcdacDrv.h"


fractional in[NUMSAMP_DETECCION];

fractional b_dur[NUMSAMP_DURACION];     // bloque de duracion actual
fractional b_dur_ant[NUMSAMP_DURACION]; // bloque de duracion anterior

fractional piso_de_ruido;


void Get_buffer_in(char *num_bloque)
{
    char aux = (*num_bloque); //Guardo numero de bloque actual para manejar mas facilmente
    
    if(DmaBuffer & 1)   //Se llenó el buffer A
    {
        VectorCopy(NUMSAMP, &(in[aux*NUMSAMP]), BufferA);  // Copio el bufer del DMA a la posicion mas vieja del buffer 'in'
    }
    else                //Se llenó el buffer B
    {
        VectorCopy(NUMSAMP, &(in[aux*NUMSAMP]), BufferB);  // Copio el bufer del DMA a la posicion mas vieja del buffer 'in'
    }

    (*num_bloque)++;    //Incremento numero de bloque actual
    (*num_bloque) %= (NUMSAMP_DETECCION/NUMSAMP);   //Buffer ciclico (Cuando llega al final, vuelve a cero)
}

void init_vectors(char num_bloque)
{
    // Copio bloque actual del buffer 'in' al buffer 'b_dur'
    if(num_bloque >= 4)
    {
        VectorCopy(NUMSAMP_DURACION, b_dur, &(in[(num_bloque-4)*NUMSAMP])); //Copio del bloque (actual - 4) hasta el bloque actual
    }
    else
    {
        char tam = num_bloque;  // Bloque actual
        
        VectorCopy(NUMSAMP*(4-tam), b_dur, &in[(num_bloque+4)*NUMSAMP]);    //Copio del bloque (actual + 4) hasta el final
        VectorCopy(NUMSAMP*tam, &b_dur[NUMSAMP*(4-tam)], in); //Y Copio del bloque 0 al actual
    }
    
    // Aplico ventaneo
    VectorWindow(NUMSAMP_DURACION, b_dur, b_dur, _window);   // Aplico ventaneo
    
    //fft(NUMSAMP_DURACION, b_dur, b_dur);               // Aplico fft
    b_dur[0] = 0;                                  // Elimino la continua de la FFT
}

void piso_ruido()
{
}

void init_next_vectors()
{
    VectorCopy(NUMSAMP, b_dur_ant, b_dur);   // Guardo bloque actual que luego se tomará como el bloque anterior
}

char Duracion()
{
    static char flag_nota = 0;          // 0: silencio - 1: se mantiene la nota - 2: nota nueva
    
    fractional frac_vector_1[NUMSAMP_DURACION];
    fractional frac_vector_2[NUMSAMP_DURACION];
    
    fractional frac_1;
    fractional frac_2;
    
    float f1, f2;
    
    
        // Divido bloque actual de fft X 2 para que no haya saturacion
    VectorScale(NUMSAMP_DURACION, b_dur, b_dur, 0x4000);          // fft_actual_aux = fft_actual/2;
    
    // Uso frac_1 para ver si la señal tiene mayor potencia que el piso de ruido
    frac_1 = asm_VectorInt(NUMSAMP_DURACION, b_dur); // frac_1 = sum(fft_actual_aux)
    if(frac_1 < piso_de_ruido)                     // SI frac_1 < piso_de_ruido, es silencio
    {
        return flag_nota = 0;
    }
    
        // fft_sub_aux = fft_actual/2 - fft_anterior/2
    VectorSubtract(NUMSAMP_DURACION, frac_vector_1, b_dur, b_dur_ant);
    
        // frac_1 = sum(fft_actual/2 - fft_anterior/2); PARAM_B
    frac_1 = asm_VectorInt(NUMSAMP_DURACION, frac_vector_1);
    
    if(frac_1 > 0) // SI Param_B es negativo, es porque decreció la señal. no hay nota nueva. sino, PUEDE haber nota nueva
    {
            // fft_sub_aux = mod(fft_actual/2 - fft_anterior/2);
        asm_VectorMod(NUMSAMP_DURACION, frac_vector_1, frac_vector_1);
        
            // frac_1 = sum(mod(fft_actual/2 - fft_anterior/2)); PARAM_A
        frac_1 = asm_VectorInt(NUMSAMP_DURACION, frac_vector_1);
        
            // fft_add_aux = fft_actual/2 + fft_anterior/2;
        VectorAdd(NUMSAMP_DURACION, frac_vector_2, b_dur, b_dur_ant);

            // frac_2 = sum(fft_actual/2 + fft_anterior/2); PARAM_C
        frac_2 = asm_VectorInt(NUMSAMP_DURACION, frac_vector_2);
        
        f1 = Fract2Float(frac_1);
        f2 = Fract2Float(frac_2);
        
        f1 = f1/f2;
        
        frac_1 = Float2Fract(f1);
        
        if(frac_1 > 0x4000)    // SI sum(mod(fft_actual/2 - fft_anterior/2))/sum(fft_actual/2 + fft_anterior/2) > 0.5 => Comienza la nota
        {
            return flag_nota = 2;
        }
    }
    if(flag_nota > 0)   // Si no hay mucha potencia pero no llega a ser silencio y ya hubo un comienzo de nota, se está manteniendo la ultima nota
    {
        return flag_nota = 1;
    }
    
    return flag_nota = 0;
    
}

void init_pitch_vector(char *num_bloque)
{
    // Copio los ultimos 4 bloques del buffer 'in' al comienzo del buffer 'in'
    if(num_bloque >= 4)
    {
        VectorCopy(NUMSAMP_DURACION, in, &(in[(num_bloque-4)*NUMSAMP])); //Copio del bloque (actual - 4) hasta el bloque actual
    }
    else
    {
        char tam = num_bloque;  // Bloque actual
        
        VectorCopy(NUMSAMP*tam, &in[NUMSAMP*(4-tam)], in); //Y Copio del bloque 0 al actual
        VectorCopy(NUMSAMP*(4-tam), in, &in[(num_bloque+4)*NUMSAMP]);    //Copio del bloque (actual + 4) hasta el final
    }
}

fractional FindPitch()
{
    int max_idx=0;                      // Indice del maximo
    int Ffund_idx[CANT_M];              // Indices de las posibles frecuencias fundamentales
    fractional piso;                    // Piso de ruido
    int maxrel_idx[NUMSAMP/2];          // Indices de todos los maximos relativos (como maximo pueden haber NUMSAMP/2 maximos relativos)
    int cant_maxrel;                    // Cantidad de maximos relativos
    fractional frec_Fundamental=8;        // Frecuencia fundamental


    // Halla la posicion en x del valor maximo de fft_y y lo almacena en index. Este valor maximo es
    // Una armonica de la frecuencia fundamental (si es que no es dicha frecuencia fundamental)
    // max_idx = max(fft_y)
    VectorMax(NUMSAMP, in, &max_idx);

    // Escribe en Ffund_idx los indices de las posibles frecuencias fundamentales.
    // Ffund_idx[n] = max_idx/(n+1), con n = 0, 1, 2, 3, 4...
    asm_frec_posibles_armonicos(Ffund_idx, max_idx, _numeros_div);

    piso = asm_piso_ruido(in, PISO_COEF);

    //Calcula todos los max relativos y los devuelve en maxrel_idx
    cant_maxrel = asm_maximos_relativos(maxrel_idx, in, piso);

    //Transformar los maxrel de x a frecuencia

    //

    //Halla la frecuencia fundamental
    frec_Fundamental = FrecFundamental(maxrel_idx,Ffund_idx);

    //Hacer la funcion deteccion...
    //

    return frec_Fundamental;
}

fractional FrecFundamental(fractional* maxrel_x,fractional* Ffund)
{
    int i,j;
    fractional aux;
    
    for(i=0; i<(NUMSAMP/2); i++)
    {
        aux = maxrel_x[i];
        if(aux > MIN_FREC)
        {
            for(j=0; j<CANT_M; j++)
            {
                if( (aux+1 > Ffund[j]) && (aux-1 < Ffund[j]) )
                {
                    return Ffund[j];
                }
            }
        }
    }

    return 0;
}


/*
fractional VectorInt(int numElements, fractional *vector)
{
    int i;
    fractional suma = 0;
    
    for(i=0; i<numElements; i++)
    {
        suma += vector[i];
    }
    
    return suma;
}
 * 
void DPDT_square (fractional* in,fractional *out)
{
    fractional real[M],imag[M];
    MatrixMultiply(1,NUMSAMP,M,real,in,real_base);
    MatrixMultiply(1,NUMSAMP,M,imag,in,imag_base);
    
    VectorMultiply(M,real_square,real,real);
    VectorMultiply(M,imag_square,imag,imag);
    VectorAdd(M,out,real_square,imag_square);
    
//    out = real^2 + imag^2;
}
*/

