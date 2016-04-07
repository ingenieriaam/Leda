clc;
clear all;
close all;


restoredefaultpath;
addpath(genpath('../../Audios/'));   % Ruta de funciones auxiliares *.m
addpath(genpath('./funciones/'));               % Ruta de funciones auxiliares *.m
    
%filename = 'b_8_k.wav';
%filename = 'G_2_8k';
%filename = 'jijiji.wav';
%filename = 'mas_arriba';
%filename = 'aun_ma_rriba.wav';
%filename = 'dosYdosOctavasDo.wav';
%filename = 'test120nps_22k.wav';
filename = 'test120nps.wav';
    
NUMSAMP = 1024;
[data,fs] = wavread(filename);
data=data(:,1);
inicio=data(1:NUMSAMP);

px=pgramBarlett(inicio',2);
varT=mean(px*pi)*2*NUMSAMP


x=1:length(data);
piso=varT*ones(1,length(data));

figure,
plot(x,data,'b-',x,piso,'r-',x,-1.*piso,'r');
legend('señal','piso de ruido');

dataL=data;
% for i=1:length(data)
%     if data(i)<varT && data(i)>-varT
%         dataL(i)=0;
%     end
%     
% end

for i=1:length(data)
    if data(i)>0
        dataL(i)=data(i)-varT;
    else
        dataL(i)=data(i)+varT;
    end
    
end
% dataL(i)=dataL(i)-sign(dataL(i))*varT;

figure,
plot(x,data,'b-',x,dataL,'g-');
legend('signal','clean');
