function Generador(filename, compas_numerador, compas_denominador, tempo, nota, duracion)
% Generador Genera un archivo MIDI
%
% Generador(filename, compas_numerador, compas_denominador, tempo, nota, duracion)
% filename:             Nombre del archivo MIDI de salida
% compas_numerador:     Numerador del compas
% compas_denominador:   Denominador del compas
% tempo:                Tempo de la cancion en [negras por minuto]
% nota:                 Vector de notas
% duracion:             Vector de duracion
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also generadorDP, duracionP, deteccion, detect_fundamental, figura, notas_to_midi.
%
% Version 1.0 01-10-2014

    duracion = figura(tempo,duracion); % Convierte la duración en segundos a la duracion en funcion de BeatsPerSecond (necesario para crear el midi) 

    nota = cellstr(nota); % Pongo las notas como vector de strings (lo requiere la funcion)

    nota = notas_to_midi(nota); % convierte las notas en lo que necesita la funcion
    
    if ~isvector(nota)
        error('Input(2) must be a vector')
    end
    if ~isvector(duracion)
        error('Input(3) must be a vector')
    end
    
    compas_denominador = log10(compas_denominador) / log10(2);  %Se necesita el _Log2(compas_denominador)_
    tempo = 60000000 / tempo;   %Para pasar de BPM(beats por minuto) a MPQN(microsegundos por quarter-note; quarter-note = negra)
    
    fp = fopen(filename,'w');

        %%DEFINES
            %%HEADER
                FORMATO_DE_PISTA_SINGLE_TRACK           =       '00';       %Solo un track
                FORMATO_DE_PISTA_MULTI_TRACK_SYNC       =       '01';       %Muchos tracks simultaneos
                FORMATO_DE_PISTA_MULTI_TRACK_ASYNC      =       '02';       %Muchos tracks secuenciales (muchos tracks del tipo 'single_track')

            %%EVENTOS
                META_EVENT                              =       'ff';
                NOTA_ON                                 =       '90';
                NOTA_OFF                                =       '80';

            %%META-EVENTOS
                COMPAS                                  =       '58';
                COMPAS_SIZE                             =       '04';
                TEMPO                                   =       '51';
                TEMPO_SIZE                              =       '03';
                END_OF_TRACK                            =       '2f';
                END_OF_TRACK_SIZE                       =       '00';


        %%CABECERA DEL ARCHIVO MIDI
    fwrite(fp,'MThd');                                                           	%"MThd"
    fwrite(fp, hex2dec('06'), 'ubit32', 0, 'ieee-be');                              %chunk length (size SOLO de la cabecera, a partir de lo siguiente)
    fwrite(fp, hex2dec(FORMATO_DE_PISTA_MULTI_TRACK_SYNC), 'ubit16', 0, 'ieee-be');	%Formato de pista
    fwrite(fp, hex2dec(['00' '01']), 'ubit16', 0, 'ieee-be');                    	%Numero de pistas o "tracks"
    fwrite(fp, hex2dec(['00' '08']), 'ubit16', 0, 'ieee-be');                    	%Division de tiempo: Indica el nï¿½mero de intervalos de tiempo contenidos
                                                                                    %en un cuarto de nota. Especifica asï¿½ el tempo de la reproducciï¿½n
                                                                                    %(ticks per beat).

        %%CABECERA DEL TRACK 1
    fwrite(fp,'MTrk');                                                              %"MTrk"
    fwrite(fp, 17+length(duracion)+7*length(nota), 'ubit32', 0, 'ieee-be');          	%size del track (a partir de lo siguiente)

        %%Evento
    fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                            	%Delta-time: tiempo de espera antes de ejecutar el evento
    fwrite(fp, hex2dec(META_EVENT), 'ubit8', 0, 'ieee-be');                         %META-EVENT
    fwrite(fp, hex2dec(COMPAS), 'ubit8', 0, 'ieee-be');                             %time signature: Compas
    fwrite(fp, hex2dec(COMPAS_SIZE), 'ubit8', 0, 'ieee-be');                        %size del META-EVENT
    fwrite(fp, compas_numerador, 'ubit8', 0, 'ieee-be');                             	%numerador (numero literal)
    fwrite(fp, compas_denominador, 'ubit8', 0, 'ieee-be');                             	%denominador (n): potencia de 2 denominador = 2^n
    fwrite(fp, hex2dec('18'), 'ubit8', 0, 'ieee-be');                              	%Pulso del metrï¿½nomo (96 = tick por cada redonda, 48 = tick por cada blanca, 18 = 3/16 = tick por cada 3 semi-corcheas)
    fwrite(fp, hex2dec('08'), 'ubit8', 0, 'ieee-be');                              	%Cantidad de fusas por cada negra_de_MIDI (24 seï¿½ales de clock del midi). DEJAR SIEMPRE EN 8

        %%Evento
    fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                             	%Delta-time: tiempo de espera antes de ejecutar el evento
    fwrite(fp, hex2dec(META_EVENT), 'ubit8', 0, 'ieee-be');                      	%META-EVENT
    fwrite(fp, hex2dec(TEMPO), 'ubit8', 0, 'ieee-be');                           	%Tempo setting: Tempo
    fwrite(fp, hex2dec(TEMPO_SIZE), 'ubit8', 0, 'ieee-be');                         %size del META-EVENT
    fwrite(fp, tempo , 'ubit24', 0, 'ieee-be');                                      %Microsegundos por negra(MPQN)



        %%NOTAS
    j=1;
    fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                             	%Delta-time: tiempo de espera antes de ejecutar el evento
    if nota(1) == -1
        fwrite(fp, hex2dec(NOTA_OFF), 'ubit8', 0, 'ieee-be');                        %Nota On
        fwrite(fp, nota(1), 'ubit8', 0, 'ieee-be');                                 %Altura de la nota (do-re-mi-etc)
        fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                           %Intensidad de la nota (apagado si es un LA_0)
    else
        fwrite(fp, hex2dec(NOTA_ON), 'ubit8', 0, 'ieee-be');                        %Nota On
        fwrite(fp, nota(1), 'ubit8', 0, 'ieee-be');                                 %Altura de la nota (do-re-mi-etc)
        fwrite(fp, hex2dec('40'), 'ubit8', 0, 'ieee-be');                           %Intensidad de la nota
    end
    fwrite(fp, duracion(j), 'ubit8', 0, 'ieee-be');                             	%Delta-time: tiempo de espera antes de ejecutar el evento
    %{
    durac = duracion(j);
    while durac >= 128
        if (durac - 128) >= 128
            fwrite(fp, rem(durac), 'ubit8', 0, 'ieee-be');                            	%Delta-time: tiempo de espera antes de ejecutar el evento
            durac = durac - 128;
        else
        end
    end
    %}
    
    j = j + 1;
    
    for i=2:length(nota)
        fwrite(fp, hex2dec(NOTA_OFF), 'ubit8', 0, 'ieee-be');                     	%Nota Off
        fwrite(fp, nota(i-1), 'ubit8', 0, 'ieee-be');                           	%Altura de la nota (do-re-mi-etc)
        fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                           %Intensidad de la nota
        fwrite(fp, 0, 'ubit8', 0, 'ieee-be');                                       %Delta-time: tiempo de espera antes de ejecutar el evento
        if nota(i) == -1
            fwrite(fp, hex2dec(NOTA_OFF), 'ubit8', 0, 'ieee-be');                        %Nota On
            fwrite(fp, nota(i), 'ubit8', 0, 'ieee-be');                                 %Altura de la nota (do-re-mi-etc)
            fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                           %Intensidad de la nota (apagado si es un LA_0)
        else
            fwrite(fp, hex2dec(NOTA_ON), 'ubit8', 0, 'ieee-be');                        %Nota On
            fwrite(fp, nota(i), 'ubit8', 0, 'ieee-be');                                 %Altura de la nota (do-re-mi-etc)
            fwrite(fp, hex2dec('40'), 'ubit8', 0, 'ieee-be');                           %Intensidad de la nota
        end
        fwrite(fp, duracion(j), 'ubit8', 0, 'ieee-be');                           	%Delta-time: tiempo de espera antes de ejecutar el evento
        j = j + 1;
    end

    fwrite(fp, hex2dec(NOTA_OFF), 'ubit8', 0, 'ieee-be');                     	%Nota Off
    fwrite(fp, nota(length(nota)), 'ubit8', 0, 'ieee-be');                           	%Altura de la nota (do-re-mi-etc)
    fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                           %Intensidad de la nota

        %%Evento
    fwrite(fp, hex2dec('00'), 'ubit8', 0, 'ieee-be');                             	%Delta-time: tiempo de espera antes de ejecutar el evento
    fwrite(fp, hex2dec(META_EVENT), 'ubit8', 0, 'ieee-be');                      	%META-EVENT
    fwrite(fp, hex2dec(END_OF_TRACK), 'ubit8', 0, 'ieee-be');                     %End of track
    fwrite(fp, hex2dec(END_OF_TRACK_SIZE), 'ubit8', 0, 'ieee-be');                %size del META-EVENT


    fclose(fp);
    
end