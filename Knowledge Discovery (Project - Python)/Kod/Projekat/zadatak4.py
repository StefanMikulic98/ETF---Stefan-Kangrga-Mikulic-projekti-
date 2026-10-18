import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import mysql.connector
import warnings
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression

#FUNCTIONS FOR ML

max = []
min = []
coef_finally = []

def mse(coef, x, y):
    # # print('MSE dot5: ', np.mean(np.power(((np.dot(x, coef.transpose())) - y), 2)) / 2)
    # # print('dot5 length: ', (np.mean(np.power(((np.dot(x, coef.transpose())) - y), 2)) / 2).shape)
    # print('MSE dot5: ', ((np.power(((np.dot(x, coef.transpose())) - y), 2)) / 2).sum()/my_data.shape[0])
    # print('dot5 length: ', (((np.power(((np.dot(x, coef.transpose())) - y), 2)) / 2).sum()/my_data.shape[0]).shape)

    return np.sum(((np.power(((np.dot(x, coef.transpose())) - y), 2)) / 2))/x.shape[0]

########################################################################################################################
def gradients(coef, x, y):
    # print('dot4 length: ', ((np.dot(x.transpose(), (np.dot(x, coef.transpose()) - y)))/my_data.shape[1]).shape)
    # return (np.dot(x.transpose(), (np.dot(x, coef.transpose()) - y)))/my_data.shape[1]

    result_delta = np.array([])
    new_matrix = np.dot(x, coef.transpose()) - y
    index1 = x.shape[1]
    for i in range(index1):
        ## print('gradients hx - y: ', (np.dot(x, coef.transpose()) - y))
        ## print('hx - y length: ', (np.dot(x, coef.transpose()) - y).shape)
        ## print('gradients x: ', x)
        ## print('x length: ', x.shape)
        ## print('gradients xi: ', x[:, i])
        ## print('xi length: ', (x[:, i]).shape)
        ## print('gradients new_matrix: ', np.dot(x, coef.transpose()) - y)
        ## print('new_matrix length: ', (np.dot(x, coef.transpose()) - y).shape)
        ## print('gradients sum new_delta: ', (np.dot(x, coef.transpose()) - y) * x[0:][i].sum())
        ## print('sum new_delta length: ', ((np.dot(x, coef.transpose()) - y) * x[0:][i].sum()).shape)
        ## print('gradients / new_delta: ', ((np.dot(x, coef.transpose()) - y) * x[0:][i].sum())/my_data.shape[0])
        ## print('/ new_delta length: ', (((np.dot(x, coef.transpose()) - y) * x[0:][i].sum())/my_data.shape[0]).shape)

        sum = 0.0
        index2 = x.shape[0]
        # print('i:::', i)
        for j in range(index2):
            sum += new_matrix[j, 0] * x[j, i]
            # print('sum:::', new_matrix[j, 0], ' + ', x[j, i])
        # new_delta = ((np.dot(x, coef.transpose()) - y) * x[0:][i].sum())/my_data.shape[0]
        # result = np.array([new_delta])
        sum /= x.shape[0]
        result = np.array([sum])
        result_delta = np.append(result_delta, result, axis= 0)
    # print('gradients result_delta: ', result_delta.transpose())
    # print('result_delta length: ', (result_delta.transpose()).shape)
    return result_delta.transpose()

########################################################################################################################
def multilinear_regression(text_widget, coef, x, y, lr, b1=0.9, b2=0.999, epsilon=1e-5):
    prev_error = 0

    while True:
        error = mse(coef, x, y)
        text_widget.insert("1.0", error)
        text_widget.insert("1.0", '\n')
        print('Loss:', error)
        if abs(error - prev_error) <= epsilon:
            break
        prev_error = error
        grad = gradients(coef, x, y)

        delta = lr * grad
        regularisation_part1 = coef * lr * (0.5/x.shape[0])
        regularisation = coef - regularisation_part1
        coef = np.subtract(regularisation, delta.transpose())
    print('Kraj')
    return coef
