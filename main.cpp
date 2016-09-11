#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Share.h"
#include "HashTable.h"
#include "PriorityQueue.h"

using namespace std;

// Constants
const unsigned int TICKERS = 504;
const unsigned int HASHSIZE = 1500;

// Function Prototypes
bool parseData(ifstream &, string &, string &, double &, double &, string &, double &,
			   double &, double &, double &, double &, double &, double &, double &);
void printBuy(PriorityQueue &, double &);
void stockInfo(Share);
void stockInfo(string, HashTable &, double); // Overloaded

int main()
{

	cout << "Would you like to use latest data file saved? (Y/y)";
	char entry;
	cin >> entry;

	// Run Python script to obtain stock data
	if (entry != 'y' && entry != 'Y')
	{
		string command = "FetchStockData.py";
		system(command.c_str());
	}

	// Read stock data from CSV file
	ifstream stockData("stockData.csv");

	// Error in opening file
	if (!stockData.is_open())
	{
		cout << "Error! File did not open correctly.";
		return -1;
	}

	// Variables
	string ticker, compName, cap;
	double price, yearLow, yearHigh, fiftyDMA, twoHundDMA, macd, signal, hist, rsi, vol;
	int count = 0;
	HashTable hashTable(HASHSIZE);	// To store ticker-data pairs
	PriorityQueue maxHeap(TICKERS); // Binary tree to sort stocks by "customFactor"
	bool filePass;

	// Parse Data
	filePass = parseData(stockData, ticker, compName, price, vol, cap, yearLow,
						 yearHigh, fiftyDMA, twoHundDMA, macd, signal, hist, rsi);

	// While input stream is not empty
	while (filePass)
	{
		// Create Share object with information
		Share stock(ticker, compName, price, vol, cap, yearLow, yearHigh,
					fiftyDMA, twoHundDMA, macd, signal, hist, rsi);

		// Insert share object to HashTable
		hashTable.insert(stock);

		// Insert share object to priority queue (max-heap) based on customFactor value
		if (stock.getFactor() >= 0)
			maxHeap.enqueue(stock);

		// Parse Data
		filePass = parseData(stockData, ticker, compName, price, vol, cap, yearLow,
							 yearHigh, fiftyDMA, twoHundDMA, macd, signal, hist, rsi);
	}

	stockData.close(); // Close file

	double avgCustomFactor; // Store average custom factor for top 15 stocks
	printBuy(maxHeap, avgCustomFactor); // Print Top 15 Stocks to BUY

	cout << endl << "Enter Stock Ticker for Information or 0 to exit." << endl;
	string viewData;
	cin >> viewData;

	// Run loop until user prompts to exit
	while (viewData != "0")
	{
		stockInfo(viewData, hashTable, avgCustomFactor); // Print Stock Data
		cout << endl << "Enter Stock Ticker for Information or 0 to exit." << endl;
		cin >> viewData;
	}

	system("pause");
	return 0;
}

// Function Definitions
bool parseData(ifstream &fin, string &ticker, string &compName, double &price, double &vol,
			   string &cap, double &yearLow, double &yearHigh, double &fiftyDMA, double &twoHundDMA,
			   double &macd, double &signal, double &hist, double &rsi)
{
	string line, field;
	getline(fin, line); // Get the entire line in the CSV file
	istringstream ss(line);

	// Check if last line in file
	if (line == "")
		return false;

	// Parse data from line to variables
	while (!ss.eof())
	{
		getline(ss, field, ',');
		ticker = field;
		getline(ss, field, ',');
		compName = field;
		getline(ss, field, ',');
		price = atof(field.c_str());
		getline(ss, field, ',');
		vol = atof(field.c_str());
		getline(ss, field, ',');
		cap = field;
		getline(ss, field, ',');
		yearLow = atof(field.c_str());
		getline(ss, field, ',');
		yearHigh = atof(field.c_str());
		getline(ss, field, ',');
		fiftyDMA = atof(field.c_str());
		getline(ss, field, ',');
		twoHundDMA = atof(field.c_str());
		getline(ss, field, ',');
		macd = atof(field.c_str());
		getline(ss, field, ',');
		signal = atof(field.c_str());
		getline(ss, field, ',');
		hist = atof(field.c_str());
		getline(ss, field, ',');
		rsi = atof(field.c_str());
	}
	return true;
}

