%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% File Name: reader.m
% Description: This script reads in a test image and thresholds it at 
%              gray level. You can change the threshold ciThres for 
%              different results.
% Environment: Matlab R2007a (may works fine with previous Matlab versions)
% Usage: In Matlab Command Window, type 'reader'.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% read image
im = imread('SFU.jpg');

% gray scale, get luminance
im = rgb2gray(im);

% threshold
ciThres = 160;

im2 = zeros(size(im));

% Method 1 -- use loops: 
% for i = 1:size(im, 1)
%     for j = 1:size(im, 2)
%         if im(i, j) > ciThres 
%             im2(i, j) = 255;
%         else
%             im2(i, j) = 0;
%         end
%     end
% end
%

% Method 2 -- use matrix operation:
%
% "You should try to define steps in the algorithm in terms of matrix 
%   manipulations if possible. It is a lot more efficient than iteration."
% [REF] http://www.cs.sfu.ca/CC/414/li/material/work/matlab_tutorial.html
%
  im2(logical(im > ciThres)) = 255;

% show image
imshow(im2);

% save image to file
imwrite(im2, 'SFU_2.bmp', 'bmp');