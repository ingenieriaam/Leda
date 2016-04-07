function [b,R] = base_DPDT(N, Fs, P0, P)
%% Calculo de la matriz base de la transformada

    Ts=1/Fs;
    M = fix(log((Fs)/(2*P0))/log(P));
    
    for k = 0:M-1
        for n = 0:N-1      
            arg = (P0*(P^k)*n*Ts);
            b(n+1,k+1) = exp(-1i*arg);
        end
    end
    
    R = N;
end