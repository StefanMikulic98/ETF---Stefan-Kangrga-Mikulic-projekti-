import mysql.connector
import pandas as pd
from openpyxl import load_workbook
import os

def newRows(records, idx, idy):
    for line in records:
        new_data = [[line[0], line[1]]]
        wb = load_workbook('excel1.xlsx')
        ws = wb.active
        ws.title = 'Category'
        for rowy, row in enumerate(new_data, start=idx):
            for colx, value in enumerate(row, start=1):
                ws.cell(column=(colx + idy), row=rowy, value=value)
        idx = idx + 1
        wb.save('excel1.xlsx')

def zadatak2():
    try:
        existing_file = 'excel1.xlsx'
        df_existing = pd.read_excel(existing_file)
        connection = mysql.connector.connect(host='localhost',
                user='root',
                passwd='YOUR_PASSWORD_HERE',
                database='knjige')
        cursor = connection.cursor()

        sql_delete = "DELETE FROM knjige WHERE format not like '%x%' or year like '%x%' or year NOT REGEXP '^[0-9]{4}$' or year>2024 or name is NULL OR authors is NULL OR year is NULL OR category is NULL OR publisher is NULL OR page_number is NULL OR format is NULL OR type is NULL OR type='' OR description is NULL OR price is NULL;"
        sql_create_new_table = "CREATE TABLE new_table AS SELECT * FROM knjige.knjige; "
        sql_delete_duplicates = "DELETE FROM knjige.knjige WHERE name IN ( SELECT name FROM new_table GROUP BY name HAVING COUNT(*) > 1);"
        sql_new_drop_table = "Drop table new_table;"

        sql_get_number_category = "SELECT category, COUNT(*) as count FROM knjige.knjige GROUP BY category"
        sql_get_number_publisher = "SELECT publisher, COUNT(*) as count FROM knjige.knjige GROUP BY publisher"
        sql_get_number_description = "SELECT COUNT(*) as count FROM knjige.knjige WHERE description LIKE '%ljubav%'"
        sql_get_number_years = "SELECT year, COUNT(*) as count FROM knjige.knjige GROUP BY year ORDER BY year DESC LIMIT 7"
        sql_get_number_price = "SELECT name, price FROM knjige.knjige ORDER BY price DESC LIMIT 30"
        sql_get_number_price_2023_2024 = "SELECT name, price FROM knjige.knjige WHERE year='2023' or year='2024' ORDER BY price"
        sql_get_number_pages_prices_format = "SELECT name, page_number, price, area FROM knjige.knjige ORDER BY page_number, price, area "
        ##sql_get_number_pages = "SELECT category, COUNT(*) as count FROM knjige.knjige GROUP BY category"
        ##sql_get_number_category = "SELECT category, COUNT(*) as count FROM knjige.knjige GROUP BY category"
        ##sql_get_number_category = "SELECT category, COUNT(*) as count FROM knjige.knjige GROUP BY category"

        cursor.execute(sql_create_new_table)
        cursor.execute(sql_delete_duplicates)
        cursor.execute(sql_new_drop_table)

        cursor.execute(sql_delete)

        cursor.execute(sql_get_number_category)
        records = cursor.fetchall()
        print("Total number of rows in table: ", cursor.rowcount)
        newRows([('Category','Count')], 1, 0)
        newRows(records, 2, 0)

        cursor.execute(sql_get_number_publisher)
        records = cursor.fetchall()
        print("Total number of rows in table: ", cursor.rowcount)
        newRows([('Publisher', 'Count')], 1, 3)
        newRows(records, 2, 3)

        cursor.execute(sql_get_number_description)
        records = cursor.fetchall()
        print("records: ", records[0][0])
        print("Total number of rows in table: ", cursor.rowcount)
        new_data = 'Description count'
        wb = load_workbook('excel1.xlsx')
        ws = wb.active
        ws.title = 'Category'
        ws.cell(column=7, row=1, value=new_data)
        ws.cell(column=7, row=2, value=records[0][0])
        wb.save('excel1.xlsx')
        # newRows([('Description count')], 1, 6)
        # newRows(records, 2, 6)

        cursor.execute(sql_get_number_years)
        records = cursor.fetchall()
        print("Total number of rows in table: ", cursor.rowcount)
        newRows([('Year', 'Count')], 1, 9)
        newRows(records, 2, 9)

        cursor.execute(sql_get_number_price)
        records = cursor.fetchall()
        print("Total number of rows in table: ", cursor.rowcount)
        newRows([('Name', 'Price')], 1, 12)
        newRows(records, 2, 12)

        cursor.execute(sql_get_number_price_2023_2024)
        records = cursor.fetchall()
        print("Total number of rows in table: ", cursor.rowcount)
        newRows([('Name', 'Price')], 1, 15)
        newRows(records, 2, 15)

        cursor.execute(sql_get_number_pages_prices_format)
        records = cursor.fetchall()
        print("Total number of rows in table: ", cursor.rowcount)
        wb = load_workbook('excel1.xlsx')
        ws = wb.active
        ws.title = '3in1'
        ws.cell(column=19, row=1, value='Name')
        ws.cell(column=20, row=1, value='Page number')
        ws.cell(column=21, row=1, value='Price')
        ws.cell(column=22, row=1, value='Area')
        wb.save('excel1.xlsx')
        idx = 2
        idy = 18
        for line in records:
            new_data = [[line[0], line[1], line[2], line[3]]]
            wb = load_workbook('excel1.xlsx')
            ws = wb.active
            ws.title = '4in1'
            for rowy, row in enumerate(new_data, start=idx):
                for colx, value in enumerate(row, start=1):
                    ws.cell(column=(colx + idy), row=rowy, value=value)
            idx = idx + 1
            wb.save('excel1.xlsx')

        os.system('mysqldump -u root -p records > database.sql')


    except mysql.connector.Error as e:
        print("Error reading data from MySQL table", e)
    # finally:
    #     if connection.is_connected():
    #         connection.close()
    #         cursor.close()
    #         print("MySQL connection is closed")