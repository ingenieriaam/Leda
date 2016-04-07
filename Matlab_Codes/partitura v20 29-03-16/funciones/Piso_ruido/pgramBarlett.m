function [px,wx] = pgramBarlett(x,n)
%PGRAMBARLETT
%   [px,wx] = pgramBarlett(x,n)
%   x:  (in)    Señal a analizar
%   n:  (in)    Numero de secciones
%   px: (out)   Densidad espectral de energia
%   wx: (out)   Vector de frecuencias normalizada [0,pi]
%
%   La funcion PGRAMBARLETT calcula el estimador PERIODOGRAMA de la
%   densidad espectral de energia de la señal x(n1:n2). 
%   
%   See also PGRAM PGRAMMODIFIED
%
%   Autor: Orge Fernando Gabriel
%   Revision: 1
%   Fecha: 06/10/2015
    
    L = floor(length(x)/n);
    n1 = 1;
    [px,wx] = pgram(x(n1:n1+L-1));
    px = px./n;
    n1 = n1 + L;
    for i = 2:n
        px = px + pgram(x(n1:n1+L-1))./n;
        n1 = n1 + L;
    end;
    
%    Px = 0;
%    n1 = 1;
%    for i = 1:n
%        Px = Px + pgram(x(n1:n1+L-1))/n;
%        n1 = n1 + L;
%    end;
end