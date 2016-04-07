    clc;
    clear all;
    close all;


% Agrego las funcines auxiliares al Workspace
    restoredefaultpath;
    addpath(genpath('../Funciones Auxiliares/'));


% Constantes
    fs = 22050;
    N = 2205000;
    P = nthroot(2,12);  % Relacion de frecuencias de interes
    P0 = 27.5;          % Frecuencia base en rad/seg
    %P0 = fs/N;


% Señal de entrada
    x = tono(P0*P^24, fs, N);


% Transformadas
    [fft_y fft_x] = FFT_abs(x, fs, N);
    [dpdt_y dpdt_x] = DPDT(x, fs, N, P0, P);
    
    
% Busco frecuencias comunes de la DPDT en la FFT
    for i=1:length(dpdt_x)
        [~, mx] = min(abs(fft_x-dpdt_x(i)));
        fft_y_nuevo(i) = fft_y(mx);
        fft_x_nuevo(i) = fft_x(mx);
    end;
    
    
% Ploteo
    figure;
    
    ax1 = subplot(311);
    stem(fft_x, fft_y);
    %title('FFT posta');
%     xlim([0 dpdt_x(end)]);
    
    ax2 = subplot(312);
    stem(fft_x_nuevo, fft_y_nuevo);
    %title('FFT descartando');
    
    
%     linkaxes([ax1 ax2], 'x');
%     
    
