import scrapy
from ..items import Pzsz1Item
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor

#pokrenuti program sa:  scrapy crawl amazon
#testirati program sa:  scrapy shell 'https://www.knjizare-vulkan.rs/domace-price-i-pripovetke/2921-bensedin'

class amazon(CrawlSpider):

    name = "amazon"
    allowed_domains = ["knjizare-vulkan.rs"]
    start_urls = ["https://www.knjizare-vulkan.rs/"]

    rules = (
        Rule(LinkExtractor(), callback='parse_item', follow='true'),
    )
    #deny=['laguna_klub_citalaca.html','mala_laguna.html','laguna-top-liste.html', 'laguna-bukmarker.html', 'naslovi_u_pripremi.html', 's_laguna_knjige_spisak_naslova.html', 'spisak_zelja.html', 'spisak_korpa.html']

    def parse_item(self, response):
        items = Pzsz1Item()
        condition_publisher = response.css('.attr-izdavac a::text').get()
        #condition1 = response.css('.attr-povez+ tr td+ td::text').get()
        #condition1 = response.css('.attr-povez+ tr td+ td::text').get()
        if condition_publisher is not None:
            #laguna
            # items['name'] = response.css('.naslov::text')[0].extract()
            # items['authors'] = response.css('.hidden-xs a::text').get()
            # items['year'] = response.css('#podaci-korica div:nth-child(5)::text').get()
            # items['category'] = json.dumps(response.css('h3 a::text').extract())
            # items['publisher'] = response.css('#podaci-korica div:nth-child(5)::text').get()
            # items['page_number'] = response.css('#podaci-korica div:nth-child(2)::text').get()
            # items['type'] = response.css('#podaci-korica div:nth-child(4)::text').get()
            # items['format'] = str(response.css('#podaci-korica div:nth-child(1)::text').extract())
            # items['description'] =str(response.css('#oknjizitab div::text').extract())
            # items['price'] = response.css('p:nth-child(1)::text').get()

            #vulkan
            items['name'] = response.css('.product-details-info .title span::text')[0].extract()
            items['authors'] = response.css('.product-details-info div .atributs-wrapper a::text').get()

            condition_year = response.css('.attr-povez+ tr td+ td::text').get()
            if condition_year is not None:
                items['year'] = int(response.css('.attr-povez+ tr td+ td::text').get())
            else:
                items['year'] = int(response.css('.attr-pismo+ tr td+ td::text').get())

            items['category'] = ' '.join(response.css('tr:nth-child(1) a::text').extract()).replace("\n","").replace("\r","").replace("  ","")
            items['publisher'] = response.css('.attr-izdavac a::text').get()

            condition_page_number = response.css('tr:nth-child(9) td+ td::text').get()
            if condition_page_number is not None:
                items['page_number'] = int(response.css('tr:nth-child(9) td+ td::text').get())
                txt = response.css('tr:nth-child(8) td+ td::text').get()
                items['format'] = txt
                # a = float(txt.split("x")[0])
                # b = float(txt.split("x")[1])
                items['area'] =float(txt.split("x")[0]) * float(txt.split("x")[1])
            else:
                items['page_number'] = int(response.css('tr:nth-child(8) td+ td::text').get())
                txt = response.css('tr:nth-child(7) td+ td::text').get()
                items['format'] = txt
                items['area'] = float(txt.split("x")[0]) * float(txt.split("x")[1])

            items['type'] = ' '.join(response.css('.attr-povez td+ td::text').extract()).replace("\n","").replace("\r","").replace("  ","")
            items['description'] = ' '.join(response.css('#tab_product_description::text').extract()).replace("\n","").replace("\r","").replace("  ","")
            items['price'] = int(response.css('.product-price-without-discount-value::text').get().replace(',00','').replace(',01','').replace('.',''))

            yield items