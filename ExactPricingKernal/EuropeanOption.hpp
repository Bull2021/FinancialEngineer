#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp
#include "VanillaOption.hpp"

class EuropeanOption: public VanillaOption				//Public inherit public data member from OptionBase for convenience
{
private:

	//Gaussian functions
	double N(double x) const;	
	double n(double x) const;

public:
	EuropeanOption();									//Default Constructor
	EuropeanOption(const EuropeanOption& source);		//Copy Constructor
	~EuropeanOption();									//Destructor	
	//member function to set member data:
	void Parameters(double S_source, double T_source, double r_source, double b_source, double K_source, double sig_source, double OptionType_source);

	double CallPrice() const;							//Calculate Price of Call Option
	double PutPrice() const;							//Calculate Price of Put Option
	double Price() const;								//If optiontype is 0, return call price, else, return put price 

	void PutCallParityCheck() const;					//Check put-call parity by calculating both put and call price from BS formula					
	double PutCallParity() const;						//Calculating put/call price by put-call parity formula

	double CallDelta() const;							//Return Call Option Delta
	double PutDelta() const;							//Return Put Option Delta	
	double Delta() const;								//If OptionType set as 0, return Call Option Delta, else return Put Delta
	double NumericalDelta(double ShockSize);			//Calculate Delta by shock BS formula

	double Gamma() const;								//Return Option Gamma
	double NumericalGamma(double ShockSize);			//Calculate Gamma by shock BS formula

	vector<double> VectorPricer(vector<double> source, int metric_index);				//Input is a vector of a specific parameter, metric index: 0-Price,1-Delta,2-Put
	vector<double>	MatrixPricer(vector<vector<double>> source, int metric_index);		//Input is a matrix of all data member, sequesnce S T r b K sig Optiontype






};








#endif // !EuropeanOption_hpp