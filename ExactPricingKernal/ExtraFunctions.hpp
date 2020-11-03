#ifndef ExtraFunctions_hpp
#define ExtraFunctions_hpp

#include<iostream>
#include"EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include<vector>
using namespace std;

//Function to create a mesh vector by low bound, upbound and h as mesh size(increment)
vector<double> MeshVectorCreator(double lbound, double ubound, double h)
{
	vector<double> v;
	for (int i = 0; ubound - lbound - i * h > 0.000001; ++i)
	{
		v.push_back(lbound + i * h);

	}
	return v;
}

//Function to print a vector
void PrintVector(vector<double> source)
{
	vector<double>::iterator it;
	for ( it = source.begin(); it != source.end(); ++it)
	{
		cout << *it << " ";
	}
}




#endif // !ExtraFunctions_hpp
