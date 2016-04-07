function [base,R] = base_DPDT(N, Fs, P0, P)
%% Calculo de la matriz base de la transformada y su normalizacion
%   [b,R] = base_DPDT(N, Fs, P0, P)
%   N:      (in) Size del bloque
%   Fs:     (in) Frecuencia de sampleo [Hz]
%   P0:     (in) Primer frecuencia que detecta [Hz]
%   P:      (in) Relacion entre las frecuencias de interes
%   [base]: (out) Matriz de la base
%   [R]:    (out) Factor de normalizacion

%% Introduccion
% La matriz de la base de la transformada NO es cuadrada. Tiene dimension
% NxM, con N = size del bloque, y M = cantidad de frecuencias que puede
% representar teniendo en cuenta que arranca en P0, aumenta con un factor
% de P^k (k: numero natural) hasta Fs/2.
% Entonces:
%
% $$ P0 * P^M = F_{max} $$
%
% $$ M = log_P ( \frac{F_{max}}{P0} ) = log_P ( \frac{(Fs/2)}{P0} ) =  \frac{log_{e}(\frac{(Fs/2)}{P0})}{log_{e}(P)} $$
%
% *Nota: se debe redondear M hacia abajo
%
% Esta transformada se basa en la matriz base de la DFT, la cual son
% fasores complejos de frecuencias multiplos enteros de una frecuencia base
%
% $$ Base\_FT = e^{jwt};\ con\ w: frecuencia\ del\ fasor\ en\ [\frac{rad}{seg}],\ y\ t: tiempo $$
%
% $$ Base\_DFT = e^{j(\frac{2\pi k Fs}{N})(nTs)};\ con\ (\frac{2\pi k Fs}{N}): frecuencia\ del\ fasor\ en\ [\frac{rad}{seg}],\ y\ (nTs): sampleo $$
%
% $$ Donde\ (\frac{2\pi Fs}{N})\ es\ la\ frecuencia\ base\ y\ k \in \aleph\ son\ los\ multiplos\ enteros\ de\ dicha\ frecuencia $$
%
% $$ Donde\ Ts\ es\ el\ periodo\ de\ sampleo\ y\ n\in \aleph\ son\ los\ multiplos\ enteros\ de\ dicho\ periodo $$
%
% La base de esta transformada utiliza una frecuencia base exponencial como
% la escala musical, es decir, no usa multiplos enteros de una frecuencia
% base, sino que utiliza una frecuencia elevada a un exponente entero.
%
% $$ Base\_DPDT = e^{j(2\pi P^kP0)(nTs)};\ con\ (2\pi P^kP0): frecuencia\ del\ fasor\ en\ [\frac{rad}{seg}],\ y\ (nTs): sampleo $$
%
% $$ Donde\ (2\pi P^kP0)\ es\ la\ frecuencia\ y\ k \in \aleph\ es\ la\ potencia\ de\ dicha\ frecuencia $$
%
% P0: Primer frecuencia que detecta la transformada
%
% P: Razon, base de la exponencial, de la escala
%


%% Constantes
    Ts=1/Fs;    % Periodo de sampleo
    
    M = fix(log((Fs/2)/(P0))/log(P));   % Calculo M (segunda dimension de la base)
    
    
%% Inicializo base
    base = zeros(N,M);  % Inicializo la base
    
    
%% Calculo base
    for k = 0:M-1
        for n = 0:N-1      
                % (P0*(P^k)*2*pi) representa la frecuencia [rad/seg] del fasor
                % (n*Ts) representa el sampleo (en tiempo) del fasor
            arg = (P0*(P^k)*2*pi*n*Ts);
            base(n+1,k+1) = exp(-1i*arg);
        end
    end
    
    
%% Calculo Normalizacion
% La normalizacion es la norma al cuadrado de la base, o lo que es lo
% mismo, el producto interno de la base por si misma
%
% $$ || \O ||^2 =\ < \O , \O >\ = \sum_{0}^{N-1} (\O) * (\O^*) = \sum_{0}^{N-1} e^{j(2\pi P^kP0)(nTs)} * e^{-j(2\pi P^kP0)(nTs)} = \sum_{0}^{N-1} 1 = N $$
%

    R = N;
end