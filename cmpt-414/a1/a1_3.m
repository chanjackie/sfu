% 3. Sharpening

peppersRGB = imread('peppers.png');
flowersRGB = imread('flower-glass.tif');

peppersLum = rgb2ycbcr(peppersRGB);
flowersLum = rgb2ycbcr(flowersRGB);

filts{1} = [0 -1 0;-1 4 -1;0 -1 0];
filts{2} = [0 -2 0;-2 9 -2;0 -2 0];
filts{3} = [0 -1/2 0;-1/2 3 -1/2;0 -1/2 0];
filts{4} = [-1 -1 -1;-1 9 -1;-1 -1 -1];
for i = 1:4
    rgbPeppers{i} = uint8(convn(peppersRGB, filts{i}, 'same'));
    lumPeppers{i} = uint8(convn(peppersLum, filts{i}, 'same'));
    lumPeppers{i} = ycbcr2rgb(lumPeppers1);
end
control = imsharpen(peppersRGB);

% subplot(1,5,1), imshow(peppersRGB);
subplot(1,3,1), imshow(rgbPeppers1);
subplot(1,3,2), imshow(lumPeppers1);
% subplot(1,5,4), imshow(newRGBPep);
% subplot(1,5,5), imshow(control);

