% 3. Sharpening

peppers = imread('peppers.png');
flowers = imread('flower-glass.tif');

p2 = rgb2ycbcr(peppers);

blur1 = [0 1 0;1 -4 1;0 1 0];
blurPeppers = uint8(convn(p2, blur1, 'same'));
sharpPeppers = 5*p2 - blurPeppers;

subplot(1,2,1), imshow(peppers);
subplot(1,2,2), imshow(sharpPeppers);
