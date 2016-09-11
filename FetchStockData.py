from yahoo_finance import Share # For stock data
import csv      # To read and write stock data
import datetime # For date and time functions
import numpy    # To work with arrays
import talib    # Technical Analysis Library (MACD, RSI)
import os       # System commands

def main():
    count = 0 # Counter
    
    # Need this for Technical Analysis calculations
    curr = datetime.datetime.now()
    currYear = str(curr.year)
    currMonth = str(curr.month)
    currDay = str(curr.day)
    currDate = currYear + '-' + currMonth + '-' + currDay
    startDate = str(curr.year - 1) + '-' + currMonth + '-' + currDay 

    contents = open('constituents.csv', 'r') # Open constituents file for reading
    reader = csv.reader(contents) # CSV reader object

    writeData = open('stockData.csv', 'w', newline = '') # Open output data file in write mode
    writer = csv.writer(writeData) # CSV writer object

    for row in reader: # For each line in the constituents file
        try:
            ticker = Share(row[0])  # Share object with ticker symbol as input

            currPrice = ticker.get_price()  # Get currPrice (15 min delay)
            avgVol = ticker.get_avg_daily_volume()  # Get average volume
            cap = ticker.get_market_cap()   # Get market cap
            yearHigh = ticker.get_year_high()   # Get year high
            yearLow = ticker.get_year_low()    # Get year low
            ma50d = ticker.get_50day_moving_avg()  # 50 DMA
            ma200d = ticker.get_200day_moving_avg() # 200 DMA

            dataList = numpy.array([])  # Create empty numpy array
            data = ticker.get_historical(startDate, currDate)   # Get historical data for 1 year
            data = data[::-1]   # Reverse data            

            for item in data:
                dataList = numpy.append(dataList, float(item['Close'])) # Add closing prices to list

            macd, macdsignal, macdhist = talib.MACD(dataList, fastperiod=12, slowperiod=26, signalperiod=9) # Calculate MACD values
            rsi = talib.RSI(dataList, timeperiod=14) # Calculate RSI value

            # Write data to stockData file
            writer.writerow([row[0], row[1], currPrice, avgVol, cap, yearLow, yearHigh, ma50d, ma200d, macd[-1], macdsignal[-1], macdhist[-1], rsi[-1]])

        except:
            pass

        # Update screen with percent complete
        count = count + 1
        os.system('CLS')
        print((str(format(count / 504.0 * 100.0, '.2f')) + '%'))

    # Close CSV files
    writeData.close()
    contents.close()

main()  # Run main function
