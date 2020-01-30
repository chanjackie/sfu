% 4. Edge Detection
% a) 
smoothIm = (imread('circuit.tif'));
noiseIm = (imread('circuit_var002.tif'));
% i) Laplacian edge detection
lapFilter = [0 1 0;1 -4 1;0 1 0];
laplacian1 = edge(smoothIm, 'zerocross', 0.1, lapFilter);
laplacian2 = edge(noiseIm, 'zerocross', 1, lapFilter);
% ii) Prewitt, Roberts and Sobel
prewitt1 = edge(smoothIm, 'Prewitt');
prewitt2 = edge(noiseIm, 'Prewitt');
roberts1 = edge(smoothIm, 'Roberts');
roberts2 = edge(noiseIm, 'Roberts');
sobel1 = edge(smoothIm, 'Sobel');
sobel2 = edge(noiseIm, 'Sobel');

figure, subplot(2,4,1), imshow(laplacian1);
title('Laplacian on Smooth Img');
imwrite(laplacian1, 'q4_images/laplacian_on_smooth.png', 'png');
subplot(2,4,2), imshow(prewitt1);
title('Prewitt on Smooth Img');
imwrite(prewitt1, 'q4_images/prewitt_on_smooth.png', 'png');
subplot(2,4,3), imshow(roberts1);
title('Roberts on Smooth Img');
imwrite(roberts1, 'q4_images/roberts_on_smooth.png', 'png');
subplot(2,4,4), imshow(sobel1);
title('Sobel on Smooth Img');
imwrite(sobel1, 'q4_images/sobel_on_smooth.png', 'png');
subplot(2,4,5), imshow(laplacian2);
title('Laplacian on Noise Img');
imwrite(laplacian2, 'q4_images/laplacian_on_noise.png', 'png');
subplot(2,4,6), imshow(prewitt2);
title('Prewitt on Noise Img');
imwrite(prewitt2, 'q4_images/prewitt_on_noise.png', 'png');
subplot(2,4,7), imshow(roberts2);
title('Roberts on Noise Img');
imwrite(roberts2, 'q4_images/roberts_on_noise.png', 'png');
subplot(2,4,8), imshow(sobel2);
title('Sobel on Noise Img');
imwrite(sobel2, 'q4_images/sobel_on_noise.png', 'png');


% b) Canny Edge Operator
roomIm = rgb2gray(imread('room.tif'));
sofaIm = rgb2gray(imread('sofa.tif'));
sfuIm = rgb2gray(imread('sfu.jpg'));

cannyRoom = cannyEdgeOperator(roomIm, 90, 50);
cannySofa = cannyEdgeOperator(sofaIm, 180, 100);
cannySfu = cannyEdgeOperator(sfuIm, 220, 180);
cannySmooth = cannyEdgeOperator(smoothIm, 150, 50);
cannyNoise = cannyEdgeOperator(noiseIm, 250, 200);
matCannyRoom = edge(roomIm, 'Canny');
matCannySofa = edge(sofaIm, 'Canny');
matCannySfu = edge(sfuIm, 'Canny');
figure, imshow([cannyRoom, matCannyRoom]);
title('My Canny Edge Operator                                                               MatLab Canny Edge Operator');
figure, imshow([cannySofa, matCannySofa]);
title('My Canny Edge Operator                                                               MatLab Canny Edge Operator');
figure, imshow([cannySfu, matCannySfu]);
title('My Canny Edge Operator                                               MatLab Canny Edge Operator');
imwrite(cannyRoom, 'q4_images/room_canny_edge.png', 'png');
imwrite(cannySofa, 'q4_images/sofa_canny_edge.png', 'png');
imwrite(cannySfu, 'q4_images/sfu_canny_edge.png', 'png');
imwrite(matCannyRoom, 'q4_images/room_mat_canny_edge.png', 'png');
imwrite(matCannySofa, 'q4_images/sofa_mat_canny_edge.png', 'png');
imwrite(matCannySfu, 'q4_images/sfu_mat_canny_edge.png', 'png');

figure, subplot(2,3,1), imshow(cannySmooth);
title('Canny on Smooth Img');
imwrite(cannySmooth, 'q4_images/canny_on_smooth.png', 'png');
subplot(2,3,2), imshow(laplacian1);
title('Laplacian on Smooth Img');
subplot(2,3,3), imshow(prewitt1);
title('Prewitt on Smooth Img');
subplot(2,3,4), imshow(cannyNoise);
title('Canny on Noise Img');
imwrite(cannyNoise, 'q4_images/canny_on_noise.png', 'png');
subplot(2,3,5), imshow(laplacian2);
title('Laplacian on Noise Img');
subplot(2,3,6), imshow(prewitt2);
title('Prewitt on Noise Img');

figure, imshow(edge(noiseIm, 'Canny'));

