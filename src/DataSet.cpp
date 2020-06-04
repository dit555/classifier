#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using std::string;
using std::stod;

using std::cout;
using std::endl;

using std::fstream;
using std::getline;


#include "../header/DataSet.h"
#include "../header/Instance.h"

DataSet::DataSet (string input){
	fstream file;
	file.open(input, std::ios::in);
	int spaces = 0;
	numInstances = 0;
	if (file.is_open()){
		string g;
		string::size_type sz;
		while(getline(file, g)){
			int i = 0;
			spaces = 0;
			//find spaces in line
			while (i < g.size()){
				if (g[i] == ' ' || (g[i] == '-' && g[i - 1] == ' '))
					spaces++;
				i++;
			}
			spaces = spaces / 2;
			i = 0;
			double input;
			double exp;
			double value;
			int index = 0;
			string temp;

			double* facts = new double[spaces - 2];
			int clas = 0;
			//interpret lines			
			while (i < g.size()){
				if (g[i] != ' '){
					//if negative
					if (g[i] == '-'){
						temp = g.substr(i, 10);
						input = stod(temp, &sz);
						i += 11;
					}
					else{
						temp = g.substr(i, 9);
						input = stod(temp, &sz);
						i += 10;
					}

					temp = g.substr(i, 4);
					exp = stod(temp, &sz);
					
					value = input * pow(10, exp);
					
					i += 3;
				
					
	                                if(index == 0){            
        	                                clas = (int)value;
						//cout << clas << "  ";
                	                        index++;
					}
					else if(index <= spaces - 2){
                                        	//cout << "value: " << value << "  " << "index: " << index << "  ";
                                        	facts[index - 1] = value;
                                        	//cout << facts[index - 1] << "  ";
						//cout << "INDEX: " << index - 1 << endl;
                                        	index++;
                                	}

				
				}
				
				i++;
				
			}
			
			numFactors = spaces - 2;
			addInstance(clas, numFactors, facts);
			

		}
		
		numInstances = tempStorage.size();
		mean = new double[numFactors];
		stdev = new double[numFactors];


	}
	else
		cout << "file failed to open" << endl;
	
	
	file.close();
}

void DataSet::addInstance(int i, int n, double* fact){
	Instance* a = new Instance(i, n, fact);
	tempStorage.push_back(a);
}

void DataSet::calcMean(){

	for (int i = 0; i < numFactors; i++){
		mean[i] = 0;
		for (int j = 0; j < numInstances; j++){
			mean[i] += tempStorage[j]->getFactor(i);
		}
	}

	for (int i = 0; i < numFactors; i++){
		mean[i] /= numInstances;
		//cout << mean[i] << endl;
	}

}

void DataSet::calcStdev(){
	double variance = 0;
	double dev;
	for (int j = 0; j < numFactors; j++){
		variance = 0;
		for (int i = 0; i < numInstances; i ++){
			variance += pow(tempStorage[i]->getFactor(j) - mean[j], 2);
		}
		variance /= numInstances;
		stdev[j] = sqrt(variance);
	}

	for (int i = 0; i < numFactors; i++)
		cout << stdev[i] << endl;
}

void DataSet::normalize(){
	calcMean();
	calcStdev();
}



DataSet::~DataSet(){
	delete[] mean;
	delete[] stdev;
}
