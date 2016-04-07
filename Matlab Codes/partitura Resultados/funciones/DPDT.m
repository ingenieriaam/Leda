function [ transformada ] = DPDT( signal, fs, N, P0, P )
    %% MYDFT realiza la transformada de fourier de signal
    % se dispone previamente de la matriz base de la trasformada


    [b, R] = base_DPDT(N, fs, P0, P);
    
    %Elimino la constante a la señal de entrada
    signal = signal - mean(signal);
    
    %calculo de la dft
    transformada = (1/R)*(signal*b);
    
end