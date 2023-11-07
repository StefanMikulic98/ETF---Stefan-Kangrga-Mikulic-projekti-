clc
clear all
close all

x=imread('C:\Users\stefa\OneDrive\Радна површина\etf\SDOS\matlab vezbanje\water_body_3.jpg'); %%putanja

Agray = rgb2gray(x);
Agray=imadjust(Agray);
figure;
imshow(x);

imageSize = size(x);
numRows = imageSize(1);
numCols = imageSize(2);

wavelengthMin = 4/sqrt(2);
wavelengthMax = hypot(numRows,numCols);
n = floor(log2(wavelengthMax/wavelengthMin));
wavelength = 2.^(0:(n-2)) * wavelengthMin;

deltaTheta = 45;
orientation = 0:deltaTheta:(180-deltaTheta);

g = gabor(wavelength,orientation);

column=floor((size(wavelength,2)*size(orientation,2))/4)+1;

figure;
subplot(4,column,1)
for p = 1:length(g)
    subplot(4,column,p);
    imshow(real(g(p).SpatialKernel),[]);
    lambda = g(p).Wavelength;
    theta  = g(p).Orientation;
    title(sprintf('\\lambda = %0.2e, \\theta = %d',lambda,theta));
end


[gabormag ,phase] = imgaborfilt(Agray,g);

column=floor((size(wavelength,2)*size(orientation,2))/4)+1;
column1 = column + 2;
figure;
subplot(4,column,1);
for p = 1:(size(wavelength,2)*size(orientation,2))
    subplot(4,column,p)
    imshow(gabormag(:,:,p),[]);
    theta = g(p).Orientation;
    lambda = g(p).Wavelength;
    title(sprintf('O=%d, W=%d',theta,lambda));
end
impixelinfo;


for i = 1:length(g)
    sigma = 0.5*g(i).Wavelength;
    K = 5;
    gabormag(:,:,i) = imgaussfilt(gabormag(:,:,i),K*sigma); 
end

figure
subplot(4,column,1);
for p = 1:(size(wavelength,2)*size(orientation,2))
    subplot(4,column,p)
    imshow(gabormag(:,:,p),[]);
    theta = g(p).Orientation;
    lambda = g(p).Wavelength;
    title(sprintf('O=%d, W=%d',theta,lambda));
end
impixelinfo;


%figure;
%imshow(gabormag(:,:,8),[]); title('gabormag');

%X = 1:numCols;
%Y = 1:numRows;
%[X,Y] = meshgrid(X,Y);
%featureSet = cat(3,gabormag,X);
%featureSet = cat(3,featureSet,Y);
%figure; imshow(featureSet);

X = 1:numCols;
Y = 1:numRows;
[X,Y] = meshgrid(X,Y);
%featureSet2 = cat(3,gabormag,phase); %1 %gabormag(:,:,3:23)
featureSet2 = cat(3,gabormag,X);
featureSet2 = cat(3,featureSet2,Y);

figure
subplot(4,column1,1);
for p = 1:(size(featureSet2,3))
    subplot(4,column1,p)
    imshow(featureSet2(:,:,p),[]);
    %theta = g(p).Orientation;
    %lambda = g(p).Wavelength;
    title(sprintf('featureSet21O=%d, featureSet21W=%d',p,p));
end
impixelinfo;


%===================================================================================
featureSet1 = cat(3,gabormag,X); %26
featureSet1 = cat(3,featureSet1,Y);

featureSet1(:,:,5:20) = bsxfun(@minus, featureSet1(:,:,5:20), mean(featureSet1(:,:,5:20)));
featureSet1(:,:,5:20) = bsxfun(@rdivide,featureSet1(:,:,5:20),std(featureSet1(:,:,5:20)));
%figure;
%imshow(featureSet1(:,:,8),[]); title('L1');
%=========================================================================================
%============================
%featureSet = cat(3,featureSet1(:,:,7),X); %26
%featureSet = cat(3,featureSet,Y);
%numPoints = numRows*numCols;
%A = reshape(featureSet,numRows*numCols,[]);
%================================================================================


