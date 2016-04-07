function [duracion_efectiva] = figura(tempo, duracion)
% figura Convierte de tiempo real de una nota a su respectiva figura dependiendo de las negras por minuto
%
% [duracion_efectiva] = figura(tempo, duracion)
% tempo:                Tempo de la cancion en [negras por minuto]
% duracion:             Vector de duracion de cada nota en [segundos]
% [duracion_efectiva]:  Vector de duracion de cada nota en su valor respectivo de acuerdo al tempo
%
% Por regla de 3 simple se vera la duracion de una negra para este tempo
%
% Duracion:
% 64 =   cuadrada
% 32 =   redonda
% 16 =   blanca
% 8  =   negra
% 4  =   corchea
% 2  =   semi-corchea
% 1  =   fusa (es el m�nimo)
%
% Ejemplo:
% negra con puntillo = negra + 1/2 negra = negra + corchea = 8 + 4 = 12
% blanca con puntillo = blanca + 1/2 blanca = blanca + negra = 16 + 8 = 24
%
% Maximo:
% 127(max) =   cuadrada + redonda + blanca + negra + corchea + semi-corchea + fusa
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also generadorDP, duracionP, deteccion, detect_fundamental, Generador, notas_to_midi.
%
% Version 1.0 01-10-2014
    
    negra = 60/tempo; % duracion de una negra en seg
    
    fusa = negra/8;
    
    l = length(duracion);

    for i = 1:l
        duracion_efectiva(i) = round(duracion(i)/fusa); %guardo "las fusas" de esa posicion
        if duracion_efectiva(i) > 127
            duracion_efectiva(i) = 127;
        end
    end
end