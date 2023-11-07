function varargout = Morfoloskeoperacije(varargin)
% MORFOLOSKEOPERACIJE MATLAB code for Morfoloskeoperacije.fig
%      MORFOLOSKEOPERACIJE, by itself, creates a new MORFOLOSKEOPERACIJE or raises the existing
%      singleton*.
%
%      H = MORFOLOSKEOPERACIJE returns the handle to a new MORFOLOSKEOPERACIJE or the handle to
%      the existing singleton*.
%
%      MORFOLOSKEOPERACIJE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MORFOLOSKEOPERACIJE.M with the given input arguments.
%
%      MORFOLOSKEOPERACIJE('Property','Value',...) creates a new MORFOLOSKEOPERACIJE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Morfoloskeoperacije_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Morfoloskeoperacije_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Morfoloskeoperacije

% Last Modified by GUIDE v2.5 25-Jun-2023 22:57:41

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Morfoloskeoperacije_OpeningFcn, ...
                   'gui_OutputFcn',  @Morfoloskeoperacije_OutputFcn, ...
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


% --- Executes just before Morfoloskeoperacije is made visible.
function Morfoloskeoperacije_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Morfoloskeoperacije (see VARARGIN)
clc
%set(handles.pushbuttonGray,'Enable','off');
set(handles.pushbuttonGray,'Enable','on');
set(handles.pushbuttonGrayShow,'Enable','off');
set(handles.pushbuttonAdapthisteq,'Enable','off');
set(handles.pushbuttonAdapthisteqShow,'Enable','off');
set(handles.pushbuttonEntropyfilt,'Enable','off');
set(handles.pushbuttonEntropyfiltShow,'Enable','off');
set(handles.pushbuttonImbinarize,'Enable','off');
set(handles.pushbuttonImbinarizeShow,'Enable','off');
set(handles.pushbuttonBwareaopen,'Enable','off');
set(handles.pushbuttonBwareaopenShow,'Enable','off');
set(handles.pushbuttonImclose,'Enable','off');
set(handles.pushbuttonImcloseShow,'Enable','off');
set(handles.pushbuttonImclose,'Enable','off');
set(handles.pushbuttonImcloseShow,'Enable','off');
set(handles.pushbuttonImfill,'Enable','off');
set(handles.pushbuttonImfillShow,'Enable','off');
set(handles.pushbuttonImdilate,'Enable','off');
set(handles.pushbuttonImdilateShow,'Enable','off');
set(handles.axes2,'Visible','off');
set(handles.axes3,'Visible','off');
set(handles.axes4,'Visible','off');
set(handles.axes5,'Visible','off');
set(handles.axes6,'Visible','off');
set(handles.axes7,'Visible','off');
set(handles.axes8,'Visible','off');
set(handles.axes9,'Visible','off');
axis off ;
x = getappdata(0,'picture');
axes(handles.axes1);       
imshow(x);
% Choose default command line output for Morfoloskeoperacije
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Morfoloskeoperacije wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Morfoloskeoperacije_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbuttonNewPic.
function pushbuttonNewPic_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonNewPic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
x = getappdata(0,'picture'); 
imshow(x);
title("Početna slika");
impixelinfo;

% --- Executes on button press in pushbuttonGray.
function pushbuttonGray_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonGray (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
x = getappdata(0,'picture'); 
Agray = rgb2gray(x);

axes(handles.axes2);       
imshow(Agray);

setappdata(0,'grayscale',Agray);
set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonGray,'Enable','off');
set(handles.pushbuttonGrayShow,'Enable','on');
set(handles.axes2,'Visible','on');



% --- Executes on button press in pushbuttonGrayShow.
function pushbuttonGrayShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonGrayShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
Agray = getappdata(0,'grayscale'); 
imshow(Agray);
title("Gray scale");
impixelinfo;

% --- Executes on button press in pushbuttonAdapthisteq.
function pushbuttonAdapthisteq_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonAdapthisteq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Agray = getappdata(0,'grayscale');  
Ieq = adapthisteq(Agray);

axes(handles.axes3);       
imshow(Ieq);

setappdata(0,'adapthisteq',Ieq);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonAdapthisteq,'Enable','off');
set(handles.pushbuttonAdapthisteqShow,'Enable','on');
set(handles.axes3,'Visible','on');


% --- Executes on button press in pushbuttonAdapthisteqShow.
function pushbuttonAdapthisteqShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonAdapthisteqShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
Ieq = getappdata(0,'adapthisteq'); 
imshow(Ieq);
title("adapthisteq");
impixelinfo;

% --- Executes on button press in pushbuttonEntropyfilt.
function pushbuttonEntropyfilt_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonEntropyfilt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
true = get(handles.checkboxAdapthisteq,'value');

