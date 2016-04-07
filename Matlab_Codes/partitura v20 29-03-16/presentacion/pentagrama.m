function pentagrama(nota)

persistent pent;

if isempty(pent)
    disp('cargo imagenes');
    pent = zeros(381,381,3,76); 
    for i = 4:76

        pent(:,:,:,i) = imread([num2str(i) '.jpg']);
        
    end
end

%% PENTAGRAMA entrega la imagen de la nota en un pentagrama
if nota < 4
    nota = 4;
end
if nota > 76
    nota =76;
end

%eml.extrinsic('imshow'); % para lograr compatibilidad con simulink
% leo a traves de I=imread('im.jpg')

% muestro la imagen que corresponde en funcion de la nota que debo
% representar traves de imshow(I)

imshow(pent(:,:,:,nota));

end
