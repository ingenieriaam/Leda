%% Init
    close all;
    clear all;
    clc;


%% Constantes
    n = 1024;
    fs = 22050;
    P = nthroot(2,12);
    P0 = 27.5;
    f0 = 880;  % Frecuencia a analizar
    
    
%% Ventanas
    h = hann(n);
    b = blackman(n);
    hn = hanning(n);
    hm = hamming(n);
    ft = flattopwin(n);

    
%% Señal a analizar
    x = tono(f0, fs, n);
        % Aplico ventaneo
    x_hann = x .* h' / mean(h);
    x_blackman = x .* b' / mean(b);
    x_hanning = x .* hn' / mean(hn);
    x_hamming = x .* hm' / mean(hm);
    x_flattop = x .* ft' / mean(ft);

    
%% Transformada DPDT    
    DPDT_x = DPDT(x, fs, n, P0, P);
    DPDT_hann = DPDT(x_hann, fs, n, P0, P);
    DPDT_blackman = DPDT(x_blackman, fs, n, P0, P);
    DPDT_hanning = DPDT(x_hanning, fs, n, P0, P);
    DPDT_hamming = DPDT(x_hamming, fs, n, P0, P);
    DPDT_flattop = DPDT(x_flattop, fs, n, P0, P);
    
    t_DPDT_x = P0*(P.^(0:(length(DPDT_x)-1)));
    
    
%% Transformada FFT
    [t_FFT_x, FFT_x] = fft_abs(x, n*128, fs);
    [~, FFT_hann] = fft_abs(x_hann, n*128, fs);
    [~, FFT_blackman] = fft_abs(x_blackman, n*128, fs);
    [~, FFT_hanning] = fft_abs(x_hanning, n*128, fs);
    [~, FFT_hamming] = fft_abs(x_hamming, n*128, fs);
    [~, FFT_flattop] = fft_abs(x_flattop, n*128, fs);
    
    
%% ploteo FFT
    figure;
    hold all;
    
    %set(gcf, 'Title', 'FFT');
    
    plot(t_FFT_x, FFT_x);
    plot(t_FFT_x, FFT_hann);
    plot(t_FFT_x, FFT_blackman);
    plot(t_FFT_x, FFT_hanning);
    plot(t_FFT_x, FFT_hamming);
    plot(t_FFT_x, FFT_flattop);
    
    legend('rectangular', 'Hann', 'Blackman', 'Hanning', 'Hamming', 'FlatTop');
    
    xlim([f0-fs/50 f0+fs/50]);
    
    
%% ploteo DPDT
    figure;
    hold all;
    
    %set(gcf, 'Title', 'DPDT');
    
    plot(t_DPDT_x, abs(DPDT_x));
    plot(t_DPDT_x, abs(DPDT_hann));
    plot(t_DPDT_x, abs(DPDT_blackman));
    plot(t_DPDT_x, abs(DPDT_hanning));
    plot(t_DPDT_x, abs(DPDT_hamming));
    plot(t_DPDT_x, abs(DPDT_flattop));
    
    legend('rectangular', 'Hann', 'Blackman', 'Hanning', 'Hamming', 'FlatTop');
    
    xlim([f0-fs/50 f0+fs/50]);
    
    
    
    
    