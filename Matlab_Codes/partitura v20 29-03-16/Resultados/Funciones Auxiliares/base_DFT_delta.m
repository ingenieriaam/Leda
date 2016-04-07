function [b,R] = base_DFT_delta(N,Fs,delta)
% [b,R] = base_DFT(N,Fs,delta)
% Calculo de la matriz base de la transformada
    
    M = delta*N;
    
    b = zeros(N,M);
    
    for k = 0:M-1
        for n = 0:N-1      
            arg = (2*pi*k*n/M);
            b(n+1,k+1) = exp(-1i*arg);
        end
    end
    
    R = M;
end