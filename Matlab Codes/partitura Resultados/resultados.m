%% Init
    clc;
    clear all;
    close all;

    % Agrego las rutas a usar al Workspace
    restoredefaultpath;
    
    addpath(genpath('../../3- Audio files/'));  % Ruta de funciones auxiliares *.m
    addpath(genpath('../partitura v20 29-03-16/'));           % Ruta de funciones auxiliares *.m
    
    
%% Definir Parámetros
    est_dur = 0.2;      % Estimador para usar en la duración (0 < est_dur < 1)  
    piso_dur = 100;     % Piso de ruido para usar en la duración (1 < piso_dur)
    piso_detec = 0.4;   % Piso de ruido para usar en la detección (coeficiente que multiplica la media espectral)
    
        % Nombre de los audios (sin la letra de instrumento)
    filenames = {'cantata.wav'; 'jijiji.wav'; 'mario.wav'; 'MiMayor2a4'; 'MiMayor3a5'; 'MiMayor5a6'};
    
    cant_inst = 2;          % Cantidad de instrumentos
    inst_start = {'P' 'G'}; % Letra que identifica a cada instrumento
    
    
%% Agrega letra de instrumento a los nombres de archivo de los audios
        % Establece tamaño de la matriz
    filenames_inst{size(filenames, 1), cant_inst} = {};
    
    for i=1:size(filenames, 1)
        for j=1:cant_inst
            filenames_inst{i,j} = {[inst_start{1,j} filenames{i,1}]};
        end;
    end;
    
    
%% Crea el MIDI
        % Establece tamaño de las matrices
        [~, detectado_Cantata_Guitarra, ~] = partitura_v20(char(filenames_inst{1,1}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_Jijiji_Guitarra, ~] = partitura_v20(char(filenames_inst{2,1}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_Mario_Guitarra, ~] = partitura_v20(char(filenames_inst{3,1}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_MiMayor2a4_Guitarra, ~] = partitura_v20(char(filenames_inst{4,1}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_MiMayor3a5_Guitarra, ~] = partitura_v20(char(filenames_inst{5,1}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_MiMayor5a6_Guitarra, ~] = partitura_v20(char(filenames_inst{6,1}), est_dur, piso_dur, piso_detec, false, false);
        
        [~, detectado_Cantata_Piano, ~] = partitura_v20(char(filenames_inst{1,2}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_Jijiji_Piano, ~] = partitura_v20(char(filenames_inst{2,2}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_Mario_Piano, ~] = partitura_v20(char(filenames_inst{3,2}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_MiMayor2a4_Piano, ~] = partitura_v20(char(filenames_inst{4,2}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_MiMayor3a5_Piano, ~] = partitura_v20(char(filenames_inst{5,2}), est_dur, piso_dur, piso_detec, false, false);
        [~, detectado_MiMayor5a6_Piano, ~] = partitura_v20(char(filenames_inst{6,2}), est_dur, piso_dur, piso_detec, false, false);
    
    
    
%% Compara cada MIDI detectado contra el real
    %% Cargo Patrones
        load('Notas_Cantata_Guitarra.mat');
        load('Notas_Jijiji_Guitarra.mat');
        load('Notas_Mario_Guitarra.mat');
        load('Notas_MiMayor2a4_Guitarra.mat');
        load('Notas_MiMayor3a5_Guitarra.mat');
        load('Notas_MiMayor5a6_Guitarra.mat');

        load('Notas_Cantata_Piano.mat');
        load('Notas_Jijiji_Piano.mat');
        load('Notas_Mario_Piano.mat');
        load('Notas_MiMayor2a4_Piano.mat');
        load('Notas_MiMayor3a5_Piano.mat');
        load('Notas_MiMayor5a6_Piano.mat');
    
    %% Guardo Variables detectadas
        save('detectado_Cantata_Guitarra.mat', 'detectado_Cantata_Guitarra');
        save('detectado_Jijiji_Guitarra.mat', 'detectado_Jijiji_Guitarra');
        save('detectado_Mario_Guitarra.mat', 'detectado_Mario_Guitarra');
        save('detectado_MiMayor2a4_Guitarra.mat', 'detectado_MiMayor2a4_Guitarra');
        save('detectado_MiMayor3a5_Guitarra.mat', 'detectado_MiMayor3a5_Guitarra');
        save('detectado_MiMayor5a6_Guitarra.mat', 'detectado_MiMayor5a6_Guitarra');

        save('detectado_Cantata_Piano.mat', 'detectado_Cantata_Piano');
        save('detectado_Jijiji_Piano.mat', 'detectado_Jijiji_Piano');
        save('detectado_Mario_Piano.mat', 'detectado_Mario_Piano');
        save('detectado_MiMayor2a4_Piano.mat', 'detectado_MiMayor2a4_Piano');
        save('detectado_MiMayor3a5_Piano.mat', 'detectado_MiMayor3a5_Piano');
        save('detectado_MiMayor5a6_Piano.mat', 'detectado_MiMayor5a6_Piano');
    