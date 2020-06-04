#ifndef _INSTANCE_
#define _INSTANCE_

class Instance{
public:
	Instance (int t, int n, double* fact);
	void print();
	int getClass();
	double getFactor(int n);
	void setFactor(int n, double fact);
	int getNumFactors();
	~Instance();

private:
int type;
int numFactors;
double *factors;

};


#endif
