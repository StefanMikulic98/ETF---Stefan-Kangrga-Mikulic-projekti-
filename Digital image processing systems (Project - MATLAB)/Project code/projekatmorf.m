clc
clear all
close all
x=imread('C:\Users\stefa\OneDrive\Радна површина\etf\SDOS\matlab vezbanje\water_body_7.jpg'); %%putanja

I1=rgb2gray(x);
I12=imadjust(I1);

I2=imgaussfilt(x, 2);
I31=rgb2gray(I2);
I3=imadjust(I31);

Ieq = adapthisteq(I1);

figure;
subplot(2,3,1); imshow(I1); title('rgb2gray Image');
subplot(2,3,2); imshow(I12); title('imadjust x');
subplot(2,3,3); imshow(Ieq); title('adapthisteq');
subplot(2,3,4); imhist(I1); title('rgb2gray');
subplot(2,3,5); imhist(I12); title('imadjust');
subplot(2,3,6); imhist(Ieq); title('adapthisteq');
%impixelinfo;

E=rescale(entropyfilt(Ieq));
binary_image=imbinarize(E,0.85);
%figure; imshow(binary_image);
area_opened=bwareaopen(binary_image,1000);
st=strel('square',5);
area_opened1=imclose(area_opened,st);
hole_filling=imfill(area_opened1,'holes');

etc_part=I1.*uint8(hole_filling);
water_part=I1.*uint8(~hole_filling);

peri=imdilate(bwperim(hole_filling),strel('disk',2));

figure;
subplot(2,3,1); imshow(E); title('entropyfilt');
subplot(2,3,2); imshow(binary_image); title('imbinarize');
subplot(2,3,3); imshow(area_opened); title('bwareaopen');
subplot(2,3,4); imshow(area_opened1); title('imclose');
subplot(2,3,5); imshow(hole_filling); title('imfill');
impixelinfo;

figure;
subplot(2,3,1); imshow(x); title('Original Image');
%subplot(2,3,2); imshow(I_sharpen); title('Sharpened Image');
subplot(2,3,3); imhist(E); title('entropyfilt');
subplot(2,3,4); imshow(etc_part); title('Ostalo');
subplot(2,3,5); imshow(water_part); title('Vodene povrsine');
subplot(2,3,6); imshow(labeloverlay(I1,peri,"Colormap",[1 1 0])); title('Granica');
impixelinfo;