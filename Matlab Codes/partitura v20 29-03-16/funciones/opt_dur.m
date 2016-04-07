function [out] = opt_dur(nota)

    out(length(nota)) = nota(length(nota));
    
    borrar = 0;
    
    for i = length(nota)-1:-1:1
        if borrar == 1
            if nota(i) == 2
                borrar = 0;
            end
            out(i) = 0;
        else
            if( (nota(i) == 0) && (nota(i+1) == 1) )
                out(i+1) = 0;
                out(i) = 0;
            elseif nota(i) == 3
                borrar = 1;
                out(i) = 0;
            elseif nota(i+1) == 2
                out(i) = 0;
            else
                out(i) = nota(i);
            end
        end
    end

end