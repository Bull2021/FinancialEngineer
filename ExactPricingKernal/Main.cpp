#include "EuropeanOption.hpp"
#include "VanillaOption.hpp"
#include "ExtraFunctions.hpp"
#include <iostream>
#include <algorithm>
#include "PerpetualAmericanOption.hpp"
using namespace std;



int main()
{
	//-----------------------------Group A-----------------------
	
	//----question a:
	//Batch 1
	EuropeanOption Batch1;
	Batch1.Parameters(60, 0.25, 0.08, 0.08, 65, 0.3, 0);
	cout<< "Batch1:"<<endl<<"Call Price: "<<Batch1.CallPrice() << " Put Price: "<<Batch1.PutPrice()<<endl;
	
	
	//Batch 2
	EuropeanOption Batch2;
	Batch2.Parameters(100, 1.0, 0.0, 0.0, 100.0, 0.2, 0);
	cout << "Batch2" << endl << "Call Price: " << Batch2.CallPrice() << " Put Price: " << Batch2.PutPrice() << endl;
	
	
	//Batch 3
	EuropeanOption Batch3;
	Batch3.Parameters(5, 1, 0.12, 0.12, 10, 0.5, 1);
	cout << "Batch3" << endl << "Call Price: " << Batch3.CallPrice() << " Put Price: " << Batch3.PutPrice() << endl;

	
	//Batch 4
	EuropeanOption Batch4;
	Batch4.Parameters(100, 30, 0.08, 0.08, 100, 0.3, 1);
	cout << "Batch4" << endl << "Call Price: " << Batch4.CallPrice() << " Put Price: " << Batch4.PutPrice() << endl;
	cout << endl;

	//----question b:
	cout << "Put/Call Parity:" << endl;

	cout << "Batch1:" << endl;
	cout << "With call price: " << Batch1.Price() << ", Put price calculated is: " << Batch1.PutCallParity()<< endl;
	Batch1.PutCallParityCheck();

	cout << "Batch2:" << endl;
	cout << "With call price: " << Batch2.Price() << ", Put price calculated is: " << Batch2.PutCallParity() << endl;
	Batch2.PutCallParityCheck();

	cout << "Batch3:" << endl;
	cout << "With Put price: " << Batch3.Price() << ", Call price calculated is: " << Batch3.PutCallParity() << endl;
	Batch3.PutCallParityCheck();

	cout << "Batch4:" << endl;
	cout << "With Put price: " << Batch4.Price() << ", Call price calculated is: " << Batch4.PutCallParity() << endl;
	Batch4.PutCallParityCheck();
	cout << endl;

	//----question c:
	//Creating a mesh vector for gradually increasing underlying price, return the corresponding vector option price. 
	vector<double> s1 = MeshVectorCreator(55.0, 65.0, 1);
	EuropeanOption Batch1_copy(Batch1);
	vector<double> p1(s1.size());
	p1=Batch1.VectorPricer(s1, 0);
	cout << "Batch 1 call option price with increasing S from 55 to 65: " << endl;
	PrintVector(p1);
	cout << endl<<endl;
	
	//----question d:
	EuropeanOption Opt;
	vector<vector<double>> v_MatrixInput;
	v_MatrixInput.push_back(s1);
	vector<double> T1 = MeshVectorCreator(0.2,0.3,0.01);
	vector<double> r1 = vector<double>(11, 0.08);
	vector<double> b1 = vector<double>(11, 0.08);
	vector<double> K1 = vector<double>(11, 65.0);
	vector<double> sig1 = MeshVectorCreator(0.25,0.35,0.01);
	vector<double> OptTp1 = vector<double>(11, 0);
	v_MatrixInput.push_back(T1);
	v_MatrixInput.push_back(r1);
	v_MatrixInput.push_back(b1);
	v_MatrixInput.push_back(K1);
	v_MatrixInput.push_back(sig1);
	v_MatrixInput.push_back(OptTp1);
	vector<double> v2 = Opt.MatrixPricer(v_MatrixInput,0);
	cout << "Option Price with Matrix Inputs: " << endl;
	PrintVector(v2);
	cout << endl << endl;
	
	//---------------------------Sensitivity a----------------------------------------
	EuropeanOption Batch5;
	Batch5.Parameters(105, 0.5, 0.1, 0, 100, 0.36, 0);
	cout << "Senesitivity a: " << endl << "Call delta: " << Batch5.CallDelta() << " Put delta:" << Batch5.PutDelta() << endl<<endl;
	
	//---------------------------Sensitivity b----------------------------------------
	EuropeanOption Batch5_copy=Batch5;
	vector<double> s5 = MeshVectorCreator(96, 110, 1);
	vector<double> s5_delta(s5.size());
	s5_delta = Batch5_copy.VectorPricer(s5, 1);
	cout << "Sensitivity b: " << endl<<"Delta with stock increasing from 96 to 110, increment 1"<<endl;
	PrintVector(s5_delta);
	cout << endl<<endl;
	
	//---------------------------Sensitivity c----------------------------------------
	vector<double> v_delta_matrix(v_MatrixInput[0].size());
	v_delta_matrix = Opt.MatrixPricer(v_MatrixInput,1);

	cout << "Sensitivity c:"<<endl<<"Delta with matrix input" << endl;
	PrintVector(v_delta_matrix);
	cout << endl;

	cout << "Gamma with matrix input" << endl;
	vector<double> v_gamma_matrix = Opt.MatrixPricer(v_MatrixInput,2);
	PrintVector(v_gamma_matrix);
	cout << endl<<endl;

	//---------------------------Sensitivity d----------------------------------------
	EuropeanOption Batch4_copy=Batch4;

	Batch4.T = 30.0;
	Batch4.K = 100;
	Batch4.sig = 0.3;
	Batch4.r = 0.08;
	Batch4.S = 100;
	Batch4.b = 0.08;
	Batch4.OptionType = 1;
	cout << "Sensitivity d: Numerical Delta" << endl;
	cout << "BS formula Delta:" << Batch4_copy.Delta() << " , Gamma:" << Batch4_copy.Gamma()<<endl;
	cout << "ShockSize 1 Delta: " << Batch4_copy.NumericalDelta(1.0) << " , Gamma:" << Batch4_copy.NumericalGamma(1.0) << endl;
	cout <<"ShockSize 0.01 Delta: " << Batch4_copy.NumericalDelta(0.01) << " , Gamma:" << Batch4_copy.NumericalGamma(0.01)<<endl<<endl;

	//------------------------------Perpetual American Option b------------------
	PerpetualAmericanOption Batch6;
	Batch6.Parameters(110, 0.1, 0.02, 100, 0.1, 1);
	cout << "Perpetual American b:" << endl;
	cout << "Perpetual American Option Call Price: " << Batch6.CallPrice() << " Put Price: " << Batch6.PutPrice() << endl<<endl;

	//------------------------------Perpetual American Option c------------------
	vector<double> s2 = MeshVectorCreator(105.0, 115.0, 1);
	vector<double> p_s2(s2.size());
	p_s2 = Batch6.VectorPricer(s2);
	cout << "Perpetual American c: increasing underlying stock vector input" << endl;
	PrintVector(p_s2);
	cout << endl << endl;

	//------------------------------Perpetual American Option d------------------
	vector<double> r2 = vector<double>(s2.size(), Batch6.r);
	vector<double> b2 = vector<double>(s2.size(), Batch6.b);
	vector<double> K2 = vector<double>(s2.size(), Batch6.K);
	vector<double> sig2 = vector<double>(s2.size(), Batch6.sig);
	vector<double> OptType2 = vector<double>(s2.size(), 1);
	vector<vector<double>> Matrix_PAO;
	Matrix_PAO.push_back(s2);
	Matrix_PAO.push_back(r2);
	Matrix_PAO.push_back(b2);
	Matrix_PAO.push_back(K2);
	Matrix_PAO.push_back(sig2);
	Matrix_PAO.push_back(OptType2);
	PerpetualAmericanOption PAO;
	vector<double> p_PAO(r2.size());
	p_PAO = PAO.MatrixPricer(Matrix_PAO);
	cout << "Perpetual American d: matrix input" << endl;
	PrintVector(p_PAO);
	cout << endl;

	return 0;
}

