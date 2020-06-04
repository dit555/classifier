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
		mean1 = new double[numFactors];
		mean2 = new double[numFactors];
		stdev1 = new double[numFactors];
		stdev2 = new double[numFactors];
		
		//get num class 1 and 2
		num1 = 0;
		num2 = 0;
		for (int i = 0; i < numInstances; i++){
			if (tempStorage[i]->getClass() == 1)
				num1++;
			else
				num2++;
		}
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
		mean1[i] = 0;
		mean2[i] = 0;
		for (int j = 0; j < numInstances; j++){
			if(tempStorage[j]->getClass() == 1)
				mean1[i] += tempStorage[j]->getFactor(i);
			else
				mean2[i] += tempStorage[j]->getFactor(i);
		}
	}

	for (int i = 0; i < numFactors; i++){
		mean1[i] /= num1;
		mean2[i] /= num2;
		//cout << mean[i] << endl;
	}

}

void DataSet::calcStdev(){
	double variance1 = 0;
	double variance2 = 0;
	double dev;
	for (int j = 0; j < numFactors; j++){
		variance1 = 0;
		variance2 = 0;
		for (int i = 0; i < numInstances; i ++){
			if (tempStorage[i]->getClass() == 1)
				variance1 += pow(tempStorage[i]->getFactor(j) - mean1[j], 2);
			else
				variance2 += pow(tempStorage[i]->getFactor(j) - mean2[j], 2);
		}
		variance1 /= num1;
		variance2 /= num2;
		stdev1[j] = sqrt(variance1);
		stdev2[j] = sqrt(variance2);
	}

	//for (int i = 0; i < numFactors; i++)
	//	cout << stdev[i] << endl;
}

void DataSet::normalize(){
	calcMean();
	calcStdev();

	//Z-normalization
	for (int i = 0; i < numFactors; i++){
		for(int j = 0; j < numInstances; j++){
			if (tempStorage[j]->getClass() == 1){	
				double temp1 = (tempStorage[j]->getFactor(i) - mean1[i])/stdev1[i];
				tempStorage[j]->setFactor(i, temp1);
			}
			else{
				double temp2 = (tempStorage[j]->getFactor(i) - mean2[i])/stdev2[i];
                        	tempStorage[j]->setFactor(i, temp2);
			}
		}

	}

	
	//test normaliation
	/*
	calcMean();
	calcStdev();

	for (int i = 0; i < numFactors; i++){
		
		cout << "mean1: " << mean1[i] << endl;
		cout << "stdev1: " << stdev1[i] << endl;
		
		cout << "mean2: " << mean2[i] << endl;
                cout << "stdev2 " << stdev2[i] << endl;
		
	}
	*/
	
}

void DataSet::printAll(){
	for (int i = 0; i < numInstances; i++)
		tempStorage[i]->print();
}

DataSet::~DataSet(){
	delete[] mean1;
	delete[] mean2;
	delete[] stdev1;
	delete[] stdev2;
}