void printBuy(PriorityQueue &maxHeap, double &avgCustomFactor)
{
	avgCustomFactor = 0;
	Share buyStock;
	int num = maxHeap.size();

	if (num > 15)
		num = 15;

	cout << "Top 15 Stocks to BUY:" << endl << endl;

	// Obtain Top 15 stocks to "Buy", unless there are less than 15 ideal stocks
	for (int i = 1; i <= num; i++)
	{
		buyStock = maxHeap.max();
		maxHeap.dequeue();
		cout << i << ") " << endl;
		stockInfo(buyStock);
		avgCustomFactor += buyStock.getFactor();
	}

	avgCustomFactor /= num;
}

void stockInfo(Share stock)
{
	cout << "Ticker Symbol: " << stock.getTicker() << endl;
	cout << "Company Name: " << stock.getCompanyName() << endl;
	cout << fixed << setprecision(2) << "Current Price: $" << stock.getPrice() << endl;
	cout << "Average Volume: " << stock.getVolume() << endl;
	cout << "Market Cap: $" << stock.getCap() << endl;
	cout << fixed << setprecision(2) << "Year Low: $" << stock.getYearLow() << endl;
	cout << fixed << setprecision(2) << "Year High: $" << stock.getYearHigh() << endl;
	cout << fixed << setprecision(2) << "50 DMA: $" << stock.get50DMA() << endl;
	cout << fixed << setprecision(2) << "200 DMA: $" << stock.get200DMA() << endl;
	cout << fixed << setprecision(2) << "MACD: " << stock.getMACD() << endl;
	cout << fixed << setprecision(2) << "MACD Signal: " << stock.getSignal() << endl;
	cout << fixed << setprecision(2) << "MACD Histogram: " << stock.getHist() << endl;
	cout << fixed << setprecision(2) << "RSI: " << stock.getRSI() << endl << endl;
}

void stockInfo(string ticker, HashTable &table, double avgCustomFactor)
{
	Share stock;
	bool exists = table.search(ticker, stock); // Check to see if ticker exists in table

	if (exists) // If exists, then print out data
	{
		cout << "Ticker Symbol: " << stock.getTicker() << endl;
		cout << "Company Name: " << stock.getCompanyName() << endl;
		cout << fixed << setprecision(2) << "Current Price: $" << stock.getPrice() << endl;
		cout << "Average Volume: " << stock.getVolume() << endl;
		cout << "Market Cap: $" << stock.getCap() << endl;
		cout << fixed << setprecision(2) << "Year Low: $" << stock.getYearLow() << endl;
		cout << fixed << setprecision(2) << "Year High: $" << stock.getYearHigh() << endl;
		cout << fixed << setprecision(2) << "50 DMA: $" << stock.get50DMA() << endl;
		cout << fixed << setprecision(2) << "200 DMA: $" << stock.get200DMA() << endl;
		cout << fixed << setprecision(2) << "MACD: " << stock.getMACD() << endl;
		cout << fixed << setprecision(2) << "MACD Signal: " << stock.getSignal() << endl;
		cout << fixed << setprecision(2) << "MACD Histogram: " << stock.getHist() << endl;
		cout << fixed << setprecision(2) << "RSI: " << stock.getRSI() << endl;

		double factor = stock.getFactor();

		if (factor < 0)
			factor = 0;
		else if (factor > avgCustomFactor)
			factor = avgCustomFactor;

		double rating = factor / avgCustomFactor * 100;
		cout << fixed << setprecision(2) << "Buy Rating: " << rating << "%" << endl << endl;
	}
	else // Otherwise, display error
		cout << "The stock symbol entered does not exist in the database." << endl;
}