function [nota,notanum] = deteccion(maximo)
% maximo: recibe la frecuencia calculada
% nota: devuelve la nota en letras
    notas = ['la_0','la#0','si_0','do_1','do#1','re_1','re#1','mi_1','fa_1','fa#1','so_1','so#1','la_1','la#1','si_1','do_2','do#2','re_2','re#2','mi_2','fa_2','fa#2','so_2','so#2','la_2','la#2','si_2','do_3','do#3','re_3','re#3','mi_3','fa_3','fa#3','so_3','so#3','la_3','la#3','si_3','do_4','do#4','re_4','re#4','mi_4','fa_4','fa#4','so_4','so#4','la_4','la#4','si_4','do_5','do#5','re_5','re#5','mi_5','fa_5','fa#5','so_5','so#5','la_5','la#5','si_5','do_6','do#6','re_6','re#6','mi_6','fa_6','fa#6','so_6','so#6','la_6','la#6','si_6','do_7','do#7','re_7','re#7','mi_7','fa_7','fa#7','so_7','so#7','la_7','la#7','si_7'];
    chupelupe = (4:76);
    fbase = 27.5;
    r = 2^(1/12);

    notanum = 0;
    
    if maximo >= 27.5
        a=maximo/fbase;
        n=log10(a)/log10(r);
        numero=round(n);
        n = numero*4+1;          % Dado que el vector va de a 3 caracteres
        nota = notas(n:n+3);
        if numero >= 73
            numero = 73;
        end
        notanum = chupelupe(numero);

        %disp(['nota = ' nota]);
        %disp(['frecuencia = ' num2str(maximo)]);
        %disp(['nota = ' nota ' (max: ' num2str(maximo) ', a: ' num2str(a) '), I = ' num2str(I(1)) ', potencia = ' num2str(potencia)]);
    else
        nota = 'none';
        notanum = 4;
        %disp(['nota = ' nota ' (max: ' num2str(maximo) '), I = ' num2str(I(1)) ', potencia = ' num2str(potencia)]);
    end
end