function varargout = Pocetak(varargin)
% POCETAK MATLAB code for Pocetak.fig
%      POCETAK, by itself, creates a new POCETAK or raises the existing
%      singleton*.
%
%      H = POCETAK returset(handles.pushbutton2,'Enable','off');
%      the existing singleton*.
%
%      POCETAK('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in POCETAK.M with the given input arguments.
%
%      POCETAK('Property','Value',...) creates a new POCETAK or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Pocetak_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Pocetak_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Pocetak

% Last Modified by GUIDE v2.5 20-Jun-2023 23:58:15

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Pocetak_OpeningFcn, ...
                   'gui_OutputFcn',  @Pocetak_OutputFcn, ...
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


% --- Executes just before Pocetak is made visible.
function Pocetak_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Pocetak (see VARARGIN)
clc
% Choose default command line output for Pocetak
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);
set(handles.pushbutton2,'Enable','off');
set(handles.pushbutton3,'Enable','off');
set(handles.axes1,'Visible','off');

% UIWAIT makes Pocetak wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Pocetak_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
[filename, pathname] = uigetfile('*.*', 'Pick a MATLAB code file');
    if isequal(filename,0) || isequal(pathname,0)
       disp('User pressed cancel')
    else
       filename=strcat(pathname,filename);
       x=imread(filename);
       axes(handles.axes1);
       
imshow(x);
set(handles.pushbutton2,'Enable','on');
set(handles.pushbutton3,'Enable','on');
%ba=imread('C:\Users\stefa\OneDrive\Радна површина\etf\SDOS\matlab vezbanje\water_body_3.jpg');
setappdata(0,'picture',x);
%setappdata(0,'picture1',ba);
set(handles.axes1,'Visible','on');
    end

  


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%strGui2 = ('C:\Users\stefa\OneDrive\Радна површина\etf\Gabor.fig'); %Set your GUI file's location
%open (strGui2); %Open the new GUI 
%closereq; 
Morfoloskeoperacije;
set(Pocetak, 'Visible', 'Off');
closereq;


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%strGui2 = ('C:\Users\stefa\OneDrive\Радна површина\etf\Gabor.fig'); %Set your GUI file's location
%open (strGui2); %Open the new GUI 
%set(Pocetak, 'Visible', 'Off');
%closereq;       %Close the actual GUI
Gabor;
set(Pocetak, 'Visible', 'Off');
closereq;
