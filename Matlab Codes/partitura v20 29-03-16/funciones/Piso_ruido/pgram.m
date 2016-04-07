function [px,wx] = pgram(x,n1,n2)
%PGRAM Periodograma
%   [px,wx] = PGRAM(x,n1,n2)
%   x:  (in)    Señal a analizar
%   n1: (in)    Extremo inferior del bloque en estudio
%   n2: (in)    Extremo superior del bloque en estudio
%   px: (out)   Densidad espectral de energia
%   wx: (out)   Vector de frecuencias normalizada [0,pi]
%
%   La funcion PGRAM calcula el estimador PERIODOGRAMA de la densidad
%   espectral de energia de la señal x(n1:n2). 
%   
%   Para su calculo utiliza la transformada Rapida de Fourier, y utiliza la
%   tecnica de zero padding en caso que la longitud de la secuencia x(n) no
%   sea un multiplo de 2. El parametro nfft es como mimino igual a 256.
%
%   El algoritmo utilizado es
%       x(n) => FFT => X(w) => 1/N * |X(w)|^2 = Pper(w)
%
%   El vector de frecuencias esta normalizado de forma tal que el mismo
%   esta comprendido entre las frecuencias 0 y pi (3.1416).
%
%   La validez del algoritmo se probo comparandolo con la funcion
%   periodogram obteniendo:
%       error 0 para el vector de frecuencias
%       error menor a 1e-15 para el vector Densidad espectral de energia
%
%   See also 
%
%   Autor: Orge Fernando Gabriel
%   Revision: 3
%   Fecha: 06/10/2015
    
    if nargin == 1
        n1 = 1; n2 = length(x);
    end;
    
    N = n2 - n1 + 1;
    
    nfft = 2^nextpow2(N);
    if (nfft < 256) 
        nfft = 256; 
    end;
    
    dw = 1 / (nfft/2);
    wx = pi*(0 : dw : 1);
    wx = wx';
    
    p = 1/(2*pi) * abs( fft(x(n1:n2),nfft ) ).^2 / N;
    px = 2*p(1:length(wx));
    
end