function ruido = mi_ruido(fs,len)


    f0 = fs/len;
    ruido = 0;
    for f = f0:f0:fs/2;
        ruido = ruido + randn(1) * tono(f, fs, len);
    end

end
