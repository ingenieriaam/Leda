function output = Reduce_vector(input, piso)
    % Reduce el vector 'input' eliminando las muestras con valor menor o 
    % igual a 'piso' del comienzo y final del vector. Si 'piso' no esta
    % definido, piso = 0.

    if (~exist('input', 'var'))
        error('Reduce_vector(input, ...): "input" es un parametro requerido');
    end
    
    if (~isvector(input))
        error('"input" debe ser un vector');
    end
    
    if (~exist('piso', 'var'))
        piso = 0;
    end
    
    for i = 1:length(input)
        if abs(input(1)) <= piso
            input (1) = [];
        else
            break;
        end
    end
    for i = length(input):-1:1
        if abs(input(i)) <= piso
            input(i) = [];
        else
            break;
        end
    end
    
    output = input;

end