/*
    NOTAS:
            Ya se termino de programar (falta probar).
*/

#define COEFICIENTE             0.05                                    // Coeficiente del piso de ruido
#define MIN_FREC                80                                      // Frecuencia minima que detecta (en Hz)
#define MIN_FREC_I              ( MIN_FREC / (___RESOLUCION_F_DETEC) )    // Indice de la frecuencia minima del largo del bloque de deteccion
#define IN_LEN                  ( ___WINDOW_LEN_DETEC - MIN_FREC_I )    // largo del bloque de la FFT desde MIN_FREC


#include "header.h"



/*  fractional piso_de_ruido(fractional *fft_y, int m_len len);
    halla un piso de ruido dinamico
    igual a 'coeficiente' del maximo

    fft_y:  Vector de la FFT
*/
fractional piso_de_ruido(fractional *fft_y)
{
    fractional ruido;   // Nivel de piso de ruido (valor de retorno de la funcion)
    int max_i;          // Indice del maximo


    fft_y = &(fft_y[MIN_FREC_I]); // Tomo solo las frecuencias superiores a MIN_FREC

    ruido = VectorMax( IN_LEN, fft_y, &max_i );

    ruido = ruido*COEFICIENTE;


    return ruido;
}














