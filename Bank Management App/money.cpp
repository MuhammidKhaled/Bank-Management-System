#include "money.h"

const int DEFAULT_PRECISION = 2;
const int DEFAULT_SCALE = 0;

double Money::scalingFactor() const {
	return pow(10, s);
}

Money::Money() :value(0), s(DEFAULT_SCALE), p(DEFAULT_PRECISION) {
}

void Money::setValue(double moneyAmount) {
	value = moneyAmount;
}

void Money::setValue(int dollars, int cents) {
	if (dollars < 0 || cents < 0 || cents >= 100) {
		throw std::invalid_argument("Invalid dollar or cent value");
	}

	value = dollars + (cents / 100.0);
}

void Money::setPrecision(int precision) {
	p = precision;
}

void Money::setScale(int scale) {
	s = scale;
}

double Money::returnValue() const {
	double val = value;

	if (s > 0) {
		val *= scalingFactor();
	}
	return val;
}

long Money::returnDollars() const {
	double dollars = value;

	if (s > 0) {
		dollars *= scalingFactor();
	}

	return std::lround(dollars);
}

int Money::returnCents() const {
	double scaledValue = value;
	if (s > 0) {
		scaledValue *= scalingFactor();
	}

	double cents = std::abs(scaledValue - std::floor(scaledValue));
	cents = std::round(cents * 100);

	return static_cast<int>(cents);
}

std::string Money::returnFormattedMoney() const {
    double val = returnValue();

    std::stringstream ss;

    ss.imbue(std::locale(""));
    ss << std::fixed << std::showpoint;

    ss << std::setprecision(p);

    ss << "$" << val;

    return ss.str();
}




