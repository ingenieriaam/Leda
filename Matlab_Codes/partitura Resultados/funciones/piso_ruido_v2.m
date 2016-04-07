function [ ruido ] = piso_ruido_v2( in,fs, w_len,coeficiente,min_frec)
%PISO_RUIDO halla un piso de ruido dinamico

[fft_x fft_y] = fft_abs(in(1:w_len),w_len,fs);

ruido = max(fft_y(fix(min_frec/fft_x(2)):end));

ruido = ruido*coeficiente;
  
end

