function [signal] = tono_con_armonicos(f,Fs,L,depth,cant_arm)
% tono_con_armonicos Genera un tono con armonicos
%
% [signal] = tono_con_armonicos(f,Fs,L,depth,cant_arm)
% f:        Frecuencia del tono en Hz
% Fs:       Frecuencia de muestreo
% L:        Tamaño del bloque de entrada
% depth:    Profundidad de armonicos
% cant_arm: Cantidad de armonicos
% [signal]: Señal del tono con armonicos
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_relativos, max_max_fft, mayores, plotFFT, tono, tono_ruido.
%
% Version 1.0 01-10-2014

T = 1/Fs;                     % periodo de muestreo
t = (0:L-1)*T;                % vector de Tiempo en ms

% construccion del tono con armonicos

w=2*pi*f;
signal=sin(w.*t);

k = 0;
while w < 2*pi*(Fs/2)
    if k < cant_arm
        k = k+1;
        w = w + w;
        signal= signal + sin(w*t)*(depth^k);
    else
        return
    end
end
