function [signal] = tono_ruido(f,Fs,L,ruido)
% tono_ruido Genera un tono puro con ruido 'random'
%
% [signal] = tono_ruido(f,Fs,L)
% f:        Frecuencia del tono en Hz
% Fs:       Frecuencia de muestreo
% L:        Tamano del bloque de entrada
% [signal]: Señal del tono con ruido
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_relativos, max_max_fft, mayores, plotFFT, tono, tono_con_armonicos.
%
% Version 1.0 01-10-2014

T = 1/Fs;                     % periodo de muestreo
t = (0:L-1)*T;                % vector de Tiempo en ms

% construccion del tono puro

w=2*pi*f;
signal=sin(w.*t)+ ruido*randn(size(t));