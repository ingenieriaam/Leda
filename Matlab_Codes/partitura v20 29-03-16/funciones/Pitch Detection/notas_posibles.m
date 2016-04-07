function [maximos_y, maximos_x] = notas_posibles(signal,max_ruido)
        
    maximos_y = 0;
    maximos_x = 0;
    if length(signal) < 2
        return;
    end
    
    for i = 1:length(signal)
        if signal(i) > max_ruido
                maximos_y = [maximos_y signal(i)];
                maximos_x = [maximos_x i];
        end
    end
    maximos_y = maximos_y(2:length(maximos_y));
    maximos_x = maximos_x(2:length(maximos_x));
    
end