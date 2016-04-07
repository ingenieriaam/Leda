function [ nivel ] = piso_ruido( signal, signal_x, coeficiente)
%PISO_RUIDO halla un piso de ruido dinamico

    L = length(signal);
    
    media = mean(signal);
    varianza = var(signal);
    curtosis = kurtosis((signal>mean(signal)).*signal);    % 0 < curtosis < L
    maximo = max(signal);
    
    curtosis = (curtosis/L);          % 0 < curtosis < 1
    
    %nivel = medfilt1(signal,4)+media;
    ruido = media; 
    %nivel = maximo(1)*(curtosis-1)/curtosis;
    %nivel = (media + varianza + nivel ) / 3;
    
    nivel = ruido*coeficiente;
 
    %{
    disp(['media: ' num2str(media) ' - varianza: ' num2str(varianza) ' - curtosis: ' num2str(curtosis) ' - nivel:' num2str(nivel)]);
    
    figure(40);
    clf;
    hold on;
    stem(signal_x, signal,'k');
    %plot(signal_x, media,'r');
    %plot(signal_x, varianza,'g');
    %plot(signal_x, maximo*curtosis,'b');
    plot(signal_x, ones(L,1)*ruido,'r');
    hold off;
    legend('signal', 'con poco ruido', 'con mucho ruido');
    %ylim([0 max(signal)]);
    xlim([0 1500]);
    %}
    
end

