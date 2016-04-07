/*
    NOTAS:
            Debe terminarse de ingresar las constantes.
            Falta agregar la ventana.
*/


#define     ___FS                   22050                               // Frecuencia de sampleo
#define     ___WINDOW_LEN_DURAC     1024                                // Largo base del bloque de analisis de la duracion
#define     ___WINDOW_LEN_DETEC     2048                                // Largo base del bloque de analisis de la deteccion
#define     ___RESOLUCION_F_DETEC   ( ___WINDOW_LEN_DETEC / ___FS )     // Resolucion espectral de la FFT de la deteccion
#define     ___RESOLUCION_F_DURAC   ( ___WINDOW_LEN_DETEC / ___FS )     // Resolucion espectral de la FFT de la deteccion



//window = hanning(w_len,'periodic');
const fractional ___WINDOW =
{
};


typedef float fractional;




fractional VectorMax( int numElems, fractional* srcV, int* maxIndex );
