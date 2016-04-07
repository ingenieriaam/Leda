function [frec_Ffund,numnota] = FindPitch_DPDT(in,fs,MIN_FREC,base, normalizacion, do_plot)

    % Halla la frecuencia fundamental del bloque de entrada
    % in: bloque de entrada, debe ser de 2048 muestras; fs: frecuencia de muestreo;
    % MIN_FREC: frecuencia mÃ­nima a detectar. En caso de la guitarra, 80.
    % frec_Ffund: nota detectada en letras


    N = length(in);             % Largo del bloque de entrada
    P = nthroot(2,12);          % Relacion de frecuencias de interes
    %P0 = 6.875;                % Frecuencia base en rad/seg
    P0 = 27.5;                  % Frecuencia base en rad/seg
    in = in - mean(in);         % Saco la continua de la señal

    transformada = (1/normalizacion)*(in*base);         % Calculo la transformada multiplicando vectorialmente

    PSD = abs(transformada).^2;                         % Calculo la Densidad Espectral de Potencia (PSD)

    i = 0:length(transformada)-1;
        PSD_x(i+1) = P0*P.^i;                           % Defino el eje X de la transformada


    piso_de_ruido = piso_ruido(PSD, PSD_x, 0.4);


    [PSD_max,PSD_max_x] = max(PSD);                             % Calcula el maximo absoluto
    Fmax = PSD_x(PSD_max_x);                                    % Frecuencia en la que se ubica el maximo absoluto

    M = 4;                                                      % El maximo absoluto va a ser menor a M*f0
    Ffund = zeros(length(M));
    for i=0:M-1
        Ffund(i+1) = Fmax/(M-i);                                    % Calculo los posibles valores de la f0
    end


%    [max_rel_y,max_rel_x] = max_relativos(PSD,piso_de_ruido);   % Vector de indices obtenidos de maximos relativos
    [max_rel_y,max_rel_x] = notas_posibles(PSD,piso_de_ruido);   % Vector de indices obtenidos de maximos relativos

    Fmax_rel_x = zeros(1,length(max_rel_x));                    % Vector de frecuencias obtenidas de maximos relativos

    for i=1:length(max_rel_x)
        if max_rel_x(i) ~= 0
            Fmax_rel_x(i)=PSD_x(max_rel_x(i));                  % Se carga el vector de frecuencias obtenidas de maximos relativos
        end
    end

    frec_Ffund = 0;             % Frecuencia fundamental a hallar

    entro = 1;                  % Flag para salir del loop cuando encuentro la fundamental
    for i=1:length(Fmax_rel_x)
        if entro
            if Fmax_rel_x(i)>MIN_FREC
                for j=1:length(Ffund)
                    if( abs(Fmax_rel_x(i) - Ffund(j)) < 1 )
                        frec_Ffund = Fmax_rel_x(i);         % Si se condice algun valor de Ffund con un valor de los maximos 
                                                            % relativos, entonces esa sera la fundamental,
                                                            % suponiendo que exista
                        entro = 0;
                        break;
                    end
                end
            end
        else
            break;
        end
    end

    [frec_Ffund,numnota] = deteccion(frec_Ffund);   % Traduce la frecuencia fundamental a "nota"
    
    if (do_plot == 1) && (strcmp(frec_Ffund,'none') == 0)
        figure;
        stem(PSD_x, PSD);
        hold on;
        plot(1:PSD_x(end), ones(1,PSD_x(end))*piso_de_ruido, '--');
        hold off;
    end;

end




