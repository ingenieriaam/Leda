function nota = dur_prueba(in, i_b, w_len, plot_param)

    persistent E_ant;           % Energia del bloque de muestras anterior
    persistent nivel_ruido;     % Energia del ruido del primer bloque
    
    
    nivel_energia = 0.2;            % Nivel de energia minimo (de la diferencia de energia del bloque actual y el bloque anterior), para detectar el comienzo de nota.
                                    % Si nivel_energia = R, La energia del bloque actual es (1+R)/(1-R) mayor a la del bloque anterior.
    coeficiente_nivel_ruido = 100;  % La cantidad de veces mayor que debe ser la energia del bloque actual con respecto a E_ruido para no detectar silencio.
    
    if isempty(nivel_ruido)
        bloque_ruido = in( 1 : w_len );
        
        E_ruido = sum(bloque_ruido.^2)/w_len;               % Calcula la energia del primer bloque
        nivel_ruido = E_ruido * coeficiente_nivel_ruido;    % Calcula nivel de ruido
    end
    
    
    bloque = in( (w_len*i_b)+1 : w_len*(i_b+1));    % Agarra un bloque
    bloque = bloque - (mean(bloque));               % Le saca la continua
    
    E_act = sum(bloque.^2)/w_len;       % Calcula la energia del bloque actual
    
    if isempty(E_ant)
        E_ant = E_act;    % La primera vez no hay bloque anterior, entonces la energia del bloque anterior es = a la energia del bloque actual
    end
    
        
    relacion_energia = (E_act - E_ant)/(E_act + E_ant); % Relacion entre la energia del bloque actual y la energia del bloque anterior. Va de -1 a 1
        
        % Si la diferencia de energia es muy alta, comienza la nota:
        if ( relacion_energia > nivel_energia ) && (E_act > nivel_ruido)
            if plot_param
                stem((w_len*i_b)+1, relacion_energia/nivel_energia,'b');    % Plotea la relacion de relacion_energia con nivel_energia
                stem((w_len*i_b)+2, E_act/nivel_ruido,'y');                 % Plotea la relacion de E_act con nivel_ruido
            end
            
            nota = 2;

        % Si el parametro disminuye pero es mas alto que el nivel de ruido, se mantiene la nota:
        elseif  (E_act > nivel_ruido)
            if plot_param
                stem((w_len*i_b)+1, relacion_energia/nivel_energia,'b');    % Plotea la relacion de relacion_energia con nivel_energia
                stem((w_len*i_b)+2, E_act/nivel_ruido,'y');                 % Plotea la relacion de E_act con nivel_ruido
            end
            
            nota = 1;
            
        % Si el parametro disminuye mucho, es silencio:
        else
            if plot_param
                stem((w_len*i_b)+1, relacion_energia/nivel_energia,'b');    % Plotea la relacion de relacion_energia con nivel_energia
                stem((w_len*i_b)+2, E_act/nivel_ruido,'y');                 % Plotea la relacion de E_act con nivel_ruido
            end
            
            nota = 0;
        end
        
    
    E_ant = E_act;    % Guarda la energia del bloque actual para la proxima vez
        
end