function E = cannyEdgeOperator(im, T_h, T_l)
    % i) Use gradient operator
    G1 = [-1 0 1;-2 0 2;-1 0 1];
    G2 = [1 2 1;0 0 0;-1 -2 -1];
    % Filter image with horizontal and vertical gradient operator
    hor_filt = conv2(im, G1, 'same');
    ver_filt = conv2(im, G2, 'same');
    % Calculate directions and magnitudes
    directions = atan2(ver_filt, hor_filt)*180/pi;
    magnitudes = sqrt(hor_filt.^2 + ver_filt.^2);

    x = size(directions, 1);
    y = size(directions, 2);
    % Set all directions to positive
    for i = 1:x
        for j = 1:y
            if (directions(i,j) < 0)
                directions(i,j) = 360 + directions(i,j);
            end
        end
    end

    % ii) Edge thinning, non-maximum suppression
    newMag = uint8(zeros(size(magnitudes)));
    for i = 2:x-1
        for j = 2:y-1
            theta = directions(i,j);
            s = magnitudes(i,j);
            if ((theta >= 0  && theta < 22.5) || (theta >= 157.5 && theta < 202.5) || (theta >= 337.5 && theta <= 360))
                if (s == max([s, magnitudes(i, j+1), magnitudes(i, j-1)]))
                    newMag(i,j) = s;
                end
            elseif ((theta >= 22.5 && theta < 67.5) || (theta >= 202.5 && theta < 247.5))
                if (s == max([s, magnitudes(i+1, j-1), magnitudes(i-1, j+1)]))
                    newMag(i,j) = s;
                end
            elseif ((theta >= 67.5 && theta < 112.5) || (theta >= 247.5 && theta < 292.5))
                if (s == max([s, magnitudes(i+1, j), magnitudes(i-1, j)]))
                    newMag(i,j) = s;
                end
            elseif ((theta >= 112.5 && theta < 157.5) || (theta >= 292.5 && theta < 337.5))
                if (s == max([s, magnitudes(i-1, j-1), magnitudes(i+1, j+1)]))
                    newMag(i,j) = s;
                end
            end
        end
    end
    % figure, imshow(newMag);

    % iii) Edge tracking, hysteresis thresholding

    E = double(zeros(size(newMag)));

    for i = 1:x
        for j = 1:y
            % If s' already explored, move to next pixel
            if (E(i,j) ~= 0)
                continue
            end
            s = newMag(i,j);
            if (s > T_h)
                E(i,j) = 1;
                theta = directions(i,j);
                if ((theta >= 0  && theta < 22.5) || (theta >= 157.5 && theta < 202.5) || (theta >= 337.5 && theta <= 360))
                    i1 = max(i-1, 1);
                    neighbour = newMag(i1, j);
    %                 disp(neighbour);
                    while (neighbour > T_l && i1 > 0)
                        disp(i1);
                        E(i1, j) = 1;
                        i1 = i1 - 1;
                        neighbour = newMag(i1, j);
                    end
                    i1 = min(i+1, x);
                    neighbour = newMag(i1, j);
                    while (neighbour > T_l && i1 <= x)
                        E(i1, j) = 1;
                        i1 = i1 + 1;
                        neighbour = newMag(i1, j);
                    end
                elseif ((theta >= 22.5 && theta < 67.5) || (theta >= 202.5 && theta < 247.5))
                    i1 = max(i-1, 1);
                    j1 = max(j-1, 1);
                    neighbour = newMag(i1, j1);
                    while (neighbour > T_l && i1 > 0 && j1 > 0)
                        E(i1, j1) = 1;
                        i1 = i1-1;
                        j1 = j1-1;
                        neighbour = newMag(i1, j1);
                    end
                    i1 = min(i+1, x);
                    j1 = min(j+1, y);
                    neighbour = newMag(i1, j1);
                    while (neighbour > T_l && i1 <= x && j1 <= y)
                        E(i1, j1) = 1;
                        i1 = i1+1;
                        j1 = j1+1;
                        neighbour = newMag(i1, j1);
                    end  
                elseif ((theta >= 67.5 && theta < 112.5) || (theta >= 247.5 && theta < 292.5))
                    j1 = max(j-1, 1);
                    neighbour = newMag(i, j1);
                    while (neighbour > T_l && j1 > 0)
                        E(i, j1) = 1;
                        j1 = j1-1;
                        neighbour = newMag(i, j1);
                    end
                    j1 = min(j+1, y);
                    neighbour = newMag(i, j1);
                    while (neighbour > T_l && j1 <= y)
                        E(i, j1) = 1;
                        j1 = j1+1;
                        neighbour = newMag(i, j1);
                    end  
                elseif ((theta >= 112.5 && theta < 157.5) || (theta >= 292.5 && theta < 337.5))
                    i1 = max(i-1, 1);
                    j1 = min(j+1, y);
                    neighbour = newMag(i1, j1);
                    while (neighbour > T_l && i1 > 0 && j1 <= y)
                        E(i1, j1) = 1;
                        i1 = i1-1;
                        j1 = j1+1;
                        neighbour = newMag(i1, j1);
                    end
                    i1 = min(i+1, x);
                    j1 = max(j-1, 1);
                    neighbour = newMag(i1, j1);
                    while (neighbour > T_l && i1 <= x && j1 > 0)
                        E(i1, j1) = 1;
                        i1 = i1+1;
                        j1 = j1-1;
                        neighbour = newMag(i1, j1);
                    end
                end
            end
        end
    end
end
            


