function prueba(in, i_b, i_m, w_len, fs)

    persistent first_time;
    persistent window;
    
    if isempty(first_time)
    	window = hanning(w_len,'periodic');
        first_time = 1;
    end
    
    
    bloque = in( (w_len*i_b)+1+i_m : w_len*(i_b+1)+i_m);
    bloque = bloque .* window;
    
    subplot(311);
        plot(in);
    
    subplot(312);
        plot(bloque);
    
    subplot(313);
        [fft_x, fft_y] = fft_abs(bloque,length(bloque),fs);
        plot(fft_x, fft_y);
    
end