numPoints = numRows*numCols;
XX = reshape(featureSet2,numRows*numCols,[]);
X = reshape(featureSet2,numRows*numCols,[]);
X = bsxfun(@minus, X, mean(X));
X = bsxfun(@rdivide,X,std(X));

Y= reshape(X,numRows,numCols,[]);
figure
subplot(4,column1,1);
for p = 1:(size(Y,3))
    subplot(4,column1,p)
    imshow(Y(:,:,p),[]);
    %theta = g(p).Orientation;
    %lambda = g(p).Wavelength;
    title(sprintf('featureSet22O=%d, featureSet22W=%d',p,p));
end
impixelinfo;

%============================================================
featureSet = reshape(featureSet1(:,:,5:20),numRows*numCols,[]);
featureSet = cat(2,featureSet,X(:,2)); %26
featureSet = cat(2,featureSet,X(:,3));


Z= reshape(featureSet,numRows,numCols,[]);
column2=floor(size(Z,3)/4)+1;
figure
subplot(4,column2,1);
for p = 1:(size(Z,3))
    subplot(4,column2,p)
    imshow(Z(:,:,p),[]);
    %theta = g(p).Orientation;
    %lambda = g(p).Wavelength;
    title(sprintf('featureSet12O=%d, featureSet12W=%d',p,p));
end
impixelinfo;

%================================================================================


%coeff = pca(X);
%feature2DImage = reshape(X*coeff(:,1),numRows,numCols);
%figure;
%imshow(feature2DImage,[]);
%gabormag=reshape(featureSet2,numRows*numCols,[]);
%========================================================

proba = cat(2,XX(:,9),XX(:,29)); %26
proba = cat(2,proba,XX(:,30));
probakon = reshape(proba(:,1),[numRows numCols]);
figure;
imshow(probakon,[]);
impixelinfo;
%========================================================
%[L, C] = kmeans(proba,2,"Replicates",5);

figure;
idx = dbscan(proba,4,37);
gscatter(proba(:,1),proba(:,2),idx,'rgbm','.',10);
idx(idx==-1)= 350;
%[X1,Y,Z] = sphere(16);
%S = repmat([70,50,20],numel(X1),1);
%C1 = repmat([1,2,3],numel(X1),1);
%s = S(:);
%c = C1(:);
%scatter3(proba(:,1),proba(:,2),proba(:,3), s,c);
%figure;
%plot(C(:,1),C(:,2),C(:,2),'kx');
%disp(C);
%impixelinfo;

idx = reshape(idx,[numRows numCols]);
figure;
imshow(label2rgb(idx));
impixelinfo;

%L = reshape(L,[numRows numCols]);
%figure;
%imshow(label2rgb(L));

%figure;
%Aseg1 = zeros(size(x),"like",x);
%Aseg2 = zeros(size(x),"like",x);
%BW = L == 2;
%BW = repmat(BW,[1 1 3]);
%Aseg1(BW) = x(BW);
%Aseg2(~BW) = x(~BW);
%montage({Aseg1,Aseg2});

%%
figure;
idy = reshape(idx,numRows*numCols,[]);
scatter3(proba(:,2),proba(:,3),proba(:,1));

%%
max = max(idx(:));
min = min(idx(:));
%%
y=idx(390,390);
idx(idx==y)=0;

B=imbinarize(idx);
A=~idx;
area_opened=imdilate(A,ones (6,6));

figure;
subplot(2,2,1); imshow(idx); title('idx');
subplot(2,2,2); imshow(B); title('B');
subplot(2,2,3); imshow(A); title('A');
subplot(2,2,4); imshow(area_opened); title('area_opened');
impixelinfo;

figure;
Aseg1 = zeros(size(x),"like",x);
Aseg2 = zeros(size(x),"like",x);
BW = area_opened == 1;
BW = repmat(BW,[1 1 3]);
Aseg1(BW) = x(BW);
Aseg2(~BW) = x(~BW);
montage({Aseg1,Aseg2});
