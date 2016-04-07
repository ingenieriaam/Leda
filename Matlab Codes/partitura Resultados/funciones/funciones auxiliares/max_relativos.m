function [maximos_y, maximos_x] = max_relativos(signal, minimo)
% max_relativos Detecta los maximos relativos de la fft de una se�al
%
% [maximos_y, maximos_x] = max_relativos(signal, minimo)
% signal:       se�al de entrada
% minimo:       minimo maximo que detecta
% [maximos_y]:  Vector de maximos relativos
% [maximos_x]:  Vector de indices de los maximos relativos
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_max_fft, mayores, plotFFT, tono, tono_con_armonicos, tono_ruido.
%
% Version 1.0 01-10-2014

    maximos_y = zeros(length(signal),1);
    maximos_x = zeros(length(signal),1);
    signal = signal(:,1);
    if length(signal) < 2
        return;
    end
    
    start = 0;
  % Detecto maximos relativos
    for i = 1:length(signal)
        if signal(i) < minimo
            continue;
        end
        if i == 1
            if signal(1) > signal(2)
                maximos_y = signal(1);
                maximos_x = 1;
                start = 1;
            end
        else
            if i == length(signal)
                if signal(i) > signal(i-1)
                    if start == 1
                        maximos_y = [maximos_y signal(i)];
                        maximos_x = [maximos_x i];
                    else
                        maximos_y = signal(i);
                        maximos_x = i;
                        start = 1;
                    end
                end
            else
                if signal(i) > signal(i+1) && signal(i) > signal(i-1)
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
    end
end