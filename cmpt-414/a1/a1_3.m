% 3. Sharpening

peppersRGB = imread('peppers.png');
flowersRGB = imread('flower-glass.tif');

peppersLum = rgb2ycbcr(peppersRGB);
flowersLum = rgb2ycbcr(flowersRGB);

filts{1} = [0 -1 0;-1 4 -1;0 -1 0];
filts{2} = [0 -1/2 0;-1/2 3 -1/2;0 -1/2 0];
filts{3} = [0 -2 0;-2 9 -2;0 -2 0];
filts{4} = [-1 -1 -1;-1 9 -1;-1 -1 -1];
rgbPeppers = cell(size(peppersRGB));
rgbFlowers = cell(size(flowersRGB));
lumPeppers = cell(size(peppersLum));
lumFlowers = cell(size(flowersLum));
for i = 1:4
    % Sharpen on all rgb values
    rgbPeppers{i} = uint8(convn(peppersRGB, filts{i}, 'same'));
    rgbFlowers{i} = uint8(convn(flowersRGB, filts{i}, 'same'));
    % Sharpen only on luminance value
    lumPeppers{i} = uint8(conv2(peppersLum(:,:,1), filts{i}, 'same'));
    lumFlowers{i} = uint8(conv2(flowersLum(:,:,1), filts{i}, 'same'));
    if (i == 1)
        rgbPeppers{i} = peppersRGB + rgbPeppers{i};
        rgbFlowers{i} = flowersRGB + rgbFlowers{i};
        lumPeppers{i} = peppersLum(:,:,1) + lumPeppers{i};
        lumFlowers{i} = flowersRGB(:,:,1) + lumFlowers{i};
    end
end
rgbPeppers{1} = double(convn(peppersRGB, filts{1}, 'same'));
rgbPeppers{1} = uint8(double(peppersRGB) + rgbPeppers{1});
imsharpPeppers = imsharpen(peppersRGB);
imsharpFlowers = imsharpen(flowersRGB);
figure, subplot(2,5,1), imshow(peppersRGB);
title('Original Peppers');
subplot(2,5,6), imshow(imsharpPeppers);
title('imsharp Peppers');
imwrite(imsharpPeppers, 'q3_images/peppers_imsharp.png', 'png');
for i = 2:5
    subplot(2,5,i), imshow(rgbPeppers{i-1});
    title(strcat('Filter_', int2str(i-1), ' on all RGB values'));
    imwrite(rgbPeppers{i-1}, strcat('q3_images/peppers_rgb_sharp_filt_',int2str(i-1),'.png'), 'png');
    subplot(2,5,i+5), imshow(lumPeppers{i-1});
    title(strcat('Filter_', int2str(i-1), ' on luminance value'));
    imwrite(lumPeppers{i-1}, strcat('q3_images/peppers_lum_sharp_filt_',int2str(i-1),'.png'), 'png');
end

figure, subplot(2,5,1), imshow(flowersRGB);
title('Original Flowers');
subplot(2,5,6), imshow(imsharpFlowers);
title('imsharp Flowers');
imwrite(imsharpFlowers, 'q3_images/flower-glass_imsharp.png', 'png');
for i = 2:5
    subplot(2,5,i), imshow(rgbFlowers{i-1});
    title(strcat('Filter_', int2str(i-1), ' on all RGB values'));
    imwrite(rgbFlowers{i-1}, strcat('q3_images/flower-glass_rgb_sharp_filt_',int2str(i-1),'.png'), 'png');
    subplot(2,5,i+5), imshow(lumFlowers{i-1});
    title(strcat('Filter_', int2str(i-1), ' on luminance value'));
    imwrite(lumFlowers{i-1}, strcat('q3_images/flower-glass_lum_sharp_filt_',int2str(i-1),'.png'), 'png');
end

