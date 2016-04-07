function [signal_out] = decimacion(signal_in,decim)
% decimacion Decima una señal descartando muestras (sin filtro)
%
% [signal_out] = decimacion(signal_in,decim)
% signal_in:    señal de entrada
% decim:        Decimacion que se quiere aplicar
% [signal_out]: señal decimada
%
% For more information, see <a href="https://sourceforge.net/p/dplabaudio/wiki/Home/">Wiki del DPLab-Audio</a>.
%
% See also generadorDP, duracionP, deteccion, figura, Generador, notas_to_midi.
%
% Version 1.0 01-10-2014

    L = length(signal_in);

    signal_out = zeros(1,L);

    for k = 1:L/decim
        signal_out(k) = signal_in(decim*k-(decim-1));
    end
end