########################################################################################################################

def predict(window, selected_parameters_list, data):

    print('=======================PRE PRIMENE ONE HOT ENCODING=========================')
    print(data)

    for selected_item in selected_parameters_list:
        if selected_item != 'year' and selected_item != 'page_number' and selected_item != 'format':
            data = pd.get_dummies(data, columns=[selected_item], dtype='int')

    print('=======================POSLE PRIMENE ONE HOT ENCODING=========================')

    i = 0
    for c in data.columns:
        while (i < len(data.columns)):
            data[c] = (data[c] - min[i]) / (max[i] - min[i])
            i = i + 1
            break

    print('My data length: ', len(data))

    Y_pred = np.dot(data, coef_finally.transpose())
    print('Y_pred: ', Y_pred)
    print('Velicina Y_pred: ', Y_pred.shape)

########################################################################################################################
def r2_score(Ypred, Y):

    print('sum/len', sum(Y)/len(Y))
    print('mean', np.average(Y))

    mean = np.average(Y)
    sum1 = np.sum((np.power(np.subtract(Ypred, mean), 2)))  # the sum of square(due to regression)
    # sum3 = np.sum((np.power(np.subtract(Y, Ypred), 2)))  # the sum of square(due to error)
    sum2 = np.sum((np.power(np.subtract(Y, mean), 2)))      # the sum of square(total)

    # print('1: ', np.subtract(Ypred, mean))
    # print('2: ', np.power(np.subtract(Ypred, mean), 2))

    print('sum1: ', np.sum((np.power(np.subtract(Ypred, mean), 2))))
    print('sum2: ', sum2)
    r2 = sum1/sum2

    return r2

##############################################################

