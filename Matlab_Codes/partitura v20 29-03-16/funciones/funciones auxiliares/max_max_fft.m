function [maximo] = max_max_fft(signal_t,Fs)
% max_max_fft Detecta el maximo entre los maximos de la fft de una señal
%
% [maximo] = max_max_fft(signal_t,Fs)
% signal_t:     Señal de entrada
% Fs:           Frecuencia de muestreo
% [maximo]:     Posicion del valor maximo
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_relativos, mayores, plotFFT, tono, tono_con_armonicos, tono_ruido.
%
% Version 1.0 01-10-2014

    [f d] = fft_abs(signal_t,length(signal_t),Fs);

    [potencia,I]=max(d);       % obtengo el mayor valor y el indice del vector
    maximo=f(I(1));          % posicion en el vector de frecuencias
end