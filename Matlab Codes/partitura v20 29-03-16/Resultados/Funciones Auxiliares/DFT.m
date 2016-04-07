function [ transformada, f ] = DFT( signal,N,Fs )
    % [ transformada, f ] = DFT( signal,Fs,N )
    % DFT_plot realiza la transformada de fourier de signal, se debe
    % disponer previamente de la matriz base de la trasformada.
    
    %% Calculo de la base de la DFT
    [b R] = base_DFT(N, Fs);
    
    %% Calculo de la DFT
    transformada = (1/R)*(signal*b);
    transformada = transformada(1:N/2+1);
    
    
    %% Genero eje de frecuencias
    f = Fs/2*linspace(0,1,N/2+1); % creo vector de 0 a 1 a pasos de NDFT/2+1

    
end