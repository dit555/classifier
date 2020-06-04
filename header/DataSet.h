#ifndef _DATA_SET_
#define _DATA_SET_

#include <string>
#include <stack>

#include "Instance.h"

using std::stack;
using std::string;

class DataSet {
public:
	DataSet(string inputFile);
	void addInstance(int i,int n, double* fact);
	
	~DataSet();

private:
stack<Instance*> tempStorage;
int numInstances;
double* mean;
Instance* Instances;

};
#endif
