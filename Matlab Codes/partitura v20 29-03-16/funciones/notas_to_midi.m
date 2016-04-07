function out = notas_to_midi(notas)
% notas_to_midi Convierte las notas de su nombre al numero por el que es identificado por el MIDI
%
% notas_to_midi(notas)
% notas:       Vector de notas
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also generadorDP, duracionP, deteccion, detect_fundamental, figura, Generador.
%
% Version 1.0 01-10-2014

    out = 1:length(notas);
    for i = 1:length(notas)
        aux = char(notas(i));
        
            %%DETERMINA SILENCIO
        if strncmpi(aux, 'none', 4)
            out(i) = -1;
        else
            
                %%DETERMINA LA NOTA
            if strncmpi(aux, 'do_', 3)
                out(i) = 0;
            elseif strncmpi(aux, 'do#', 3)
                out(i) = 1;
            elseif strncmpi(aux, 're_', 3)
                out(i) = 2;
            elseif strncmpi(aux, 're#', 3)
                out(i) = 3;
            elseif strncmpi(aux, 'mi_', 3)
                out(i) = 4;
            elseif strncmpi(aux, 'fa_', 3)
                out(i) = 5;
            elseif strncmpi(aux, 'fa#', 3)
                out(i) = 6;
            elseif strncmpi(aux, 'so_', 3)
                out(i) = 7;
            elseif strncmpi(aux, 'so#', 3)
                out(i) = 8;
            elseif strncmpi(aux, 'la_', 3)
                out(i) = 9;
            elseif strncmpi(aux, 'la#', 3)
                out(i) = 10;
            else
                out(i) = 11;
            end

                %%DETERMINA LA OCTAVA
            if ~isempty(strfind(aux, '0'))
                out(i) = out(i) + 12;
            elseif ~isempty(strfind(aux, '1'))
                out(i) = out(i) + 12*2;
            elseif ~isempty(strfind(aux, '2'))
                out(i) = out(i) + 12*3;
            elseif ~isempty(strfind(aux, '3'))
                out(i) = out(i) + 12*4;
            elseif ~isempty(strfind(aux, '4'))
                out(i) = out(i) + 12*5;
            elseif ~isempty(strfind(aux, '5'))
                out(i) = out(i) + 12*6;
            elseif ~isempty(strfind(aux, '6'))
                out(i) = out(i) + 12*7;
            elseif ~isempty(strfind(aux, '7'))
                out(i) = out(i) + 12*8;
            elseif ~isempty(strfind(aux, '8'))
                out(i) = out(i) + 12*9;
            elseif ~isempty(strfind(aux, '9'))
                out(i) = out(i) + 12*10;
            end
            
        end
    end
end