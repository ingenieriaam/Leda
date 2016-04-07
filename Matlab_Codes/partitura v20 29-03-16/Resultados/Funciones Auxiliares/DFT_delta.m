function [ transformada, f ] = DFT_delta( signal,Fs,N,delta )
    % [ transformada, f ] = DFT_delta( signal,Fs,N,delta )
    % DFT_plot realiza la transformada de fourier de signal, se debe
    % disponer previamente de la matriz base de la trasformada.
    
    
    %% Calculo de la base de la DFT
    [b R] = base_DFT_delta(N, Fs, delta);
    
    M = delta*N;
    
    %% Calculo de la DFT
    transformada = (1/R)*(signal*b);
    transformada = transformada(1:M/2+1);
    
    
    %% Genero eje de frecuencias
    f = Fs/2*linspace(0,1,M/2+1); % creo vector de 0 a 1 a pasos de NDFT/2+1

    
end