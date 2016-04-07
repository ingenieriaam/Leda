function output = Complete_vector(input, div)
    % Completa el vector 'input' al final con 'relleno' con tantas muestra tal
    % que el tamaño de 'input' sea divisible por 'div'

    if (~exist('input', 'var'))
        error('Complete_vector(input, div): "input" es un parametro requerido');
    end
    if (~exist('div', 'var'))
        error('Complete_vector(input, div): "div" es un parametro requerido');
    end
    
    if (~isvector(input))
        error('"input" debe ser un vector');
    end
    
    dim = size(input);
    if dim(1) == 1
        dim_ext = 'addcol';
    else
        dim_ext = 'addrow';
    end
    

    input_len = length(input);

    total_length = div-mod(length(input),div);

    output = wextend(dim_ext,'zpd',input,input_len-total_length,'r');

end