if true == 1
    Ieq = getappdata(0,'adapthisteq');
    E=rescale(entropyfilt(Ieq));
else
    Agray = getappdata(0,'grayscale'); 
    E=rescale(entropyfilt(Agray));
end

axes(handles.axes4);       
imshow(E);

setappdata(0,'entropyfilt',E);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonEntropyfilt,'Enable','off');
set(handles.pushbuttonEntropyfiltShow,'Enable','on');
set(handles.pushbuttonImbinarize,'Enable','on');
set(handles.axes4,'Visible','on');

% --- Executes on button press in pushbuttonEntropyfiltShow.
function pushbuttonEntropyfiltShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonEntropyfiltShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
E = getappdata(0,'entropyfilt'); 
imshow(E);
title("entropyfilt");
impixelinfo;

% --- Executes on button press in pushbuttonImbinarize.
function pushbuttonImbinarize_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImbinarize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
E = getappdata(0,'entropyfilt');
valueTxt = get(handles.editImbinarize,'String'); 
value = str2num(valueTxt);

binary_image=imbinarize(E,value);

axes(handles.axes5);       
imshow(binary_image);

setappdata(0,'imbinarize',binary_image);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonImbinarizeShow,'Enable','on');
set(handles.pushbuttonBwareaopen,'Enable','on');
set(handles.axes5,'Visible','on');

% --- Executes on button press in pushbuttonImbinarizeShow.
function pushbuttonImbinarizeShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImbinarizeShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
binary_image = getappdata(0,'imbinarize'); 
imshow(binary_image);
title("imbinarize");
impixelinfo;

% --- Executes on button press in pushbuttonBwareaopen.
function pushbuttonBwareaopen_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonBwareaopen (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
binary_image = getappdata(0,'imbinarize');
valueTxt = get(handles.editBwareaopen,'String'); 
value = str2num(valueTxt);

area_opened=bwareaopen(binary_image,value);

axes(handles.axes6);       
imshow(area_opened);

setappdata(0,'bwareaopen',area_opened);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonBwareaopenShow,'Enable','on');
set(handles.pushbuttonImclose,'Enable','on');
set(handles.axes6,'Visible','on');


% --- Executes on button press in pushbuttonBwareaopenShow.
function pushbuttonBwareaopenShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonBwareaopenShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
area_opened = getappdata(0,'bwareaopen'); 
imshow(area_opened);
title("bwareaopen");
impixelinfo;

% --- Executes on button press in pushbuttonImclose.
function pushbuttonImclose_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImclose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
area_opened = getappdata(0,'bwareaopen');
valueTxt = get(handles.editImclose,'String'); 
value = str2num(valueTxt);

st=strel('square',value);
area_opened1=imclose(area_opened,st);

axes(handles.axes7);       
imshow(area_opened1);

setappdata(0,'imclose',area_opened1);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonImcloseShow,'Enable','on');
set(handles.pushbuttonImfill,'Enable','on');
set(handles.axes7,'Visible','on');

% --- Executes on button press in pushbuttonImfill.
function pushbuttonImfill_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImfill (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
area_opened1 = getappdata(0,'imclose');
Agray = getappdata(0,'grayscale');

hole_filling=imfill(area_opened1,'holes');
etc_part=Agray.*uint8(hole_filling);
water_part=Agray.*uint8(~hole_filling);

axes(handles.axes8);       
imshow(water_part);

setappdata(0,'hole_filling',hole_filling);
setappdata(0,'etc_part',etc_part);
setappdata(0,'water_part',water_part);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonImfillShow,'Enable','on');
set(handles.pushbuttonImdilate,'Enable','on');
set(handles.axes8,'Visible','on');

% --- Executes on button press in pushbuttonImfillShow.
function pushbuttonImfillShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImfillShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
etc_part = getappdata(0,'etc_part'); 
water_part = getappdata(0,'water_part'); 
subplot(1,2,1); imshow(etc_part); title('Ostalo');
subplot(1,2,2); imshow(water_part); title('Vodene povrsine');
impixelinfo;

% --- Executes on button press in pushbuttonImcloseShow.
function pushbuttonImcloseShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImcloseShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
area_opened1 = getappdata(0,'imclose'); 
imshow(area_opened1);
title("imclose");
impixelinfo;

% --- Executes on button press in pushbuttonImdilate.
function pushbuttonImdilate_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImdilate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Agray = getappdata(0,'grayscale');
hole_filling = getappdata(0,'hole_filling');
valueTxt = get(handles.editImdilate,'String'); 
value = str2num(valueTxt);

peri=imdilate(bwperim(hole_filling),strel('disk',value));

