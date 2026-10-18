# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class Pzsz1Item(scrapy.Item):
    # define the fields for your item here like:
    name = scrapy.Field()
    authors = scrapy.Field()
    category = scrapy.Field()
    publisher = scrapy.Field()
    year = scrapy.Field()
    page_number = scrapy.Field()
    type = scrapy.Field()
    format = scrapy.Field()
    area = scrapy.Field()
    description = scrapy.Field()
    price = scrapy.Field()
