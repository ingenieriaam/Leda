%% Generación de base para transformada en Q15

clc;
clear all;
close all;
tic
% genero la base en doble presición
P=nthroot(2,12);
P0=82.41;
Fs=22050;
N=2048;
[b,R] = base_DPDT(N, Fs, P0, P);

% la paso a Q15

normB = b./R;       % normalización

Br = real(normB);   % separacion en real e imaginario
Bi = imag(normB);



for i=1:size(Br,2)
    i
    parfor k=1:size(Br,1)
%         % formato binario
%         BQrb{k,i} = cellstr(dec2q15(Br(k,i),'bin'));
%         BQib{k,i} = cellstr(dec2q15(Bi(k,i),'bin'));

        %formato hexadecimal
        BQrh{k,i} = cellstr(dec2q15(Br(k,i),'hex'));
        BQih{k,i} = cellstr(dec2q15(Bi(k,i),'hex'));
    end
end
toc

% guardo los resultados 
save('baseQ15heximag.mat','BQih');
save('baseQ15hexreal.mat','BQrh');