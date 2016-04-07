function y_corr = mi_xcorr(x1, x2, ploteo, tiempo_ploteo)

if (~exist('ploteo', 'var'))
    ploteo = 0;
end
if (~exist('tiempo_ploteo', 'var'))
    tiempo_ploteo = 0;
end

    x1 = x1(:,1);
    x2 = x2(:,1);
    
    if length(x1) > length(x2)
        N = length(x1);
        aux = x2;
        x2 = [x1 zeros(N-length(x1),1)];
        x1 = aux;
    else
        N = length(x2);
        if length(x2) > length(x1)
            x1 = [x2 zeros(N-length(x1),1)];
        end
    end
    
    y_corr = zeros(N,1);
    
    if N > 1
        if ploteo == 1
            figure;
            subplot(311);
            plot(x1);
        end
        
        x1 = x1 - sum(x1)/N;
        x2 = x2 - sum(x2)/N;
        norm = sqrt(sum(x1.^2)*sum(x2.^2));
        
        for k = 1:N
            if k > 1
                x2 = [x2(end); x2(1:end-1)];
            end
            
            if norm == 0
                y_corr = ones(N,1);
            else
                y_corr(k:end) = (sum(x1.*x2) / norm) .* ones(N-k+1,1);
            end
            
            if ploteo == 1
                subplot(312);
                plot(x2);
                subplot(313);
                plot(y_corr);
                if norm == 0
                    break;
                end
                pause(tiempo_ploteo/N);    % Espera n segundos
            end
        end
    end

end