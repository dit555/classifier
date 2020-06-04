#include <iostream>

#include "../header/Instance.h"

using std::cout;
using std::endl;

Instance::Instance (int t, int n, double *fact){
	type = t;
	numFactors = n;
	double *f = new double[n];
	f = fact;
	factors = fact;
}

void Instance::print(){
	cout << type << "  ";
	for (int i = 0; i < numFactors; i++)
		cout << getFactor(i) << "  ";
	cout << endl;
}

double Instance::getFactor(int n){
	return factors[n];
}

void Instance::setFactor(int n, double fact){
	factors[n] = fact;
}

int Instance::getNumFactors(){
	return numFactors;
}

Instance::~Instance(){
	delete[] factors;
}

