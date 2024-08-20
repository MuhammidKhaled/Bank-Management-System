#ifndef MONEY_H
#define MONEY_H


#include <cmath>
#include <sstream>
#include <iomanip>



class Money {
public:
//Modifiers
	void setValue(int dollars, int cents);
	void setValue(double moneyAmount);
	void setPrecision(int precision);
	void setScale(int scale);
//Accessors
	std::string returnFormattedMoney() const;
	long returnDollars() const;
	int returnCents() const;
	double returnValue() const;

	Money();
private:
	int s; // Scaling factor
	int p; // number of decimal points of precision
	double value;
	double scalingFactor() const;
};
#endif // !MONEY_H
