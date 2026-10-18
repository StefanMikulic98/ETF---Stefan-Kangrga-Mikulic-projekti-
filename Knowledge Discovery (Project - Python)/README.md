# Knowledge Discovery — Book Market Data Mining (Python)

A full knowledge-discovery pipeline — web scraping, a MySQL data warehouse, data cleaning, SQL analytics, visualisation, and machine learning models implemented from scratch — built on data from a Serbian online bookstore, as a university project for the *Knowledge Discovery (Pronalaženje skrivenog znanja)* course at ETF.

## What it does

The project scrapes, cleans, analyses, and models book-market data end-to-end:

- **Web scraping (`Kod/PZSZ1`)**: a Scrapy `CrawlSpider` (`amazon`) crawls [knjizare-vulkan.rs](https://www.knjizare-vulkan.rs/) and extracts book attributes (name, authors, category, publisher, year, page count, format/area, cover type, description, price) into the `Pzsz1Item` schema, rotating user agents to avoid blocking.
- **Data warehouse (`Pzsz1Pipeline`)**: each scraped item is written straight into a MySQL table `knjige` via `mysql.connector`.
- **Cleaning & aggregation (`Kod/Projekat/zadatak2.py`)**: removes duplicate/malformed records (bad years, missing fields), then runs SQL aggregations (books per category/publisher/decade, price distributions, price outliers, "ljubav"-themed description search) and writes the results into `excel1.xlsx`.
- **Visualisation (`zadatak3.py`)**: runs further SQL queries and renders them as Seaborn/Matplotlib bar charts — books per publisher/category/decade, top-5 publisher market share, price-range distribution, and hardcover vs. other binding share — saved as the `chart_*.png` files.
- **Linear regression (`zadatak4.py`)**: a multilinear regression model to predict book price from selected features (author, category, publisher, year, format/area, binding type, page count), implemented **from scratch** with one-hot/label encoding, min-max normalisation, batch gradient descent, and R² evaluation on a train/test split — plus a `predict()` function for ad-hoc price estimates.
- **Clustering (`KMeans.py`)**: a from-scratch k-means implementation (random center init, Euclidean-distance assignment, iterative mean-center update) over the same feature set, with pairwise scatter plots of the resulting clusters.
- **GUI (`GUI.py`)**: a Tkinter front-end tying it all together — buttons to run the cleaning/analysis step, open the results workbook, generate/view the charts, train the regression model with live loss output, test a price prediction for custom input, and run k-means with a chosen *k* and epoch count.

## Project structure

```
Kod/
  PZSZ1/                      — Scrapy project (web scraper)
    scrapy.cfg
    PZSZ1/
      items.py                — Scraped item schema (Pzsz1Item)
      pipelines.py             — Writes scraped items into the MySQL "knjige" table
      middlewares.py           — User-agent rotation middleware
      settings.py              — Scrapy project settings
      spiders/main.py          — "amazon" CrawlSpider targeting knjizare-vulkan.rs
  Projekat/                   — Analysis & ML application
    GUI.py                    — Tkinter application tying the steps together
    zadatak2.py               — Data cleaning + SQL aggregation -> excel1.xlsx
    zadatak3.py               — SQL analytics + chart generation
    zadatak4.py               — Multilinear regression from scratch (train/test/predict)
    KMeans.py                 — K-means clustering from scratch
    excel1.xlsx               — Aggregated analysis results
    chart_*.png               — Generated visualisations
Izvestaj_StefanKangrgaMikulic_2023_3424.pdf — Final project report
```

## Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| Web scraping | Scrapy `CrawlSpider` + `LinkExtractor` with rules-based crawling and a custom item pipeline persisting directly to MySQL |
| Data cleaning | SQL-based deduplication and validity filtering (malformed years, missing required fields) |
| Exploratory data analysis | Aggregation queries (`GROUP BY`, `CASE`, CTEs) for category/publisher/decade/price-range distributions |
| Data visualisation | Seaborn/Matplotlib bar charts generated directly from SQL query results |
| Feature engineering | One-hot encoding for categorical features, min-max normalisation for numeric features |
| Linear regression from scratch | Manual gradient computation, batch gradient descent with L2 regularisation, R² evaluation on held-out data |
| K-means from scratch | Random centroid initialisation, Euclidean-distance cluster assignment, iterative centroid update |
| GUI application | Tkinter interface with threaded execution so long-running analysis/ML steps don't block the UI |

## Building & running

Requires Python 3.10+, MySQL Server, and the packages: `scrapy`, `mysql-connector-python`, `pandas`, `numpy`, `matplotlib`, `seaborn`, `scikit-learn`, `openpyxl`, `xlwings`, `Pillow`.

```bash
# 1. Scrape data into MySQL (database "knjige" is created automatically)
cd "Kod/PZSZ1"
scrapy crawl amazon

# 2. Run the analysis / ML GUI
cd "../Projekat"
python GUI.py
```

> **Note:** the MySQL connection details (`host`, `user`, `passwd`) in `pipelines.py`, `KMeans.py`, `zadatak2.py`, `zadatak3.py`, and `zadatak4.py` use a placeholder password (`YOUR_PASSWORD_HERE`). Replace it with your local MySQL root password (or, better, load it from an environment variable) before running.
