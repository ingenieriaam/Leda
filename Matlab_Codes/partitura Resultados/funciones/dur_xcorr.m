function nota = dur_xcorr(in, i_b, i_m, w_len, fs, ploteo)

    persistent first_time;
    persistent window;
    persistent bloque_ant;
    persistent ruido;
    persistent p;
    persistent flag_nota;   % Flag de cuando arranca y termina una nota
    persistent pot_ant;     % Potencia del bloque anterior
    persistent piso_dif;    % Piso de la diferencia del bloque actual con el anterior
    
    if isempty(first_time)
    	window = hanning(w_len,'periodic');
        bloque_ruido = in( 1 : w_len );
        bloque_ruido = bloque_ruido .* window;
        [~, fft_y] = fft_abs(bloque_ruido,w_len,fs);
        ruido = sum(fft_y);
        flag_nota = 0;
        pot_ant = 0;
        piso_dif = 2e-3;
        p = 2;
    
        first_time = 1;
    end
    
    bloque = in( (w_len*i_b)+1+i_m : w_len*(i_b+1)+i_m);
    bloque = bloque .* window;
    
    if isempty(bloque_ant)
        bloque_ant = bloque;
    end
    
    
    [fft_x, fft_y1] = fft_abs(bloque_ant,length(bloque_ant),fs);
    %fft_y1 = fft_y1 - median(fft_y1);
    %fft_y1 = (fft_y1>0) .* fft_y1;
    [~, fft_y2] = fft_abs(bloque,length(bloque),fs);
    %fft_y2 = fft_y2 - median(fft_y2);
    %fft_y2 = (fft_y2>0) .* fft_y2;
    
    
    %sum(fft_y2.*fft_y2);
    %sum(fft_y1.*fft_y2);
    %sum( ((fft_y2.*fft_y2) ./ (fft_y1.*fft_y2)).^p ) / (w_len/2+1)
    resp1 = fft_y2;
    resp2 = fft_y1;
    resp2 = (resp2 > 0) .* resp2 + (resp2 <= 0) .* 1e-10;
    resp = resp1 - resp2;
    %resp = resp / max(abs(resp));
    
    if sum(resp) > piso_dif && (flag_nota == 0 || flag_nota == 1)
        if ploteo
            disp('ACA EMPIEZA LA NOTA');
        end
        flag_nota = 3;  % Arranca la nota
    elseif flag_nota > 0
        if sum(fft_y2.*fft_y2) >= 20*ruido
            if ploteo
                disp('SIGUE NOTA');
            end
            if sum(fft_y2.*fft_y2) > pot_ant && flag_nota > 1
                flag_nota = 2;  % Busca maximo
            else
                flag_nota = 1;  % Encontro maximo
            end
        else
            if ploteo
                disp('TERMINA LA NOTA')
            end
            flag_nota = 0;  % Silencio
        end
    end
    pot_ant = sum(fft_y2.*fft_y2);
    
    if ploteo
        ax3 = subplot(313);
            plot(fft_x, resp);

        ax2 = subplot(312);
            plot(fft_x, resp2);

        ax1 = subplot(311);
            plot(fft_x, resp1,'b');

        linkaxes([ax1 ax2], ['x' 'y']);     % Linkea ejes
        %axis([ax1 ax2 ax3], [0 4000 -2 2]);    % limites de los ejes


         sound(bloque, fs);

        ruido
        ruido_10 = 10*ruido
        sum_fft_y2 = sum(fft_y2.*fft_y2)
        sum_resp = sum(resp)
    end

    bloque_ant = bloque;
    
    nota = flag_nota
    
end