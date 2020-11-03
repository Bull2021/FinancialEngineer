#include "PerpetualAmericanOption.hpp"
#include <cmath>
#include <iostream>
using namespace std;

PerpetualAmericanOption::PerpetualAmericanOption()
{
	//Default Constructor
}

PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& source)
{//Copy constructor
	S = source.S;
	b = source.b;
	r = source.r;
	sig = source.sig;
	K = source.K;
	OptionType = source.OptionType;
}

PerpetualAmericanOption::~PerpetualAmericanOption()
{
	//Destructor
}

void PerpetualAmericanOption::Parameters(double S_source, double r_source, double b_source, double K_source, double sig_source, double OptionType_source)
{//Data member setter
	S = S_source;
	r = r_source;
	b = b_source;
	K = K_source;
	sig = sig_source;
	OptionType = OptionType_source;
}

double PerpetualAmericanOption::CallPrice() const
{//Perpertual American Put Price
	double tmp = b / (sig * sig);
	double y1 = 0.5 - tmp + sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * r / (sig * sig));
	return K/(y1-1)*pow((y1-1)*S/(y1*K),y1);
}

double PerpetualAmericanOption::PutPrice() const
{//Perpertual American Put Price
	double tmp = b / (sig * sig);
	double y2 = 0.5 - tmp - sqrt((tmp - 0.5) * (tmp - 0.5) + 2 * r / (sig * sig));
	return K / (1-y2) * pow((y2 - 1) * S / (y2 * K), y2);
}

double PerpetualAmericanOption::Price() const
{//Return Call Price when OptionType is 0, else return put price
	if (OptionType == 0) return CallPrice();
	else return PutPrice();
}

double PerpetualAmericanOption::NumericalDelta(double ShockSize)
{//Delta calculated by shocking S to call price
	S += ShockSize;
	double PriceUp = Price();
	S = S - 2 * ShockSize;
	double PriceDown = Price();
	//Return Member Data to Before Shock
	S += ShockSize;
	return (PriceUp - PriceDown) / (2 * ShockSize);
}


double PerpetualAmericanOption::NumericalGamma(double ShockSize)
{//Gamma calculated by shocking S to call price
	S += ShockSize;
	double PriceUp = Price();
	S = S - 2 * ShockSize;
	double PriceDown = Price();
	//Return Member Data to Before Shock
	S += ShockSize;
	double PriceBase = Price();
	return (PriceUp + PriceDown - 2 * PriceBase) / (ShockSize * ShockSize);
}

//Input a range of one parameter
vector<double> PerpetualAmericanOption::VectorPricer(vector<double> source)
{
	vector<double> v_output;
	for (int i = 0; i < source.size();++i)
	{
		S = source[i];
		v_output.push_back(Price());
	}
	return v_output;
}

//Input a matrix of all parameter in the sequence of S r b K sig OptionType
vector<double> PerpetualAmericanOption::MatrixPricer(vector<vector<double>> source)
{
	vector<double> v_output;

	for (int j = 0; j < source[0].size();++j)
	{
		S = source[0][j];
		r = source[1][j];
		b = source[2][j];
		K = source[3][j];
		sig = source[4][j];
		OptionType = source[5][j];
		v_output.push_back(Price());
	}
	return v_output;
}
