import numpy as np
import matplotlib.pyplot as plt
import random
import mysql.connector
import pandas as pd
from sklearn import preprocessing
from sklearn.decomposition import PCA
import seaborn as sns
import warnings


def random_centers(dim,k):
    centers = []
    for i in range(k):
        center = []
        for d in range(dim):
            rand = random.randint(0,100)
            center.append(rand)
        centers.append(center)
    return centers

def point_clustering(data, centers, dims, first_cluster=False):
    for point in data:
        nearest_center = 0
        nearest_center_dist = None
        for i in range(0, len(centers)):
            euclidean_dist = 0
            for d in range(0, dims):
                dist = abs(point[d] - centers[i][d])
                euclidean_dist += dist
            euclidean_dist = np.sqrt(euclidean_dist)
            if nearest_center_dist == None:
                nearest_center_dist = euclidean_dist
                nearest_center = i
            elif nearest_center_dist > euclidean_dist:
                nearest_center_dist = euclidean_dist
                nearest_center = i
        if first_cluster:
            point.append(nearest_center)
        else:
            point[-1] = nearest_center
    return data


def mean_center(data, centers, dims):
    print('centers:', centers, 'dims:', dims)
    new_centers = []
    for i in range(len(centers)):
        new_center = []
        n_of_points = 0
        total_of_points = []
        for point in data:
            if point[-1] == i:
                n_of_points += 1
                for dim in range(0, dims):
                    if dim < len(total_of_points):
                        total_of_points[dim] += point[dim]
                    else:
                        total_of_points.append(point[dim])
        if len(total_of_points) != 0:
            for dim in range(0, dims):
                # print(total_of_points, dim)
                new_center.append(total_of_points[dim] / n_of_points)
            new_centers.append(new_center)
        else:
            new_centers.append(centers[i])

    return new_centers


# Gets data and k, returns a list of center points.
def train_k_means_clustering(data, k=2, epochs=5):
    dims = len(data[0])
    print('data[0]:', data[0])
    centers = random_centers(dims, k)

    clustered_data = point_clustering(data, centers, dims, first_cluster=True)

    for i in range(epochs):
        centers = mean_center(clustered_data, centers, dims)
        clustered_data = point_clustering(data, centers, dims, first_cluster=False)

    return centers


def predict_k_means_clustering(point, centers):
    dims = len(point)
    center_dims = len(centers[0])

    if dims != center_dims:
        raise ValueError('Point given for prediction have', dims, 'dimensions but centers have', center_dims,
                         'dimensions')

    nearest_center = None
    nearest_dist = None

    for i in range(len(centers)):
        euclidean_dist = 0
        for dim in range(1, dims):
            dist = point[dim] - centers[i][dim]
            euclidean_dist += dist ** 2
        euclidean_dist = np.sqrt(euclidean_dist)
        if nearest_dist == None:
            nearest_dist = euclidean_dist
            nearest_center = i
        elif nearest_dist > euclidean_dist:
            nearest_dist = euclidean_dist
            nearest_center = i
        print('center:', i, 'dist:', euclidean_dist)

    return nearest_center

def kmeans(window, selected_parameters_list, epochs, k):
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
    # print('=======================PRE PRIMENE ONE HOT ENCODING=========================')
    # print(my_data)
    #
    # for selected_item in selected_parameters_list:
    #     if selected_item != 'year' and selected_item != 'page_number' and selected_item != 'format':
    #         my_data = pd.get_dummies(my_data, columns=[selected_item], dtype='int')
    #
    # print('=======================POSLE PRIMENE ONE HOT ENCODING=========================')
    print('=======================PRE PRIMENE ONE HOT ENCODING=========================')
    print(my_data)

    for selected_item in selected_parameters_list:
        if selected_item != 'year' and selected_item != 'page_number' and selected_item != 'format':
            label = 0
            values = my_data[selected_item].unique()
            for value in values:
                my_data[selected_item].replace({value: label}, inplace=True)
                label += 1

    print('=======================POSLE PRIMENE LABEL ENCODING=========================')
    print(my_data)

    # NORMALIZACIJA
    colums = my_data.columns[0]
    max = [my_data[c].max() for c in my_data.columns]
    min = [my_data[c].min() for c in my_data.columns]
    print('Maksimalne vrednosti po kolonama: ', max)
    print('Minimalne vrednosti po kolonama: ', min)
    i = 0
    for c in my_data.columns:
        while (i < len(my_data.columns)):
            my_data[c] = (my_data[c] - min[i]) / (max[i] - min[i])
            i = i + 1
            break

    print('My data length: ', len(my_data))
    df = my_data.sample(frac=1)

    X = np.matrix(df).tolist()
    # print(X)
    print('X: ', len(X))
    centers = train_k_means_clustering(X, k, epochs)
    print(centers)

    plotx = []
    ploty = []
    plot_num = 1
    rows = int(((len(X[0])-1)*(len(X[0])-2))/8)
    if rows != ((len(X[0])-1)*(len(X[0])-2))/8:
        rows += 1
    columns = 4
    for i in range(0, len(X[0])-2):
        for j in range(1, len(X[0])-1):
            if j > i:
                for k in range(len(X)):
                    plotx.append(X[k][i])
                    ploty.append(X[k][j])
                fig = plt.subplot(rows, columns, plot_num)
                plt.plot(plotx, ploty, 'bo')
                plt.xlabel(my_data.columns[i],fontsize=10)
                plt.ylabel(my_data.columns[j],fontsize=10)
                plt.subplots_adjust(hspace=1)
                for center in centers:
                    plt.plot(center[i], center[j], 'ro')
                plot_num += 1

    pca_num_components = 2

    # reduced_data = PCA(n_components=pca_num_components).fit_transform(X)
    # results = pd.DataFrame(reduced_data, columns=['pca1', 'pca2'])
    #
    # sns.scatterplot(x="pca1", y="pca2", data=results) # hue=data['clusters'],

    plt.subplots_adjust(left=0.1,
                        bottom=0.1,
                        right=0.9,
                        top=0.9,
                        wspace=0.7,
                        hspace=0.4)
    plt.show()


if __name__=="__main__":
    X = [[100,5], [90,5], [110,5], [97,4], [102,4], [112,4], [92,4], [95,3], [90,3], [100,3],
         [110,5], [100,5], [110,4], [93,3], [107,2], [117,3], [96,2], [105,3], [100,3], [110,3],
         [60,-1], [70,-1],[40,1], [70,-3], [50,-1], [80,0],[50,0],[60,-1],[60,1],[55,0],
         [40,-1], [45,-1],[40,0], [55,-3], [60,-1], [65,0],[70,0],[51,-2],[51,1],[48,0]]
    print(X)
    centers = train_k_means_clustering(X, k=2, epochs=5)
    print(centers)
    point = [110,3]
    print(predict_k_means_clustering(point, centers))

    plotx = []
    ploty = []
    for i in range(len(X)):
        plotx.append(X[i][0])
        ploty.append(X[i][1])
    plt.plot(plotx, ploty, 'bo')
    plt.plot(plotx,ploty, 'bo', centers[0][0], centers[0][1],'ro', centers[1][0], centers[1][1], 'go', point[0], point[1], 'yo')
    plt.show()