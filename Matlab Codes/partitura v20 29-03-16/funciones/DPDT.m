function [ transformada ] = DPDT( signal, b, R, Fs, N, P0, P, factor )
    %% MYDFT realiza la transformada de fourier de signal
    % se dispone previamente de la matriz base de la trasformada


    %Elimino la constante a la señal de entrada
    signal = signal - sum(signal)/N;
    
    Ts=1/Fs;
    t=0:(1/Fs):((N-1)*Ts);
    %calculo de la dft
    transformada = (1/R)*(signal*b);
    
    i = 0:length(transformada)-1;
        f(i+1) = P0*P.^i; % creo vector de 0 a 1 a pasos de NDFT/2+1
    
    figure(1);
    subplot(311);
        plot(t,signal);
        title('señal bajo estudio');
    % subplot(312);stem(f,2*abs(transformada(1:n/2+1)/n))
    subplot(312);
        stem(f,abs(transformada).^factor);
        title('transformada discreta de D´Angelo');
        xlabel('frecuencia en Hz');
        ylabel('modulo');

    %% opcional para el estudio de fase
    y = transformada;                            % Compute DFT of x
    p = unwrap(angle(y));                  % Phase
    f = (0:length(y)-1)/length(y)*100;     % Frequency vector
    subplot(313);stem(f,p)
    xlabel ('frecuencia en Hz')
    ylabel ('fase en radianes')
    
end