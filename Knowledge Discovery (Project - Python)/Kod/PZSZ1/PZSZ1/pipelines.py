# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import mysql.connector
#from item import Pzsz1Item
from mysql.connector import errorcode
from scrapy.exceptions import DropItem


class Pzsz1Pipeline(object):

    def __init__(self):
        self.create_connection()
        self.create_table()

    def create_connection(self):
        self.conn = mysql.connector.connect(
            host='localhost',
            user='root',
            passwd='YOUR_PASSWORD_HERE',
            database='knjige'
        )
        self.curr = self.conn.cursor()

    def create_table(self):
        self.curr.execute("""DROP TABLE IF EXISTS knjige""") #json
        self.curr.execute("""create table knjige(name varchar(250), 
                                                authors varchar(250),
                                                category varchar(250),
                                                publisher varchar(250),
                                                year int,
                                                page_number int,
                                                type varchar(250),
                                                format varchar(250),
                                                area double,
                                                description varchar(500),
                                                price double)""")

    def process_item(self, item, spider):
        try:
            self.store_db(item)
            print("Pipeline print:"+item['name'][0])
            return item
        except mysql.connector.Error as e:
            raise DropItem(f'Error inserting item: {e}')
    def store_db(self, item):
        record = (item['name'], item['authors'], item['category'], item['publisher'], item['year'], item['page_number'], item['type'], item['format'],item['area'], item['description'], item['price'])
        self.curr.execute("""insert ignore into knjige(name,authors,category,publisher,year,page_number,type,format,area,description,price) values (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)""",
            record
        )
        self.conn.commit()

#         record = (item['name'], item['authors'], item['category'], item['publisher'], item['year'], item['page_number'], item['type'], item['format'], item['description'], item['price'])
#        self.curr.execute("""insert ignore into knjige(name,authors,category,publisher,year,page_number,type,format,description,price) values (%s, %s,%s,%s,%s,%s,%s,%s,%s,%s)""",
