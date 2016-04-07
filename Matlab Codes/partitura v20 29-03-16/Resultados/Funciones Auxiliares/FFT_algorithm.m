function [ my_fft_y my_fft_x] = FFT_algorithm(x, fs, N)
    % FFT_algorithm
    % [ my_fft_y my_fft_x] = FFT_algorithm(x, fs, N)
        
    
    % Bit Reversal
        my_fft_y = bitrevorder(x);
        
        
    % Butterfly
        c = -1 + 1i*0;
        for l = 0:log2(N)-1
            W = 1 + 1i*0;
            for j = 0:(2^l)-1
                for k = j:2^(l+1):N-1
                    i1 = k + (2^l);
                    t = my_fft_y(i1+1)*(W);
                    my_fft_y(i1+1) = my_fft_y(k+1) - t;
                    my_fft_y(k+1) = my_fft_y(k+1) + t;
                end;
                W = W * c;
            end;
            c = (sqrt((1.0 + real(c)) / 2.0)) + 1i*(-sqrt((1.0 - real(c)) / 2.0));
        end;
    
        
    % Calculo eje de frecuencias
        my_fft_x = (fs/N)*(1:length(my_fft_y));
        
        