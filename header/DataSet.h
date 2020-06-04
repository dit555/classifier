#ifndef _DATA_SET_
#define _DATA_SET_

#include <string>
#include <vector>

#include "Instance.h"


using std::vector;
using std::string;

class DataSet {
public:
	DataSet(string inputFile);
	void addInstance(int i,int n, double* fact);
	void calcMean();
	void calcStdev();
	void normalize();
	void genTestSet(int i);

	void printAll();
	~DataSet();

private:
vector<Instance*> tempStorage;
int numInstances;
int numFactors;
int num1;
int num2;
double* mean1;
double* mean2;
double* stdev1;
double* stdev2;

Instance* testSet[10];
};
#endif
