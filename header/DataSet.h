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
	
	~DataSet();

private:
vector<Instance*> tempStorage;
int numInstances;
double* mean;

};
#endif
