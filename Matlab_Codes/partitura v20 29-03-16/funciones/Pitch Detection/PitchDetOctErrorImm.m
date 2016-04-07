clear all;close all;
    addpath('C:\Users\Agus\Dropbox\DPLabUTN\Audios algunos\8K');
    addpath('C:\Users\Agus\Dropbox\DPLabUTN\Audios algunos');
[in,fs] = audioread('fa2.wav');

w_len = 2048;

for i = 1:fix(length(in)/w_len)-1
    bloque=in((i*w_len)+1:(i+1)*w_len); % Bloque de 2048 a analizar
    sound(bloque,fs);           % Reproduzco el audio
    tic                     % tic-toc: para informarme cuanto tarda la funcion
    MIN_FREC = 80;          % Frecuencia mínima a detectar (guitarra:80)
    frec_Ffund = FindPitch(bloque,fs,MIN_FREC);
    toc
    
    waitforbuttonpress;
end