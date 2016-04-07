
{6,2}={};

vecDURcantata=[0.32,0.32,0.32,0.16,0.16,0.96,
               0.32,0.32,0.32,0.16,0.16,0.96,
               0.32,0.32,0.32,0.16,0.16,0.64,
               0.24,0.16,0.16,0.32,0.64,1.28,
               0.32,0.32,0.32,0.16,0.16,0.96,
               0.32,0.32,0.32,0.16,0.16,0.96,
               0.32,0.32,0.32,0.16,0.16,0.64,
               0.24,0.16,0.16,0.32,0.64,1.28,
               0.32,0.32,0.32,0.16,0.16,0.64,0.48,
               0.32,0.32,0.32,0.16,0.16,0.64,0.48,
               0.32,0.32,0.32,0.16,0.16,0.48,
               0.16,0.16,0.16,0.16,2.56];
     
Notas_MiMayor2a4_Piano=char('mi_2','fa#2','so#2','la_2','si_2','do_3','re#_3','mi_3','fa#3','so#3','la_3','si_3','do_4','re#_4','mi_4');

Notas_MiMayor3a5_Piano=char('mi_3','fa#3','so#3','la_3','si_3','do_4','re#_4','mi_4','fa#4','so#4','la_4','si_4','do_5','re#_5','mi_5');

Notas_MiMayor5a6_Piano=char('mi_5','fa#5','so#5','la_5','si_5','do_6','re#_6','mi_6');

tabla_patron_guitarra{4,1}=Notas_MiMayor2a4_Piano;
tabla_patron_guitarra{5,1}=Notas_MiMayor3a5_Piano;
tabla_patron_guitarra{6,1}=Notas_MiMayor5a6_Piano;
% 
% tabla_patron_guitarra{1,2}=vecDURcantata;
% tabla_patron_guitarra{2,2}=vecDURjijiji;
% tabla_patron_guitarra{3,2}=vecDURmario;
% tabla_patron_guitarra{4,2}=vecDURMiMayor2a4;
% tabla_patron_guitarra{5,2}=vecDURMiMayor3a5;
% tabla_patron_guitarra{6,2}=vecDURMiMayor5a6;



% Ncd = notas correctamente detectadas
% Nnd = notas detectadas
% De las notas que DETECTO, cuantas se detectaron correctamente
precision=Ncd/Nnd;

% Nnd = numero de notas detectadas
% Nne = numero de notas que eran realmente
% De las nota que meti, cuantas de detectaron correctamente
recall=Nnd/Nne;

% Vp=Nnd = notas que detecte
% Fv = notas detectadas que no estan realmente
% Fn = notas que no detecte pero en realidad estaban
acc=Vp/(Vp+Fp+Fn);