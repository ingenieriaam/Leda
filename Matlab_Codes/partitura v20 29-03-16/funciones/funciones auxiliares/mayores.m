function [maximos_y, maximos_x] = mayores(signal,max_ruido)
% mayores Detecta los valores mayores de la fft de una señal a partir de un cierto valor de ruido
%
% [maximos_y, maximos_x] = mayores(signal,max_ruido)
% signal:       Señal de entrada
% max_ruido:    Nivel maximo de ruido (para eliminar el ruido)
% [maximos_y]:  Vector de valores mayores
% [maximos_x]:  Vector indices de valores mayores
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_relativos, max_max_fft, plotFFT, tono, tono_con_armonicos, tono_ruido.
%
% Version 1.0 01-10-2014

    maximos_y = [];
    maximos_x = [];
    if length(signal) < 2
        return;
    end
    
    start = 0;
    for i = 1:length(signal)
        if signal(i) > max_ruido
            if start == 1
                maximos_y = [maximos_y signal(i)];
                maximos_x = [maximos_x i];
            else
                maximos_y = signal(i);
                maximos_x = i;
                start = 1;
            end
        end
    end
end