axes(handles.axes9);       
imshow(labeloverlay(Agray,peri,"Colormap",[1 1 0]));

setappdata(0,'imdilate',peri);
%set(handles.pushbuttonEntropyfilt,'Enable','on');
set(handles.pushbuttonImdilateShow,'Enable','on');
set(handles.axes9,'Visible','on');

% --- Executes on button press in pushbuttonImdilateShow.
function pushbuttonImdilateShow_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonImdilateShow (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
figure;
Agray = getappdata(0,'grayscale');
peri = getappdata(0,'imdilate'); 
imshow(labeloverlay(Agray,peri,"Colormap",[1 1 0]));
title("imclose");
impixelinfo;

% --- Executes on button press in pushbuttonPocetak.
function pushbuttonPocetak_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonPocetak (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Pocetak;
set(Morfoloskeoperacije, 'Visible', 'Off');
closereq;

% --- Executes on button press in pushbuttonReset.
function pushbuttonReset_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonReset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in checkboxAdapthisteq.
function checkboxAdapthisteq_Callback(hObject, eventdata, handles)
% hObject    handle to checkboxAdapthisteq (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
true = get(handles.checkboxAdapthisteq,'value');

if true == 1
    set(handles.pushbuttonAdapthisteq,'Enable','on');
    %set(handles.pushbuttonAdapthisteqShow,'Enable','on');
else
    set(handles.pushbuttonAdapthisteq,'Enable','off');
    set(handles.pushbuttonAdapthisteqShow,'Enable','off');
end
% Hint: get(hObject,'Value') returns toggle state of checkboxAdapthisteq



function editImbinarize_Callback(hObject, eventdata, handles)
% hObject    handle to editImbinarize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editImbinarize as text
%        str2double(get(hObject,'String')) returns contents of editImbinarize as a double


% --- Executes during object creation, after setting all properties.
function editImbinarize_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editImbinarize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editBwareaopen_Callback(hObject, eventdata, handles)
% hObject    handle to editBwareaopen (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editBwareaopen as text
%        str2double(get(hObject,'String')) returns contents of editBwareaopen as a double


% --- Executes during object creation, after setting all properties.
function editBwareaopen_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editBwareaopen (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editImclose_Callback(hObject, eventdata, handles)
% hObject    handle to editImclose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editImclose as text
%        str2double(get(hObject,'String')) returns contents of editImclose as a double


% --- Executes during object creation, after setting all properties.
function editImclose_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editImclose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function editImdilate_Callback(hObject, eventdata, handles)
% hObject    handle to editImdilate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of editImdilate as text
%        str2double(get(hObject,'String')) returns contents of editImdilate as a double


% --- Executes during object creation, after setting all properties.
function editImdilate_CreateFcn(hObject, eventdata, handles)
% hObject    handle to editImdilate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbuttonNewPicture.
function pushbuttonNewPicture_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonNewPicture (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname] = uigetfile('*.*', 'Pick a MATLAB code file');
    if isequal(filename,0) || isequal(pathname,0)
       disp('User pressed cancel')
    else
       filename=strcat(pathname,filename);
       x=imread(filename);
       axes(handles.axes1);
       set(handles.pushbuttonGray,'Enable','on');
       set(handles.pushbuttonGrayShow,'Enable','off');
       set(handles.pushbuttonAdapthisteq,'Enable','off');
       set(handles.pushbuttonAdapthisteqShow,'Enable','off');
       set(handles.pushbuttonEntropyfilt,'Enable','off');
       set(handles.pushbuttonEntropyfiltShow,'Enable','off');
       set(handles.pushbuttonImbinarize,'Enable','off');
       set(handles.pushbuttonImbinarizeShow,'Enable','off');
       set(handles.pushbuttonBwareaopen,'Enable','off');
       set(handles.pushbuttonBwareaopenShow,'Enable','off');
       set(handles.pushbuttonImclose,'Enable','off');
       set(handles.pushbuttonImcloseShow,'Enable','off');
       set(handles.pushbuttonImclose,'Enable','off');
       set(handles.pushbuttonImcloseShow,'Enable','off');
       set(handles.pushbuttonImfill,'Enable','off');
       set(handles.pushbuttonImfillShow,'Enable','off');
       set(handles.pushbuttonImdilate,'Enable','off');
       set(handles.pushbuttonImdilateShow,'Enable','off');
       set(handles.axes2,'Visible','off');
       set(handles.axes3,'Visible','off');
       set(handles.axes4,'Visible','off');
       set(handles.axes5,'Visible','off');
       set(handles.axes6,'Visible','off');
       set(handles.axes7,'Visible','off');
       set(handles.axes8,'Visible','off');
       set(handles.axes9,'Visible','off');
       imshow(x);
       setappdata(0,'picture',x);
    end
