#include "Share.h"

// Default Constructor
Share::Share()
{
	setTicker("");
	setCompName("");
	setPrice(0);
	setVolume(0);
	setCap("");
	setYearLow(0);
	setYearHigh(0);
	set50DMA(0);
	set200DMA(0);
	setMACD(0);
	setSignal(0);
	setHist(0);
	setRSI(0);
	setFactor();
}

// Constructor
Share::Share(string symbol, string name, double priceIn, double volIn, string capIn, double low, double high,
			 double fiftyIn, double twoHundIn, double macdIn, double signalIn, double histIn, double rsiIn)
{
	setTicker(symbol);
	setCompName(name);
	setPrice(priceIn);
	setVolume(volIn);
	setCap(capIn);
	setYearLow(low);
	setYearHigh(high);
	set50DMA(fiftyIn);
	set200DMA(twoHundIn);
	setMACD(macdIn);
	setSignal(signalIn);
	setHist(histIn);
	setRSI(rsiIn);
	setFactor();
}

// Destructor
Share::~Share() {}

// Copy constructor.
Share::Share(const Share& rhs)
{
	setTicker(rhs.getTicker());
	setCompName(rhs.getCompanyName());
	setPrice(rhs.getPrice());
	setVolume(rhs.getVolume());
	setCap(rhs.getCap());
	setYearLow(rhs.getYearLow());
	setYearHigh(rhs.getYearHigh());
	set50DMA(rhs.get50DMA());
	set200DMA(rhs.get200DMA());
	setMACD(rhs.getMACD());
	setSignal(rhs.getSignal());
	setHist(rhs.getHist());
	setRSI(rhs.getRSI());
	setFactor();
}

// Assignment operator.
Share& Share::operator=(const Share& rhs)
{
	setTicker(rhs.getTicker());
	setCompName(rhs.getCompanyName());
	setPrice(rhs.getPrice());
	setVolume(rhs.getVolume());
	setCap(rhs.getCap());
	setYearLow(rhs.getYearLow());
	setYearHigh(rhs.getYearHigh());
	set50DMA(rhs.get50DMA());
	set200DMA(rhs.get200DMA());
	setMACD(rhs.getMACD());
	setSignal(rhs.getSignal());
	setHist(rhs.getHist());
	setRSI(rhs.getRSI());
	setFactor();
	return *this;
}

// Comparison Operator Overload Function
bool operator==(const Share &lhs, const Share &rhs)
{
	return (lhs.getTicker() == rhs.getTicker() &&
			lhs.getCompanyName() == rhs.getCompanyName() &&
			lhs.getPrice() == rhs.getPrice() &&
			lhs.getVolume() == rhs.getVolume() &&
			lhs.getCap() == rhs.getCap() &&
			lhs.getYearLow() == rhs.getYearLow() &&
			lhs.getYearHigh() == rhs.getYearHigh() &&
			lhs.get50DMA() == rhs.get50DMA() &&
			lhs.get200DMA() == rhs.get200DMA() &&
			lhs.getMACD() == rhs.getMACD() &&
			lhs.getSignal() == rhs.getSignal() &&
			lhs.getHist() == rhs.getHist() &&
			lhs.getRSI() == rhs.getRSI());
}


// Mutator Functions
void Share::setPrice(double priceInput)
{
	price = priceInput;
}

void Share::setCap(string capInput)
{
	cap = capInput;
}

void Share::set50DMA(double maInput)
{
	fiftyDMA = maInput;
}

void Share::set200DMA(double maInput)
{
	twoHundredDMA = maInput;
}

void Share::setVolume(double vol)
{
	volume = vol;
}

void Share::setYearLow(double low)
{
	yearLow = low;
}

void Share::setYearHigh(double high)
{
	yearHigh = high;
}

void Share::setMACD(double macdInput)
{
	macd = macdInput;
}

void Share::setSignal(double sigInput)
{
	signal = sigInput;
}

void Share::setHist(double histInput)
{
	hist = histInput;
}

void Share::setRSI(double rsiInput)
{
	rsi = rsiInput;
}

void Share::setFactor()
{
	if (rsi >= 30 && rsi <= 70 && hist > 0 && fiftyDMA >= twoHundredDMA)
		customFactor = hist * rsi * fiftyDMA / twoHundredDMA;
	else
		customFactor = -1.0;
}

void Share::setTicker(string tickerSymbol)
{
	ticker = tickerSymbol;
}

void Share::setCompName(string name)
{
	companyName = name;
}


// Accessor Functions
double Share::getPrice() const
{
	return price;
}

string Share::getCap() const
{
	return cap;
}

double Share::get50DMA() const
{
	return fiftyDMA;
}

double Share::get200DMA() const
{
	return twoHundredDMA;
}

double Share::getVolume() const
{
	return volume;
}

double Share::getYearLow() const
{
	return yearLow;
}

double Share::getYearHigh() const
{
	return yearHigh;
}

double Share::getMACD() const
{
	return macd;
}

double Share::getSignal() const
{
	return signal;
}

double Share::getHist() const
{
	return hist;
}

double Share::getRSI() const
{
	return rsi;
}

double Share::getFactor() const
{
	return customFactor;
}

string Share::getTicker() const
{
	return ticker;
}

string Share::getCompanyName() const
{
	return companyName;
}