function [ transformada, f ] = DFT_delta_DPDT( signal,Fs,N,delta,t,tf )
    % [ transformada, f ] = DFT_delta_DPDT( signal,Fs,N,delta,t,tf )
    % DFT_plot realiza la transformada de fourier de signal, se debe
    % disponer previamente de la trasformada.
    
    
    P = nthroot(2,12);  % Relacion de frecuencias de interes
    P0 = 27.5;          % Frecuencia base en rad/seg
    
    M = fix(log((Fs/2)/(P0))/log(P));   % Calculo M (segunda dimension de la base)
    
    transformada = zeros(1, M);
    f = zeros(1, M);
    
    for i=1:M
        fi = P0*P^(i-1);
        [~, mx] = min(abs(tf-fi));
        transformada(i) = t(mx);
        f(i) = tf(mx);
    end;

    
end