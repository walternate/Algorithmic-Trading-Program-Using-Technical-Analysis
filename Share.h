#ifndef SHARE_H
#define SHARE_H

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Share
{
public:
	// Default Constructor
	Share();

	// Constructor
	Share(string symbol, string name, double, double, string, double,
		double, double, double, double, double, double, double);
	
	// Destructor
	~Share();

	// Copy constructor.
	Share(const Share& rhs);

	// Assignment operator.
	Share& operator=(const Share& rhs);

	// Comparison Operator Overload Function
	friend bool operator==(const Share &lhs, const Share &rhs);

	// Accessor Functions
	double getPrice() const;
	string getCap() const;
	double get50DMA() const;
	double get200DMA() const;
	double getVolume() const;
	double getYearLow() const;
	double getYearHigh() const;
	double getMACD() const;
	double getSignal() const;
	double getHist() const;
	double getRSI() const;
	double getFactor() const;
	string getTicker() const;
	string getCompanyName() const;

private:
	// Member Variables
	double price, fiftyDMA, twoHundredDMA, volume, yearHigh,
		   yearLow, macd, signal, hist, rsi, customFactor;
	string companyName, ticker, cap;

	// Mutator Functions
	void setPrice(double priceInput);
	void setCap(string capInput);
	void set50DMA(double maInput);
	void set200DMA(double maInput);
	void setVolume(double vol);
	void setYearLow(double low);
	void setYearHigh(double high);
	void setMACD(double macdInput);
	void setSignal(double sigInput);
	void setHist(double histInput);
	void setRSI(double rsiInput);
	void setFactor();
	void setTicker(string tickerSymbol);
	void setCompName(string name);
};

#endif