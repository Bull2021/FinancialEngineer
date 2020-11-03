#include "EuropeanOption.hpp"
#include "boost/math/distributions/normal.hpp"
#include <cmath>
using namespace std;
using boost::math::normal;

EuropeanOption::EuropeanOption()
{
	//Default Constructor
}

EuropeanOption::EuropeanOption(const EuropeanOption& source)
{
	//Copy Constructor
	S = source.S;
	T = source.T;
	r = source.r;
	b = source.b;
	K = source.K;
	sig = source.sig;
	OptionType = source.OptionType;
	
}

EuropeanOption::~EuropeanOption()
{
	//destructor
}

double EuropeanOption::N(double x) const
{	//Cumulative distribution function for normal distribution N(d1) and N(d2)
	normal s;
	return cdf(s, x);
}

double EuropeanOption::n(double x) const
{	//probability density function 
	normal s;
	return pdf(s, x);
}

void EuropeanOption::Parameters(double S_source, double T_source, double r_source, double b_source, double K_source, double sig_source, double OptionType_source)
{//Public data member setter
	S = S_source;
	T = T_source;
	r = r_source;
	b = b_source;
	K = K_source;
	sig = sig_source;
	OptionType = OptionType_source;
}


double EuropeanOption::CallPrice() const
{	//Black scholes call price formula
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig / 2) * T) / tmp;
	double d2 = d1 - tmp;
	return S * exp((b - r) * T) * N(d1) - K * exp(-r * T) * N(d2);
}


double EuropeanOption::PutPrice() const
{	//Black scholes put price formula
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig / 2) * T) / tmp;
	double d2 = d1 - tmp;
	return -S * exp((b - r) * T) * N(-d1) + K * exp(-r * T) * N(-d2);
}

double EuropeanOption::Price() const
{	//If optiontype is 0, return call price, else, return put price  
	if (OptionType == 0) return CallPrice();
	else return PutPrice();
}


void EuropeanOption::PutCallParityCheck() const
{	//Check put call parity by checking equality of call/put price from black scholes formula
	if (CallPrice() + K * exp(-r * T) - PutPrice() - S <0.000000000001)
	{
		cout << "Put/Call Parity Satisfied" << endl;
	}
	else 
	{ 
		cout<<"Put/Call Parity Not Satisfied" << endl;
	}
}

double EuropeanOption :: PutCallParity() const
{	//Calculating put/call price by put call parity formula
	//If option type is call, return put price, if option type is put, return call price
	if (OptionType==0)
	{
		return CallPrice() + K * exp(-r * T) - S;
	} 
	else
	{
		return PutPrice() + S - K * exp(-r * T);
	}
}

//Return Call Option Delta
double EuropeanOption::CallDelta() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig / 2) * T) / tmp;
	return exp((b-r)*T)*N(d1);
}

//Return Put Option Delta
double EuropeanOption::PutDelta() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig / 2) * T) / tmp;
	return exp((b - r) * T) * (N(d1)-1);
}

//If OptionType set as 0, return Call Option Delta, else return Put Delta
double EuropeanOption::Delta() const
{
	if (OptionType == 0) return CallDelta();
	else return PutDelta();

}

//Return Option Gamma
double EuropeanOption::Gamma() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (b + sig * sig / 2) * T) / tmp;
	return exp((b - r) * T) * n(d1) / (S * sig * sqrt(T));
}

//Calculate Delta by shock BS formula
double EuropeanOption::NumericalDelta(double ShockSize)
{
	S += ShockSize;
	double PriceUp = Price();
	S = S - 2 * ShockSize;
	double PriceDown = Price();
	//Return Member Data to Before Shock
	S += ShockSize;								
	return (PriceUp - PriceDown) / (2 * ShockSize);
}

//Calculate Gamma by shock BS formula
double EuropeanOption::NumericalGamma(double ShockSize)
{
	S += ShockSize;
	double PriceUp = Price();
	S = S - 2 * ShockSize;
	double PriceDown = Price();
	//Return Member Data to Before Shock
	S += ShockSize;
	double PriceBase = Price();
	return (PriceUp + PriceDown -2*PriceBase) / (ShockSize * ShockSize);
}

//Input is a vector of a specific parameter, metric index: 0-Price,1-Delta,2-Put
vector<double> EuropeanOption::VectorPricer(vector<double> source, int metric_index)
{
	vector<double> v_output;
	for (int i = 0; i < source.size();++i)
	{
		S = source[i];
		if (metric_index == 0) v_output.push_back(Price());
		else if (metric_index == 1) v_output.push_back(Delta());
		else v_output.push_back(Gamma());	
	}
	return v_output;
}

//Input is a matrix of all data member, sequesnce S T r b K sig Optiontype
vector<double>	EuropeanOption::MatrixPricer(vector<vector<double>> source, int metric_index)
{
	vector<double> v_output;

	for (int j = 0; j < source[0].size();++j)
	{

		S = source[0][j];
		T = source[1][j];
		r = source[2][j];
		b = source[3][j];
		K = source[4][j];
		sig = source[5][j];
		OptionType = source[6][j];

		if (metric_index == 0) v_output.push_back(Price());
		else if (metric_index == 1) v_output.push_back(Delta());
		else v_output.push_back(Gamma());
	}
	return v_output;
}
