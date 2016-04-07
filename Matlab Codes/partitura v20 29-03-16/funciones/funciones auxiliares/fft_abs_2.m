function [fft_x fft_y] = fft_abs_2(signal,Length,Fs)
% fft_abs devuelde el modulo de la fft al cuadrado de una se�al (densidad espectral de potencia) y su respectivo eje de frecuencias
%
% [fft_x fft_y] = fft_abs(signal, Length, Fs)
% signal:   Se�al de entrada
% Length:   Longitud del vector de entrada
% Fs:       Frecuencia de muestreo de la se�al de entrada
% [fft_x]:  Eje de frecuencias de la fft de la se�al
% [fft_y]:  Eje de modulo de la fft de la se�al
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_relativos, max_max_fft, mayores, plotFFT, tono, tono_con_armonicos.
%
% Version 1.0 01-10-2014

    L = Length;
    NFFT = 2^(nextpow2(L));
    
    
    signal_f = fft(signal,NFFT)/L;
    
    fft_x = Fs/2*linspace(0,1,NFFT/2+1);
    fft_y = abs(signal_f(1:int64(NFFT/2+1))).^2;
end