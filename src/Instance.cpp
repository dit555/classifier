#include <iostream>

#include "../header/Instance.h"

Instance::Instance (int t, int n, double *fact){
	type = t;
	numFactors = n;
	double *f = new double[n];
	f = fact;
	factors = fact;
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

