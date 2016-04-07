%% Init
    clc;
    clear all;
    close all;
    
    
%% Init tabla    
    tabla_patron_Piano{ 6, 2 } = {};
    tabla_patron_Guitarra{ 6, 2 } = {};

    
%% Nombre de nota
    %% Cantata Piano
        Notas_Cantata_Piano = char( 'do#3', 're_3', 'mi_3', 'fa#3', 'so#3', 'fa#3', ...
                                    'do#3', 're_3', 'mi_3', 'fa#3', 'so#3', 'fa#3', ...
                                    'do#3', 're_3', 'mi_3', 'fa#3', 'so#3', 'fa#3', ...
                                    'fa#3', 'la_3', 'so#3', 'fa#3', 'la_3', 'so#3', ...
                                    'fa#3', 'so#3', 'la_3', 'si_3', 'do#4', 'si_3', ...
                                    'fa#3', 'so#3', 'la_3', 'si_3', 'do#4', 'si_3', ...
                                    'fa#3', 'so#3', 'la_3', 'si_3', 'do#4', 'si_3', ...
                                    'si_3', 're_4', 'do#4', 'si_3', 're_4', 'do#4', ...
                                    'do#4', 're_4', 'mi_4', 'fa#4', 'la_4', 'so#4', 'do#5', ...
                                    'do#4', 're_4', 'mi_4', 'fa#4', 'la_4', 'so#4', 'do#5', ...
                                    'do#4', 're_4', 'mi_4', 'fa#4', 'la_4', 'so#4', ...
                                    'la_4', 'so#4', 'fa#4', 'mi_4', 're_4');
                             
                                
    %% Cantata Guitarra
        Notas_Cantata_Guitarra = Notas_Cantata_Piano;
    
    
    %% Jijiji Piano
        Notas_Jijiji_Piano = char(  'la_3', 're_4', 'mi_4', 'fa_4', 'so_4', ...
                                    'la_4', 'la_4', 'la_4', 'so_4', 'fa_4', ...
                                    'mi_4', 're_4', 're_4', 're_4', 're_4', ...
                                    're_4', 'do#4', 'do#4', 're_4', 'mi_4', ...
                                    'so_4', 'fa_4', 'mi_4', ...
                                    'so_4', 'fa_4', 'mi_4', 'so_4', 'fa_4', 'mi_4', 'so_4', 'fa_4', ...
                                    'mi_4', 'so_4', 'fa_4', 'mi_4', 'so_4', 'fa_4', 'mi_4', 're_4', ...
                                    'do#4', 're_4', 'mi_4', 'fa_4', 'mi_4', 're_4', 'do#4', 're_4');
                   
                                
    %% Jijiji Guitarra             
        Notas_Jijiji_Guitarra = Notas_Jijiji_Piano;
              
                                
    %% Mario Piano                      
        Notas_Mario_Piano = char(   'mi_4', 'mi_4', 'mi_4', 'do_4', 'mi_4', 'so_4', 'so_3', ...
                                    'do_4', 'so_3', 'mi_3', 'la_3', 'si_3', 'la#3', 'la_3', 'so_3', ...
                                    'do_4', 'mi_4', 'so_4', 'la_4', 'fa_4', 'so_4', 'mi_4', 'do_4', 're_4', 'si_3');
    
    
    %% Mario Guitarra
        Notas_Mario_Guitarra = char(   'mi_4', 'mi_4', 'mi_4', 'do_4', 'mi_4', 'so_4', 'so_3', ...
                                        'do_4', 'so_3', 'mi_3', 'la_3', 'si_3', 'la#3', 'la_3', 'so_3', ...
                                        'mi_4', 'so_4', 'la_4', 'fa_4', 'so_4', 'mi_4', 'do_4', 're_4', 'si_3');
    
    
    %% MiMayor2a4 Piano
        Notas_MiMayor2a4_Piano=char('mi_2','fa#2','so#2','la_2','si_2','do_3','re#_3','mi_3','fa#3','so#3','la_3','si_3','do_4','re#_4','mi_4');
    
    
    %% MiMayor2a4 Guitarra
        Notas_MiMayor2a4_Guitarra=Notas_MiMayor2a4_Piano;
    
    
    %% MiMayor3a5 Piano
        Notas_MiMayor3a5_Piano=char('mi_3','fa#3','so#3','la_3','si_3','do_4','re#_4','mi_4','fa#4','so#4','la_4','si_4','do_5','re#_5','mi_5');
    
    
    %% MiMayor3a5 Guitarra
        Notas_MiMayor3a5_Guitarra=Notas_MiMayor3a5_Piano;
    
    
    %% MiMayor5a6 Piano
        Notas_MiMayor5a6_Piano=char('mi_5','fa#5','so#5','la_5','si_5','do_6','re#_6','mi_6');
    
    
    %% MiMayor5a6 Guitarra
        Notas_MiMayor5a6_Guitarra=Notas_MiMayor5a6_Piano;
    


%% Guardo matriz
    tabla_patron_Guitarra{1,1}=Notas_Cantata_Guitarra;
    tabla_patron_Guitarra{2,1}=Notas_Jijiji_Guitarra;
    tabla_patron_Guitarra{3,1}=Notas_Mario_Guitarra;
    tabla_patron_Guitarra{4,1}=Notas_MiMayor2a4_Guitarra;
    tabla_patron_Guitarra{5,1}=Notas_MiMayor3a5_Guitarra;
    tabla_patron_Guitarra{6,1}=Notas_MiMayor5a6_Guitarra;
    
    tabla_patron_Piano{1,1}=Notas_Cantata_Piano;
    tabla_patron_Piano{2,1}=Notas_Jijiji_Piano;
    tabla_patron_Piano{3,1}=Notas_Mario_Piano;
    tabla_patron_Piano{4,1}=Notas_MiMayor2a4_Piano;
    tabla_patron_Piano{5,1}=Notas_MiMayor3a5_Piano;
    tabla_patron_Piano{6,1}=Notas_MiMayor5a6_Piano;

    
    save('Notas_Cantata_Guitarra.mat', 'Notas_Cantata_Guitarra');
    save('Notas_Jijiji_Guitarra.mat', 'Notas_Jijiji_Guitarra');
    save('Notas_Mario_Guitarra.mat', 'Notas_Mario_Guitarra');
    save('Notas_MiMayor2a4_Guitarra.mat', 'Notas_MiMayor2a4_Guitarra');
    save('Notas_MiMayor3a5_Guitarra.mat', 'Notas_MiMayor3a5_Guitarra');
    save('Notas_MiMayor5a6_Guitarra.mat', 'Notas_MiMayor5a6_Guitarra');
    
    save('Notas_Cantata_Piano.mat', 'Notas_Cantata_Piano');
    save('Notas_Jijiji_Piano.mat', 'Notas_Jijiji_Piano');
    save('Notas_Mario_Piano.mat', 'Notas_Mario_Piano');
    save('Notas_MiMayor2a4_Piano.mat', 'Notas_MiMayor2a4_Piano');
    save('Notas_MiMayor3a5_Piano.mat', 'Notas_MiMayor3a5_Piano');
    save('Notas_MiMayor5a6_Piano.mat', 'Notas_MiMayor5a6_Piano');
    
    