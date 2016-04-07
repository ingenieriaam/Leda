/*
    NOTAS:
            Falta completar...
*/



#include "header.h"

void duracion(fractional *in)
{
    static bloque_ant[___W_LEN];
    static bloque_act[___W_LEN];
    static first = 1;               // Flag si es la primera vez que entra a la funcion


    if( first )
    {
        bloque_ruido = in( 1 : w_len );
        bloque_ruido = bloque_ruido .* window;
        [~, fft_y] = fft_abs(bloque_ruido,w_len,fs);
        ruido = sum(fft_y);
        ruido_2 = sum(fft_y.^2);
        flag_nota = 0;

        first = 0;
    }

}
