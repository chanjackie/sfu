% 2. Smoothing
gnIms{1} = imread('trees_var002.tif');
gnIms{2} = imread('trees_var010.tif');
gnIms{3} = imread('trees_var025.tif');
spIms{1} = imread('trees_salt004.tif');
spIms{2} = imread('trees_salt020.tif');
spIms{3} = imread('trees_salt050.tif');
t = ones(3,3)*1/9;
uwAvgIms = cell(size(gnIms{1}));
knnIms = cell(size(spIms{1}));
medFiltIms = cell(size(gnIms{1}));
for i = 1:3
    uwAvgIms{i} = gnIms{i};
    knnIms{i} = spIms{i};
    medFiltIms{i} = gnIms{i};
    medFiltIms{i+3} = spIms{i};
end
iterations = 3;
K = 4;
for i = 1:3
    for j = 1:iterations
        uwAvgIms{i} = uint8(conv2(uwAvgIms{i}, t, 'same'));
        knnIms{i} = computeKNearestNeighbours(knnIms{i}, K);
        medFiltIms{i} = medfilt2(medFiltIms{i});
        medFiltIms{i+3} = medfilt2(medFiltIms{i+3});
    end
end

row = 3;
col = 6;
for i = 1:3
    subplot(row, col, i), imshow(gnIms{i});
    title(strcat('trees var_',int2str(i)));
    subplot(row, col, i+3), imshow(spIms{i});
    title(strcat('trees salt_',int2str(i)));
    subplot(row, col, i+6), imshow(uwAvgIms{i});
    title(strcat('trees var uw avg_',int2str(i)));
    imwrite(uwAvgIms{i}, strcat('q2_images/trees_var_uw_avg_',int2str(i),'.png'), 'png');
    subplot(row, col, i+9), imshow(knnIms{i});
    title(strcat('trees salt knn_',int2str(i)));
    imwrite(knnIms{i}, strcat('q2_images/trees_salt_knn_',int2str(i),'.png'), 'png');
    subplot(row, col, i+12), imshow(medFiltIms{i});
    title(strcat('trees var med filt_',int2str(i)));
    imwrite(medFiltIms{i}, strcat('q2_images/trees_var_med_filt_',int2str(i),'.png'), 'png');
    subplot(row, col, i+15), imshow(medFiltIms{i+3});
    title(strcat('trees salt med filt_',int2str(i)));
    imwrite(medFiltIms{i+3}, strcat('q2_images/trees_salt_med_filt_',int2str(i),'.png'), 'png');
end
% subplot(1,3,1), imshow(gnIms{3});
% title('Original Image');
% subplot(1,3,2), imshow(uwAvgIms{3});
% title('Unweighted Average Smoothed');
% subplot(1,3,3), imshow(medFiltIms{3});
% title('Median Filtering Smoothed');

function newImg = computeKNearestNeighbours(img, K)
    newImg = uint8(zeros(size(img)));
    for j = 1:size(img, 1)
        for k = 1:size(img, 2)
            % Get 8 neighbours surrounding current pixel
            neighbours = [img(max(1,j-1), max(1,k-1)), img(j, max(1,k-1))...
                img(min(size(img,1),j+1), max(1,k-1)), img(max(1,j-1), k)...
                img(min(size(img,1),j+1), k), img(max(1,j-1), min(size(img,2),k+1))...
                img(j, min(size(img,2),k+1)), img(min(size(img,1),j+1), min(size(img,2),k+1))];
            newImg(j,k) = computeNNAvg(neighbours, img(j,k), K);
        end
    end
end

function val = computeNNAvg(neighbours, center, K)
    nearestNeighbours = zeros(K,1);
    for i = 1:K
        minVal = Inf;
        minIndex = 1;
        for j = 1:size(neighbours)
            diff = abs(neighbours(j)-center);
            if diff < minVal
                minVal = diff;
                minIndex = j;
            end
        end
        nearestNeighbours(i) = neighbours(minIndex);
        neighbours(minIndex) = [];
    end
%     disp(mean(nearestNeighbours));
    val = round(mean(nearestNeighbours));            
end