def linear_regression(window, selected_parameters_list, text_widget):

    warnings.filterwarnings('ignore')
    connection = mysql.connector.connect(host='localhost',
            user='root',
            passwd='YOUR_PASSWORD_HERE',
            database='knjige')
    cursor = connection.cursor()
    column_names = ''
    for selected_item in selected_parameters_list:
        if selected_item == 'format':
            column_names = column_names + 'area' + ','
        else:
            column_names = column_names + selected_item + ','

    column_names += 'price'
    sql_script = "SELECT " + column_names + " FROM knjige"

    my_data = pd.read_sql(sql_script, con=connection)
    print('=======================PRE PRIMENE ONE HOT ENCODING=========================')
    print(my_data)

    for selected_item in selected_parameters_list:
        if selected_item != 'year' and  selected_item != 'page_number' and  selected_item != 'format':
            my_data = pd.get_dummies(my_data, columns=[selected_item], dtype='int')

    # my_data = pd.get_dummies(my_data, columns=['type'], dtype='int')
    # my_data = pd.get_dummies(my_data, columns=['category'], dtype='int')

    print('=======================POSLE PRIMENE ONE HOT ENCODING=========================')
    print('Nove kolone: ', my_data.columns)   #my_data.head()
    print('Broj kolona: ', my_data.shape[1])


    #NORMALIZACIJA
    colums = my_data.columns[0]
    max = [my_data[c].max() for c in my_data.columns]
    min = [my_data[c].min() for c in my_data.columns]
    print('Maksimalne vrednosti po kolonama: ', max)
    print('Minimalne vrednosti po kolonama: ', min)
    i = 0
    for c in my_data.columns:
        while(i<len(my_data.columns)):
            my_data[c]=(my_data[c]-min[i])/(max[i]-min[i])
            i=i+1
            break

    print('My data length: ', len(my_data))
    df = my_data.sample(frac=1)

    # Select ratio
    ratio = 0.75

    total_rows = df.shape[0]
    train_size = int(total_rows * ratio)

    # Split data into test and train
    train = df[0:train_size]
    test = df[train_size:]
    train_without_price = df[0:train_size].drop(columns = ['price'])
    test_without_price = df[train_size:].drop(columns = ['price'])

    print('Skup za obucavanje sa izlazom: ', train)
    print('Velicina skupa za obucavanje: ', train.shape)
    print('Skup za testiranje: ', test)
    print('Velicina skupa za testiranje sa izlazom: ', test.shape)


    X_train = np.matrix(train_without_price)
    X_train = np.concatenate((np.ones(X_train.shape[0])[:, np.newaxis], X_train), axis=1)
    Y_train = np.asarray(train["price"].values.tolist())
    Y_train = Y_train.reshape(len(Y_train), 1)

    X_test = np.matrix(test_without_price)
    X_test = np.concatenate((np.ones(X_test.shape[0])[:, np.newaxis], X_test), axis=1)
    #X_test = np.asarray(test[:test.shape[1]].values.tolist())
    #X_test = X_test.reshape(len(X_test), test.shape[1])
    Y_test = np.asarray(test["price"].values.tolist())
    Y_test = Y_test.reshape(len(Y_test), 1)


    print('X_train with w0: ', X_train)
    print('X_train length: ', X_train.shape)
    print('Y_train: ', Y_train)
    print('Y_train length: ', Y_train.shape)

    print('X_test with w0: ', X_test)
    print('X_test length: ', X_test.shape)
    print('Y_test: ', Y_test)
    print('Y_test length: ', Y_test.shape)

    # coef = np.zeros((1, X_train.shape[1]))
    #Randomizacija pocetnih parametara modela
    coef = np.random.randint(low=12, high=16, size=(1, X_train.shape[1]))
    coef = 0.01 * coef
    print('Pocetni parametri modela: ', coef)
    print('coef length: ', coef.shape)

    coef_finally = multilinear_regression(text_widget, coef, X_train, Y_train, 1e-2)
    print('Konacni parametri modela: ', coef_finally )
    print('Velicina matrice: ', coef_finally.shape)

    Y_pred =  np.dot(X_train, coef_finally.transpose())
    print('Y_pred: ', Y_pred)
    print('Velicina Y_pred: ', Y_pred.shape)

    print('R2 score', r2_score(Y_pred,Y_train))

    fig = plt.figure(1)
    plt.plot(Y_train, label="True")
    plt.plot(Y_pred, label="Predicted")
    plt.xlabel("Sample")
    plt.ylabel("Price")
    plt.title("True vs Predicted Price")
    plt.legend()
    plt.show()


    Y_pred_test =  np.dot(X_test, coef_finally.transpose())
    print('Y_pred: ', Y_pred_test)
    print('Velicina Y_pred: ', Y_pred_test.shape)

    print('R2 score nad testnim podacima', r2_score(Y_pred_test,Y_test))

    # fig = plt.figure(2)
    # ax = fig.add_subplot() #projection='3d'
    # ax.plot(Y_train[0:,0], Y_pred[0:,0], color='k', label='Regression model')
    # ax.scatter(Y_train[0:,0], Y_pred[0:,0], edgecolor='k', facecolor='grey', alpha=0.7, label='Sample data')
    #
    #
    # # ax.scatter(X_train, Y_pred, label='y', s=5)
    # ax.legend()
    # ax.view_init(45, 0)
    #
    # plt.show()



    # canvas = FigureCanvasTkAgg(fig, master=window)
    # canvas.draw()
    # canvas.get_tk_widget().pack()
    # toolbar = NavigationToolbar2Tk(canvas, window)
    # toolbar.update()
    # canvas.get_tk_widget().pack()
####################################################################
# # Pravo resenje
#
# # Create an instance of the LinearRegression class
# reg = LinearRegression()
#
# # Fit the model to the data
# reg.fit(X_train, Y_train)
#
# # Print the coefficients of the model
# print(reg.coef)
#####################################################################