function [notasnum, notasname, duracion] = partitura_v20(filename, est_dur, piso_dur, piso_detec, do_plot, plot_detec)
%% [notasnum, notasname, duracion] = partitura_v20(filename, do_plot, do_detec)
%
%   [notasnum]:     Numero de cada nota MIDI (69 = LA_4)
%   [notasname]:    Nombre de cada nota MIDI
%   [duracion]:     Duración de cada nota MIDI (en segundos)
%   est_dur:        Estimador para usar en la duración
%   piso_dur:       Piso de ruido para usar en la duración
%   piso_detec:       Piso de ruido para usar en la detección
%   filename:       Nombre del archivo de audio


%% ******** INICIALIZACION ********** %
    if ~exist('plot_detec', 'var');
        do_plot = false;
    end;
    
    if ~exist('plot_detec', 'var');
        plot_detec = false;
    end;
    

    % Agrego las rutas a usar al Workspace
    %restoredefaultpath;
    addpath(genpath('../../3- Audio files/'));  % Ruta de funciones auxiliares *.m
    addpath(genpath('./funciones/'));           % Ruta de funciones auxiliares *.m
    
    %filename = 'lldhyem.wav';
    %filename = 'b_8_k.wav';
    %filename = 'G_2_8k';
    %filename = 'jijiji.wav';
    %filename = 'mas_arriba';
    %filename = 'aun_ma_rriba.wav';
    %filename = 'dosYdosOctavasDo.wav';
    %filename = 'test120nps_22k.wav';
    %filename = 'test120nps.wav';
    %filename = 'narananana.wav';
    %filename = 'Mi major.wav';
    %filename = 'mop.wav';
    %filename = 'ac.wav';
    %filename = 'miMbass.wav';
    %filename = 'miM2bass.wav';
    %filename = 'av.wav';
    %filename = 'armonica.wav';
    %filename = 'saxo.wav';
    %filename = '5.wav';
    %filename = 'bajo_2.wav';
    %filename = 'melody_voice_1.wav';
    
    
    % carga de archivo
    [in, fs] = wavread(filename);
    in = in(:,1);
    in = resample(in, 22050, fs, 1024);
    fs = 22050;
    %n=0.025*randn(length(in),1);
    %in=in+n;
    % Asignacion de valores a las variables intervinientes en funcion de
    % las caracteristicas del archivo
    
    % window_len es cantidad de muestras a analizar (bloque)
    % salto es el desplazamiento respecto a la primer muestra del bloque
    % analizado con anterioridad, a partir del cual se comforma el segundo
    % bloque de analisis
    if fs == 44100
        window_len = 2048;  % puede funcionar con 4096 (y salto de 1024)
    elseif fs == 22050
        window_len = 512;  % puede funcionar con 4096 (y salto de 1024)
    else %if fs == 8000
        window_len = 1024;
    end
    
    
    in = in(:,1);                           % se toma un solo canal
    in = in / max(abs(in));                 % escalamiento entre -1 y 1
    in = Complete_vector(in', window_len)'; % zero padding hasta que el largo de in sea divisible por window_len
    
    
%% ******** DURACION ********** %

    nota = [];                                              % guarda 2, 1 o 0 indicando Ataque, Sustain y Silencio
    nota_x = [];                                            % guarda las posiciones de los eventos antedichos

    len_deteccion = 2756;
    k=1;
    dur_inicio=0;
    dur_fin=0;
    in_detect = zeros(len_deteccion, 1);
    in_detect_x = zeros(1,1);
    duracion = [];
    nota_idx = 1;
    nota_idx_inicio = 1;
    
    if do_plot==true
        figure;
        
        set(gcf,'name',filename,'NumberTitle','off');

        plot(in,'r');
        xlim([0 length(in)]);
        hold on;
    end;
    
    %% organizacion de bloques 
    % para graficos y envio de datos a la funcion de deteccion
    for i = 0:(length(in)/window_len)-10     
        clc;
        aux = dur_prueba(in, i, window_len, est_dur, piso_dur, 0);   % Algoritmo que estima la duracion (carpeta funciones)
        if i==0
            aux = 0;
        end
        if (aux == 2) || (aux == 0 && dur_inicio ~= 0)
            if nota(end) == 2
                aux = 1;
            else                
                if dur_inicio == 0
                    dur_inicio = (window_len*i);
                    nota_idx_inicio = nota_idx;
                else
                    dur_fin = (window_len*i);
                    if (dur_fin-dur_inicio) > window_len*2
                        duracion(k) = (dur_fin-dur_inicio)/fs;
                        in_detect_x(k) = dur_inicio;
                        in_detect(:,k) = in(in_detect_x(k):in_detect_x(k)+len_deteccion-1,1);
                        k = k+1;
                    else
                        nota(nota_idx_inicio:nota_idx) = zeros(1, nota_idx-nota_idx_inicio+1);
                    end
                    dur_inicio = 0;
                end
                if aux == 2
                    nota(end) = 0;
                    dur_inicio = (window_len*i);
                    nota_idx_inicio = nota_idx;
                end
            end
        elseif aux == 1 && nota(end) == 0
            aux = 0;
        end

        nota(nota_idx) = aux;                              % Concatenacion de eventos
        nota_x(nota_idx) = (window_len*i);         % Concatenacion de las posiciones de ocurrencia de los eventos
        nota_idx = nota_idx + 1;

    end
    
    
%% ******** PLOT DURACION ********** %

    if do_plot==true
        plot(nota_x, nota,'--');
        xlim([0 length(in)]);
        
        stem(in_detect_x, ones(length(in_detect_x),1),'g');
        xlim([0 length(in)]);

        legend('Señal de audio', 'Duración de la nota', 'Comienzo de la nota');
        xlabel('Número de muestras', 'FontSize', 15);
        ylabel('Amplitud [V]', 'FontSize', 15);
    end;
    

%% ******** SELECCION DE BLOQUES PARA DETECCION DE TONO ******** %
% La deteccion del tono depende integramente de la estabilidad de la
% informacion del bloque a analizar queriendose evitar sectores con ataques
% o decaimiento, el siguiente proceso seleccionara dichos bloques
% para facilitar la estimacion del tono
    
    
%% ********* DETECTOR ************ %
[~,n_notas] = size(in_detect);

notasnum = [];
notasname = [];


N = len_deteccion;
P = nthroot(2,12);  % Relacion de frecuencias de interes
P0 = 27.5;         % Frecuencia base en rad/seg
[base, normalizacion] = base_DPDT(N,fs, P0*2*pi, P);

for index=1:n_notas
    [notaname,notanum] = FindPitch_DPDT(in_detect(:,index)',fs,80,base, normalizacion, piso_detec, plot_detec);   % llamado a deteccion de tono (carpeta funciones\Pitch Detection)
    
    if (plot_detec == true) && (strcmp(notaname,'none') == 0)
        title(['Espectro: ' num2str(notaname) ', index: ' num2str(index)]);
    end;
    
    notasnum = [notasnum notanum];
    notasname = char(notasname, notaname);
end


%% ********* Generador de MIDI ************ %

Generador([filename '.mid'], 4, 4, 200, notasname(2:length(duracion)+1, :), duracion);





