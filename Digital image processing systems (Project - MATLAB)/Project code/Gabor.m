function varargout = Gabor(varargin)
% GABOR MATLAB code for Gabor.fig
%      GABOR, by itself, creates a new GABOR or raises the existing
%      singleton*.
%
%      H = GABOR returns the handle to a new GABOR or the handle to
%      the existing singleton*.
%
%      GABOR('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GABOR.M with the given input arguments.
%
%      GABOR('Property','Value',...) creates a new GABOR or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Gabor_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Gabor_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Gabor

% Last Modified by GUIDE v2.5 21-Jun-2023 18:55:56

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Gabor_OpeningFcn, ...
                   'gui_OutputFcn',  @Gabor_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Gabor is made visible.
function Gabor_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Gabor (see VARARGIN)
clc
set(handles.uipaneldbscan,'Visible','off');
set(handles.uipanelFinal,'Visible','off');
set(handles.pushbuttonPicture,'Visible','off');
set(handles.pushbuttondbscanResult,'Visible','off');
set(handles.pushbuttonRpicture,'Visible','off');
set(handles.axes2,'Visible','off');
set(handles.axes3,'Visible','off');
set(handles.axes4,'Visible','off');
x = getappdata(0,'picture');
axes(handles.axes1);       
imshow(x);
% Choose default command line output for Gabor
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Gabor wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Gabor_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%ba = getappdata(0,'picture1');
%axes(handles.axes2);       
%imshow(ab);
Pocetak;
set(Gabor, 'Visible', 'Off');
closereq;





function editWavelengthMin_Callback(hObject, eventdata, handles)
% hObject    handle to editWavelengthMin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editWavelengthMin as text
%        str2double(get(hObject,'String')) returns contents of editWavelengthMin as a double


% --- Executes during object creation, after setting all properties.
function editWavelengthMin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editWavelengthMin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editOrientationMin_Callback(hObject, eventdata, handles)
% hObject    handle to editOrientationMin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editOrientationMin as text
%        str2double(get(hObject,'String')) returns contents of editOrientationMin as a double


% --- Executes during object creation, after setting all properties.
function editOrientationMin_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editOrientationMin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editOrientationMax_Callback(hObject, eventdata, handles)
% hObject    handle to editOrientationMax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editOrientationMax as text
%        str2double(get(hObject,'String')) returns contents of editOrientationMax as a double


% --- Executes during object creation, after setting all properties.
function editOrientationMax_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editOrientationMax (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editN_Callback(hObject, eventdata, handles)
% hObject    handle to editN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editN as text
%        str2double(get(hObject,'String')) returns contents of editN as a double


% --- Executes during object creation, after setting all properties.
function editN_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbuttonGabor.
function pushbuttonGabor_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonGabor (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

x = getappdata(0,'picture');
Agray = rgb2gray(x);
Agray=imadjust(Agray);
axes(handles.axes2);       
imshow(Agray);

imageSize = size(x);
numRows = imageSize(1);
numCols = imageSize(2);
setappdata(0,'numRows',numRows);
setappdata(0,'numCols',numCols);
numRowsTxt=string(numRows);
numColsTxt=string(numCols);
set(handles.textNumRows, 'String', numRowsTxt);
set(handles.textNumCols, 'String', numColsTxt);

wavelengthMinTxt = get(handles.editWavelengthMin,'String');  %4/sqrt(2);
wavelengthMin = str2num(wavelengthMinTxt);

orientationMinTxt = get(handles.editOrientationMin,'String');  %0;
orientationMin = str2num(orientationMinTxt);

orientationMaxTxt = get(handles.editOrientationMax,'String');  %135;
orientationMax = str2num(orientationMaxTxt);

nTxt = get(handles.editN,'String');  %8;
n1 = str2num(nTxt);

wavelengthMax = hypot(numRows,numCols);
n = floor(log2(wavelengthMax/wavelengthMin));
wavelength = 2.^(0:(n-2)) * wavelengthMin;

deltaTheta=floor(orientationMax/(n1-1));
orientation = orientationMin:deltaTheta:orientationMax;

setappdata(0,'wavelengthMin',wavelengthMin);
setappdata(0,'wavelengthMax',wavelengthMax);
setappdata(0,'orientationMin',orientationMin);
setappdata(0,'orientationMax',orientationMax);
setappdata(0,'n1',n1);
setappdata(0,'n',n);

g = gabor(wavelength,orientation);

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
    title(sprintf('O=%d, W=%0.2e',theta,lambda));
end
impixelinfo;

sigmaTxt = get(handles.editSigma,'String');  %4/sqrt(2);
sigma = str2num(sigmaTxt);

kTxt = get(handles.editK,'String');  %0;
K = str2num(kTxt);

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
    title(sprintf('O=%d, W=%0.2e',theta,lambda));
end
impixelinfo;

setappdata(0,'gabormag',gabormag);
set(handles.uipaneldbscan,'Visible','on');
set(handles.pushbuttonPicture,'Visible','on');
set(handles.axes2,'Visible','on');




function editSigma_Callback(hObject, eventdata, handles)
% hObject    handle to editSigma (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editSigma as text
%        str2double(get(hObject,'String')) returns contents of editSigma as a double


% --- Executes during object creation, after setting all properties.
function editSigma_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editSigma (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editK_Callback(hObject, eventdata, handles)
% hObject    handle to editK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editK as text
%        str2double(get(hObject,'String')) returns contents of editK as a double


% --- Executes during object creation, after setting all properties.
function editK_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbuttonPicture.
function pushbuttonPicture_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonPicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
x = getappdata(0,'picture'); 
imshow(x);
title("Početna slika");
impixelinfo;



% --- Executes on button press in checkboxNorm.
function checkboxNorm_Callback(hObject, eventdata, handles)
% hObject    handle to checkboxNorm (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkboxNorm



function editSelectFilter_Callback(hObject, eventdata, handles)
% hObject    handle to editSelectFilter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editSelectFilter as text
%        str2double(get(hObject,'String')) returns contents of editSelectFilter as a double


% --- Executes during object creation, after setting all properties.
function editSelectFilter_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editSelectFilter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editRadius_Callback(hObject, eventdata, handles)
% hObject    handle to editRadius (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editRadius as text
%        str2double(get(hObject,'String')) returns contents of editRadius as a double


% --- Executes during object creation, after setting all properties.
function editRadius_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editRadius (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editMinPoints_Callback(hObject, eventdata, handles)
% hObject    handle to editMinPoints (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editMinPoints as text
%        str2double(get(hObject,'String')) returns contents of editMinPoints as a double


% --- Executes during object creation, after setting all properties.
function editMinPoints_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editMinPoints (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbuttonDBSCAN.
function pushbuttonDBSCAN_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonDBSCAN (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

numRows = getappdata(0,'numRows');
numCols = getappdata(0,'numCols');
gabormag = getappdata(0,'gabormag');

X = 1:numCols;
Y = 1:numRows;
[X,Y] = meshgrid(X,Y);

featureSet2 = cat(3,gabormag,X);
featureSet2 = cat(3,featureSet2,Y);

column=floor(size(featureSet2,3)/4)+1;
figure
subplot(4,column,1);
for p = 1:(size(featureSet2,3))
    subplot(4,column,p)
    imshow(featureSet2(:,:,p),[]);
    %theta = g(p).Orientation;
    %lambda = g(p).Wavelength;
    title(sprintf('featureSet=%d',p));
end
impixelinfo;

numPoints = numRows*numCols;

true = get(handles.checkboxNorm,'value');

if true == 1 
    X = reshape(featureSet2,numRows*numCols,[]);
    X = bsxfun(@minus, X, mean(X));
    X = bsxfun(@rdivide,X,std(X));
    Y= reshape(X,numRows,numCols,[]);
    column=floor(size(Y,3)/4)+1;
    figure
    subplot(4,column,1);
    for p = 1:(size(Y,3))
        subplot(4,column,p)
        imshow(Y(:,:,p),[]);
        %theta = g(p).Orientation;
        %lambda = g(p).Wavelength;
        title(sprintf('Normalize=%d',p));
    end
    impixelinfo;
else
    X = reshape(featureSet2,numRows*numCols,[]);
end

selectFiltTxt = get(handles.editSelectFilter,'String');  
selectFilt = str2num(selectFiltTxt);

radiusTxt = get(handles.editRadius,'String'); 
radius = str2num(radiusTxt);

minPointsTxt = get(handles.editMinPoints,'String'); 
minPoints = str2num(minPointsTxt);


proba = cat(2,X(:,selectFilt),X(:,29)); 
proba = cat(2,proba,X(:,30));
probakon = reshape(proba(:,1),[numRows numCols]);
figure;
imshow(probakon,[]);
title("Selektovani filter");
impixelinfo;

figure;
idx = dbscan(proba,radius,minPoints);
gscatter(proba(:,1),proba(:,2),idx,'rgbm','.',10);
idx(idx==-1)= 350;

set(handles.axes3,'Visible','on');

idx = reshape(idx,[numRows numCols]);
axes(handles.axes3);
imshow(label2rgb(idx));
impixelinfo;

figure;
imshow(idx);
title("Pixel");
impixelinfo;

set(handles.uipanelFinal,'Visible','on');
set(handles.axes3,'Visible','on');
set(handles.pushbuttondbscanResult,'Visible','on');
setappdata(0,'pictureDBSCAN',idx);



% --- Executes on button press in pushbuttondbscanResult.
function pushbuttondbscanResult_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttondbscanResult (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
idx = getappdata(0,'pictureDBSCAN'); 
imshow(label2rgb(idx));
title("DBSCAN");
impixelinfo;

fig = uifigure;
uit = uitable(fig,"Data",idx);


% --- Executes on button press in pushbuttonRpicture.
function pushbuttonRpicture_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonRpicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
idx1 = getappdata(0,'idx1'); 
imshow(label2rgb(idx1));
title("Rešenje");
impixelinfo;


function editCluster_Callback(hObject, eventdata, handles)
% hObject    handle to editCluster (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editCluster as text
%        str2double(get(hObject,'String')) returns contents of editCluster as a double


% --- Executes during object creation, after setting all properties.
function editCluster_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editCluster (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbuttonResult.
function pushbuttonResult_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonResult (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

x = getappdata(0,'picture');
selectClusterTxt = get(handles.editCluster,'String');  
selectCluster = str2num(selectClusterTxt);

idx = getappdata(0,'pictureDBSCAN');

idx1=idx;
idx1(idx==selectCluster)=0;

B=imbinarize(idx1);
A=~B;
area_opened=imdilate(A,ones (6,6));

figure;
subplot(2,2,1); imshow(idx1); title('idx1');
subplot(2,2,2); imshow(B); title('B');
subplot(2,2,3); imshow(A); title('A');
subplot(2,2,4); imshow(area_opened); title('area opened');
impixelinfo;

figure;
Aseg1 = zeros(size(x),"like",x);
Aseg2 = zeros(size(x),"like",x);
BW = area_opened == 1;
BW = repmat(BW,[1 1 3]);
Aseg1(BW) = x(BW);
Aseg2(~BW) = x(~BW);
final = montage({Aseg1,Aseg2});
impixelinfo;

axes(handles.axes4);
montage({Aseg1,Aseg2})

set(handles.pushbuttonRpicture,'Visible','on');
set(handles.axes4,'Visible','on');
setappdata(0,'Final',final);
setappdata(0,'idx1',idx1);
