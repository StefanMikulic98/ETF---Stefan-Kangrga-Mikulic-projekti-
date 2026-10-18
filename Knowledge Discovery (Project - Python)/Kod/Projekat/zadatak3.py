import mysql.connector
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import warnings
import time
import os
from threading import Thread


from pandas import DataFrame

def newPlot(sql, connection, fig,xlabel, ylabel, title):
    #fig = plt.figure(figure_number)
    df = pd.read_sql(sql, con=connection)
    if xlabel=='total_books':
        print("DF::::::::::::::::", df)
    #ax = fig.add_subplot(3, 2, idx)
    sns.barplot(x=xlabel, y=ylabel, data=df,  hue=ylabel, palette='viridis')
    plt.xlabel('X Label')
    plt.ylabel('Y Label')

    plt.title(title )
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    fig.show()
    fig.savefig('chart_'+title+'.png')

# def kraj():
#     time.sleep(5)
#     os._exit(1)

def zadatak3():
    #try:
    connection = mysql.connector.connect(host='localhost',
            user='root',
            passwd='YOUR_PASSWORD_HERE',
            database='knjige')
    cursor = connection.cursor()
    warnings.filterwarnings('ignore')


    sql_get_number_publisher = "SELECT publisher, COUNT(*) as book_count FROM knjige GROUP BY publisher ORDER BY book_count DESC LIMIT 10"
    sql_get_number_category = "SELECT category, COUNT(*) as book_count FROM knjige GROUP BY category ORDER BY book_count DESC"
    sql_get_number_time_case = "SELECT CASE WHEN year BETWEEN 1961 AND 1970 THEN '1961-1970' WHEN year BETWEEN 1971 AND 1980 THEN '1971-1980' WHEN year BETWEEN 1981 AND 1990 THEN '1981-1990' WHEN year BETWEEN 1991 AND 2000 THEN '1991-2000' WHEN year BETWEEN 2001 AND 2010 THEN '2001-2010' WHEN year BETWEEN 2011 AND 2020 THEN '2011-2020' ELSE '2021-present' END AS decade, COUNT(*) as book_count FROM knjige GROUP BY decade ORDER BY decade"
    # sql_get_number_prices = "WITH Top5Publishers AS ( SELECT publisher, COUNT(*) AS count FROM knjige GROUP BY publisher ORDER BY count DESC LIMIT 5) SELECT b.publisher, COUNT(*) AS total_books, ROUND(SUM(CASE WHEN b.sold = 1 THEN 1 ELSE 0 END) / COUNT(*) * 100, 2) AS percentage_sold FROM knjige b JOIN Top5Publishers t5 ON b.publisher = t5.publisher GROUP BY b.publisher ORDER BY books_sold DESC;"
    sql_get_number_books = "WITH TotalBooks AS (SELECT COUNT(*) AS total_books FROM knjige),Top5Publishers AS (SELECT publisher,COUNT(*) AS total_publisher_books FROM knjige GROUP BY publisher ORDER BY total_publisher_books DESC LIMIT 5) SELECT t5.publisher ,t5.total_publisher_books,ROUND((t5.total_publisher_books / tb.total_books) * 100, 2) AS percentage_of_total_books FROM Top5Publishers t5 CROSS JOIN TotalBooks tb ORDER BY t5.total_publisher_books DESC"
    sql_get_number_prices_category = """
    WITH TotalBooks AS (
        SELECT COUNT(*) AS total_books
        FROM knjige
    )
    
    SELECT 
        CASE 
            WHEN price <= 500 THEN 'less than or equal to 500 dinars'
            WHEN price BETWEEN 501 AND 1500 THEN 'between 501 and 1500 dinars'
            WHEN price BETWEEN 1501 AND 3000 THEN 'between 1501 and 3000 dinars'
            WHEN price BETWEEN 3001 AND 5000 THEN 'between 3001 and 5000 dinars'
            WHEN price BETWEEN 5001 AND 10000 THEN 'between 5001 and 10000 dinars'
            WHEN price BETWEEN 10001 AND 15000 THEN 'between 10001 and 15000 dinars'
            ELSE '15001 or more'
        END AS price_range,
        COUNT(*) AS book_count,
        ROUND(COUNT(*) / (SELECT total_books FROM TotalBooks) * 100, 2) AS percentage_of_total_books
    FROM 
        knjige
    GROUP BY 
        price_range
    ORDER BY 
        FIELD(price_range, 
               'less than or equal to 500 dinars',
               'between 501 and 1500 dinars',
               'between 1501 and 3000 dinars',
               'between 3001 and 5000 dinars',
               'between 5001 and 10000 dinars',
               'between 10001 and 15000 dinars',
               '15001 or more');
    """

    sql_get_number_type = """
    WITH TotalBooks AS (
        SELECT COUNT(*) AS total_books
        FROM knjige
        WHERE year >= 2021
    )
    
    SELECT 
        CASE 
            WHEN type = 'Tvrd' THEN 'Tvrd povez'
            ELSE 'Ostalo'
        END AS type_range,
        COUNT(*) AS book_count,
        ROUND(COUNT(*) / (SELECT total_books FROM TotalBooks) * 100, 2) AS percentage_of_total_books
    FROM 
        knjige
     WHERE year >= 2021
    GROUP BY 
        type_range
    ORDER BY 
        FIELD(type_range, 
               'Tvrd povez',
               'Ostalo');
    """

    # cursor.execute(sql_get_number_publisher)
    # records = cursor.fetchall()

    fig = plt.figure(1)
    newPlot(sql_get_number_publisher, connection, fig, 'book_count','publisher','Number of Books for each Publisher')
    fig.show()
    fig = plt.figure(2)
    newPlot(sql_get_number_category, connection, fig,'book_count','category','Number of Books for each Category')
    fig.show()
    fig = plt.figure(3)
    newPlot(sql_get_number_time_case, connection, fig,'book_count','decade','Number of Books for each time category')
    fig.show()
    fig = plt.figure(4)
    newPlot(sql_get_number_books, connection, fig,'total_publisher_books','publisher','Number of Books for the Top 5 Publishers')
    fig.show()
    fig = plt.figure(5)
    newPlot(sql_get_number_books, connection, fig,'percentage_of_total_books','publisher','Percentage of Total Books for the Top 5 Publishers')
    fig.show()
    fig = plt.figure(6)
    newPlot(sql_get_number_prices_category, connection, fig,'book_count','price_range','Number of Books for the price')
    fig.show()
    fig = plt.figure(7)
    newPlot(sql_get_number_prices_category, connection, fig,'percentage_of_total_books','price_range','Percentage of Total Books for the price')
    fig.show()
    fig = plt.figure(8)
    newPlot(sql_get_number_type, connection, fig,'book_count','type_range','Number of Books for the type Tvrd povez')
    fig.show()
    fig = plt.figure(9)
    newPlot(sql_get_number_type, connection, fig,'percentage_of_total_books','type_range','Percentage of Total Books for the type Tvrd povez')
    fig.show()

    # t_3 = Thread(target=kraj)
    # t_3.start()
    # input()

    print('Kraj 3.zadatka')

    # except mysql.connector.Error as e:
    #     print("Error reading data from MySQL table", e)
    # finally:
    #     if connection.is_connected():
    #         connection.close()
    #         cursor.close()
    #         print("MySQL connection is closed")