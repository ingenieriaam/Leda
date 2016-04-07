function [maximo, potencia] = max_fft(signal_t,Fs,max_ruido)
% max_fft Detecta los valores mayores de un cierto valor de ruido de la fft de una señal
%
% [maximo, potencia] = max_fft(signal_t,Fs,max_ruido)
% signal_t:     Señal de entrada
% Fs:           Frecuencia de muestreo
% max_ruido:    nivel maximo de ruido (para eliminar el ruido)
% [maximo]:     Vector de valores maximos
% [potencia]:   Vector de potencia de cada valor maximo
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_relativos_fft, max_relativos, max_max_fft, mayores, plotFFT, tono, tono_con_armonicos, tono_ruido.
%
% Version 1.0 01-10-2014

    [f d] = fft_abs(signal_t,Fs);

    %% Deteccion de las 'cant_max' frecuencias mas altas

    [potencia,I]=mayores(d,max_ruido);       % obtengo el mayor valor y el indice del vector
    maximo=f(I);          % posicion en el vector de frecuencias
end