function [frec_Ffund] = FindPitch_v2(in,fs,piso_de_ruido,MIN_FREC)

% Halla la frecuencia fundamental del bloque de entrada
% in: bloque de entrada, debe ser de 2048 muestras; fs: frecuencia de muestreo;
% MIN_FREC: frecuencia mínima a detectar. En caso de la guitarra, 80.
% frec_Ffund: nota detectada en letras

Rangof = 0.05;


in_hann = in.*hann(length(in))';                        % Aplica una ventana Hann

in_hann_corr = xcorr(in_hann);                          % Y autocorrelaciona

[fft_in_hann_corr,f_corr] = plotFFT(in_hann_corr,fs);   % Obtiene la FFT y la grafica
[Fm_corr,Fm_x_corr] = max(fft_in_hann_corr);            % Calcula el maximo absoluto
f=f_corr(Fm_x_corr);                                    % Frecuencia en la que se ubica el maximo absoluto

d = floor(MIN_FREC/(fs/2048));                          % Distancia minima entre harmonicos
M = floor(f/d);                                         % El maximo absoluto va a ser menor a M*f0
Ffund = zeros(length(M));
for i=1:M
    Ffund(i+1) = f/i;                                   % Calculo los posibles valores de la f0
end

%piso_corr = Fm_corr*0.00005;                              % Determino un piso para no considerar el ruido
piso_corr = piso_de_ruido;

[max_y_corr,max_x_corr] = max_relativos(fft_in_hann_corr,piso_corr);

max_frec_corr=zeros(1,length(max_x_corr));              % Vector de frecuencias obtenidas de maximos relativos

for i=1:length(max_x_corr)
    max_frec_corr(i)=f_corr(max_x_corr(i));
end
frec_Ffundaux = 0;
entro = 1;                                              % Flag para salir del loop cuando encuentro la fundamental
for i=1:length(max_frec_corr)
    if entro
        if max_frec_corr(i)>MIN_FREC
            for j=1:length(Ffund)
                if (((max_frec_corr(i)*(1+Rangof) + 1) > Ffund(j)) && ((max_frec_corr(i)*(1-Rangof) - 1) < Ffund(j)))
                    frec_Ffundaux = Ffund(j);           % Si se condice algun valor de Ffund con un valor de los maximos 
                                                        % relativos (dentro de un entorno), entonces esa sera la fundamental,
                                                        % suponiendo que exista
                    entro = 0;
                end
            end
        end
    end
end
frec_Ffund = deteccion(frec_Ffundaux);

hold on
plot(ones(2048,1)*piso_de_ruido,'r');

end