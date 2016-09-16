# Algorithmic-Trading-Program
Implements linked lists, priority queues, heaps and hashing to compute recommended positions for stocks on the S&amp;P 500.

Run main.cpp

Stocks on S&P 500 are sorted using a custom factor involving various quantitative technical analysis tools such as the MACD, RSI and moving averages.

Program first requests user to enter whether they would like to update the current stock data csv file with the latest information. If yes, a Python script is run which contains Yahoo Finanace API calls to retrieve stock information for all of the stocks on the S&P 500. The data is further manipulated for use with the Technical Analysis library which contains some common quantitative finance tools such as the MACD and RSI.

Once the csv file has been updated by the Python program, the file is read into a hash table and priority queue by the C++ program. The hash function algorithm is as follows:

index = (Product of ASCII code for each character in ticker symbol) modulo (Hash Table capacity)

The hash table is configured for separate chaining with Linked Lists. The share object is passed to the priority queue based on criteria that would suggest that the recommended position for the stock is "buy". The queue is implemented using a max-heap tree and is ordered based on a custom factor derived from various share properties.

The program then outputs the Top 15 stocks to "buy" and prompts the user for any stocks that they would like information for. Based on the user's input, the program would either exit, or print the stock information for the provided ticker and also suggest a "Buy Rating".



Credits:

Yahoo Finance Library:
https://github.com/lukaszbanasiak/yahoo-finance

Technical Analysis Library:
https://github.com/mrjbq7/ta-lib

Numpy:
https://github.com/numpy/numpy
