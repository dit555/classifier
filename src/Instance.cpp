#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../header/Instance.h"

using std::cout;
using std::endl;

Instance::Instance (int t, int n, double *fact){
	type = t;
	numFactors = n;
	factors = fact;
}

Instance::Instance(Instance* parent){
	type = parent->getClass();
	numFactors = parent->getNumFactors();
	factors = new double[numFactors];

	srand(time(NULL));
	for (int i = 0; i < numFactors;i++){
		double r = (double)(rand() % 21 - 10) / 100;
		factors[i] = parent->getFactor(i) + r;
	}

//	parent->print();
//	print();

	
}

void Instance::print(){
	cout << type << "  ";
	for (int i = 0; i < numFactors; i++)
		cout << getFactor(i) << "  ";
	cout << endl;
}

int Instance::getClass(){
	return type;
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

double* Instance::getFacts(){
	return factors;
}

Instance::~Instance(){
	delete[] factors;
}

