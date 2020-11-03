#ifndef PerpetualAmericanOption_hpp
#define PerpetualAmericanOption_hpp

#include "VanillaOption.hpp"
using namespace std;

class PerpetualAmericanOption : public VanillaOption
{
public:
	PerpetualAmericanOption();														//Default Constructor
	PerpetualAmericanOption(const PerpetualAmericanOption& source);					//Copy Constructor
	~PerpetualAmericanOption();														//Destructor
	//Data member setter
	void Parameters(double S_source, double r_source, double b_source, double K_source, double sig_source, double OptionType_source);
	double CallPrice() const;														//Perpertual American Put Price
	double PutPrice() const;														//Perpertual American Put Price
	double Price() const;															//Return Call Price when OptionType is 0, else return put price
	double NumericalDelta(double ShockSize);														//Delta calculated by shocking S to call price 
	double NumericalGamma(double ShockSize);														//Gamma calculated by shocking S to call price
	vector<double> VectorPricer(vector<double> source);								//Input a range of one parameter
	vector<double>	MatrixPricer(vector<vector<double>> source);					//Input a matrix of all parameter in the sequence of S r b K sig OptionType
};










#endif // !PerpetualAmericanOption_hpp
