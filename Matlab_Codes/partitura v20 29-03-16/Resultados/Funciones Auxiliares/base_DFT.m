function [b,R] = base_DFT(N,Fs)
% [b,R] = base_DFT(N,Fs)
% Calculo de la matriz base de la transformada
    
    for k = 0:N-1
        for n = 0:N-1      
            arg = (2*pi*k*n/N);
            b(n+1,k+1) = exp(-1i*arg);
        end
    end
    
    R = N;
end