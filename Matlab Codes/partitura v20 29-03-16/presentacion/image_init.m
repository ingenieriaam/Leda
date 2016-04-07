%% armado de la matriz que contiene las imagenes a mostrar
  pent = zeros(381,381,3,76); 
% leo a traves de I=imread('im.jpg')
% muestro a traves de imshow(I)

    % contiene las imagenes
    
    % cargo las imagenes
    for i = 4:76

        pent(:,:,:,i) = imread([num2str(i) '.jpg']);
        
    end
  