function plotFFT2(signal,fs)
% plotFFT Plotea el cuadrado de la FFT de una señal (Densidad Espectral de
% potencia)
%
% plotFFT(signal,fs)
% signal:   Vector de notas
% fs:       Vector de notas
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also max_fft, max_relativos_fft, max_relativos, max_max_fft, mayores, tono, tono_con_armonicos, tono_ruido.
%
% Version 1.0 01-10-2014

    L = length(signal);
    NFFT = 2^nextpow2(L);
    fft_s = fft(signal,NFFT)/L;
    f = fs/2*linspace(0,1,NFFT/2+1);
    % Plot single-sided amplitude spectrum.
    semilogx(f,(abs(fft_s(1:NFFT/2+1)).^2)), axis tight,xlim([1 20000]),grid;
    set(gca,'XTickLabel',{'1','10','100','1K','10K'});
    title('Single-Sided Amplitude Spectrum of s(t)');
    xlabel('Frequency (Hz)');
    ylabel('|S(f)|');
end