#ifndef VanillaOption_hpp
#define VanillaOption_hpp

#include <vector>
#include <sstream>
using namespace std;

class VanillaOption					//OptionBase to Create EuropeanOption and AmericanOption
{
public:
	double S;						//Underlying Stock Price
	double K;						//Strike Price
	double b;						//Cost of Carry
	double r;						//risk free rate
	double sig;						//Vol
	double T;						//T
	double OptionType;				//0 as Call, non-zero as put


	virtual double CallPrice() const = 0;
	virtual double PutPrice() const= 0;
	virtual double Price() const = 0;

	virtual double NumericalDelta(double ShockSize) = 0;
	virtual double NumericalGamma(double ShockSize) = 0;
};

#endif // !VanillaOption
