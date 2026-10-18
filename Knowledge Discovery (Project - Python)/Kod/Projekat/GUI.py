from tkinter import *
from threading import Thread
from tkinter import ttk
from zadatak2 import zadatak2
from zadatak3 import zadatak3
from zadatak4 import linear_regression
from zadatak4 import predict
from KMeans import kmeans
from PIL import Image
from tkinter.scrolledtext import ScrolledText
import os
import openpyxl
import xlwings

def openExcel():
    # workbook = openpyxl.load_workbook('excel1.xlsx')
    # type(workbook)
    excel_app = xlwings.App(visible=True)
    file = xlwings.Book('excel1.xlsx')

def analiza():
    # Call work function
    t1 = Thread(target=zadatak2)
    t1.start()

def vizuelizacija():
    # Call work function
    button2.config(bg='red')
    t2 = Thread(target=zadatak3)
    t2.start()
    button2.config(bg='white')


def openCharts():
    # workbook = openpyxl.load_workbook('excel1.xlsx')
    # type(workbook)
    # excel_app = xlwings.App(visible=True)
    # file = xlwings.Chart('chart_Number of Books for each Category.png')
    im1 = Image.open('Number of Books for each Publisher.png')
    im2 = Image.open('Number of Books for each Category.png')
    im3 = Image.open('Number of Books for each time category.png')
    im4 = Image.open('Number of Books for the Top 5 Publishers.png')
    im5 = Image.open('Percentage of Total Books for the Top 5 Publishers.png')
    im6 = Image.open('Number of Books for the price.png')
    im7 = Image.open('Percentage of Total Books for the price.png')
    im8 = Image.open('Number of Books for the type Tvrd povez.png')
    im9 = Image.open('Percentage of Total Books for the type Tvrd povez.png')

    im1.show()
    im2.show()
    im3.show()
    im4.show()
    im5.show()
    im6.show()
    im7.show()
    im8.show()
    im9.show()
def threading(window, selected_parameters_list, text_widget):
    # Call work function
    t3 = Thread(target=lambda: linear_regression(window, selected_parameters_list, text_widget))
    t3.start()

def test(window, selected_parameters_list):
    # Call work function
    data = []
    for selected_item in selected_parameters_list:
        match selected_item:
            case 'authors':
                data.append(input_authors.get(1.0, "end-1c"))
            case 'category':
                data.append(input_category.get(1.0, "end-1c"))
            case 'publisher':
                data.append(input_publisher.get(1.0, "end-1c"))
            case 'year':
                data.append(int(input_year.get(1.0, "end-1c")))
            case 'format':
                selected_item = 'area'
                data.append(int(input_format.get(1.0, "end-1c")))
            case 'type':
                data.append(input_type.get(1.0, "end-1c"))
            case 'page_number':
                data.append(int(input_page_number.get(1.0, "end-1c")))
    t5 = Thread(target=lambda: predict(window, selected_parameters_list, data))
    t5.start()

def k_means(window, selected_parameters_list):
    # Call work function
    epochs = int(input_epochs.get(1.0, "end-1c"))
    k = int(input_k.get(1.0, "end-1c"))
    t4 = Thread(target=lambda: kmeans(window, selected_parameters_list, epochs, k))
    t4.start()

def process(var, text):
    try:
        val = int(var.get())
    except ValueError:
        val = var.get()

    if val:
        selected_parameters_list.append(val)
    else:
        selected_parameters_list.remove(text)

    print(selected_parameters_list)


if __name__=="__main__":
    window = Tk()
    window.geometry("1000x500")
    window.title("Welcome")

    # label1 = Label(window, text="PSZ", fg='blue', bg='yellow', relief="solid", font=("arial", 12, "bold"))
    # label1.pack()
    # # label1.place(x=90, y=50)

    button1 = Button(window, text="Analiza podataka", fg='black', bg='white', relief=RIDGE, font=("arial", 12, "bold"),command=analiza)
    button1.pack()
    button1.place(x=300, y=20)

    button11 = Button(window, text="Rezultati", fg='black', bg='white', relief=RIDGE, font=("arial", 12, "bold"),command=openExcel)
    button11.pack()
    button11.place(x=650, y=20)

    # Separator object
    separator1 = ttk.Separator(window, orient='horizontal')
    separator1.place(x=0.1, y=60, relwidth=1, relheight=0.8)

    button2 = Button(window, text="Vizuelizacija podataka", fg='black', bg='white', relief=RIDGE, font=("arial", 12, "bold"),command=vizuelizacija)
    button2.pack()
    button2.place(x=300, y=70)

    button11 = Button(window, text="Rezultati", fg='black', bg='white', relief=RIDGE, font=("arial", 12, "bold"),command=openCharts)
    button11.pack()
    button11.place(x=650, y=70)

    # Separator object
    separator2 = ttk.Separator(window, orient='horizontal')
    separator2.place(x=0.1, y=110, relwidth=1, relheight=0.8)

    button3 = Button(window, text="Linearna regresija", fg='black', bg='white', relief=RIDGE, font=("arial", 12, "bold"), command=lambda: threading(window, selected_parameters_list, text_widget))
    button3.pack()
    button3.place(x=300, y=120)

    button5 = Button(window, text="Test", fg='black', bg='white', relief=RIDGE,font=("arial", 12, "bold"),command=lambda: test(window, selected_parameters_list))
    button5.pack()
    button5.place(x=650, y=120)

    text_widget = ScrolledText(window, height=7, width=50, wrap="word")
    text_widget.pack()
    text_widget.place(x=310, y=230)
    # ScrolledText(text_widget).pack()

    selected_parameters_list = []
    parameters = ['authors', 'category', 'publisher', 'year', 'format', 'type', 'page_number']

    position = 40
    for idx, i in enumerate(parameters):
        var = StringVar(value=" ")
        cb = Checkbutton(window, text=i, variable=var, command=lambda i=i, var=var: process(var, i), onvalue=i)
        position = position + 100
        # cb.pack(padx=position, pady=10)
        # cb.grid(row=1, column=0)
        # position = 5*idx
        cb.place(x=position, y=170)

    input_authors = Text(window,height=1, width=7)
    input_category = Text(window,height=1, width=7)
    input_publisher = Text(window,height=1, width=7)
    input_year = Text(window,height=1, width=7)
    input_format = Text(window, height=1, width=7)
    input_type = Text(window, height=1, width=7)
    input_page_number = Text(window, height=1, width=7)
    input_authors.pack()
    input_authors.place(x=145, y=195)
    input_category.pack()
    input_category.place(x=245, y=195)
    input_publisher.pack()
    input_publisher.place(x=345, y=195)
    input_year.pack()
    input_year.place(x=445, y=195)
    input_format.pack()
    input_format.place(x=545, y=195)
    input_type.pack()
    input_type.place(x=645, y=195)
    input_page_number.pack()
    input_page_number.place(x=745, y=195)

    # Separator object
    separator3 = ttk.Separator(window, orient='horizontal')
    separator3.place(x=0.1, y=400, relwidth=1, relheight=0.8)

    button4 = Button(window, text="K means", fg='black', bg='white', relief=RIDGE,font=("arial", 12, "bold"),command=lambda: k_means(window, selected_parameters_list))
    button4.pack()
    button4.place(x=460, y=410)

    input_epochs = Text(window, height=1, width=7)
    input_k = Text(window, height=1, width=7)
    input_epochs.pack()
    input_epochs.place(x=420, y=460)
    input_k.pack()
    input_k.place(x=540, y=460)

    input_epochs.insert(END, """Epochs""")
    input_k.insert(END, """K""")

    window.mainloop()
