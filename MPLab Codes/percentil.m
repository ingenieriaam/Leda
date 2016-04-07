function [percentil0,percentil50,percentil100] = percentil(s)
%% devolvera la mediana con corrimiento punto a punto

L = length(s);
percentil0 = zeros(1,L);
percentil50 = zeros(1,L);
percentil100 = zeros(1,L);
w=round(L/100);
%% La mediana ordenara el bloque y tomara el valor deseado
% ej para el percentil 50 tomare el del medio, todo esto con corrimiento
% muestra a muestra

for h=1:L-w
    h;
    h+w;
    x=s(h:h+w);
    y=sort(x,'descend');
    percentil0(h)=y(end);
    percentil50(h)=y(round(w/2));
    percentil100(h)=y(1);
end