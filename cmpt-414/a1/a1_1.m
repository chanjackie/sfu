% 1. Linear stretch
% read image
im = imread('dark.tif');

% gray scale, get luminance
% im = rgb2gray(im);

% threshold
% b = max(max(im));
% a = min(min(im));
b = 170;
a = 22;
pm = 255;
p0 = 0;

im2 = zeros(size(im));

for i = 1:size(im, 1)
    for j = 1:size(im, 2)
        if (im(i, j) <= b) && (im(i, j) >= a)
            val = ((pm-p0)/(b-a))*(im(i, j)-a) + p0;
            im2(i, j) = uint8(val);
        elseif im(i, j) > b
            im2(i, j) = pm;
        else
            im2(i, j) = p0;
        end
    end
end
% min1 = min(min(im));
% max1 = max(max(im));
% im2 = round((im-min1)* (255/(max1-min1)));
% im2(logical(im >= a & im <= b)) = ((pm-p0)/(b-a));
% im2(logical(im > b)) = pm;

% convert im2 to uint8 matrix
newim = uint8(im2);
disp(max(max(newim)));
disp(min(min(newim)));
% show image
subplot(1,2,1), imshow(newim);
subplot(1,2,2), imshow(im);

% save image to file
imwrite(newim, 'dark_2.bmp', 'bmp');
