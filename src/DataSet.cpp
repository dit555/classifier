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
		sol = new int[numFactors];	
		numTests = 0;
		
		cout << endl << "This data set has " << numFactors << " features and " << numInstances << " instances." << endl << endl;
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
	
	cout << "Normalizing...            ";

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

	cout << "Done" << endl << endl;
}

void DataSet::genTestSet(int i){
	testSet = new Instance*[i];
	numTests = i;
	for(int j = 0; j < i; j++){
		 Instance* test = new Instance(tempStorage[j]);
		 testSet[j] = test;
	}	
}

int DataSet::nearNeighbor(int fact, double val, int offset){
	double pos = val;
	double dist = 0.01;
	double r = 1;
	//cout << val << endl;
	while(1){
		double upper = pos + dist * r;
                double lower = pos - dist * r;

		for (int i = offset; i < numInstances; i++){
			if (upper >= tempStorage[i]->getFactor(fact) && lower <= tempStorage[i]->getFactor(fact))
				return tempStorage[i]->getClass();
		}
		//cout << "testing:   upper:" << upper << "   lower: " << lower << endl;
		r++;
		if (r > 300)
			break;
	}

	return 0;
}

double DataSet::accuracy(int fact){
	
	cout << " using feature(s): {";
	for (int i = 0; i < fact; i++)
		cout << sol[i] << " ";

	cout << "} accuracy is: ";
	
	double correct = 0;
	double incorrect = 0;
	for (int i = 0; i < fact; i++){
		//cout << "cake" << numTests << endl;
		for (int j = 0; j < numTests; j++){
			//cout << "poop" << j << endl;
			if(testSet[j]->getClass() == nearNeighbor(sol[i], testSet[j]->getFactor(i), 0))
					correct++;
			else
				incorrect++;
		}
	}
	
	double ac = correct/(correct + incorrect) * 100;
	cout << ac << "%" << endl;
	return ac;
}

double DataSet::loo(int k){
	int test = numInstances/k;
	//cout << test << endl;
       	double correct = 0;
        double incorrect = 0;
	for (int i = 0; i < numFactors; i++){
                //cout << "cake" << i << endl;
                for (int j = 0; j < test; j++){
                        //cout << "poop" << j << endl;
                        if(tempStorage[j]->getClass() == nearNeighbor(i, tempStorage[j]->getFactor(i), test))
                                        correct++;
                        else
                                incorrect++;
                }
        }
        //cout << "correct " << correct << " times out of " << correct + incorrect << endl;
        return correct/(correct + incorrect) * 100;	

}
void DataSet::forwardSelection(int k){
	cout << "Begining Forward selection... " << endl << endl;

	genTestSet(k);
	double maxTot = 0;
	double maxCur = 0;
	int index = 0;
	int maxIndex;
	bool dup = false;
	bool less = false;
	while (maxTot >= maxCur && index < numFactors){
		maxCur = 0;
		for (int i = 0; i < numFactors; i++){
			dup = false;
			for (int j = 0; j < index; j++){
				sol[index] = i; 
				if (sol[j] == sol[index]){
					dup = true;
					//cout << "excluded: " << sol[index] << "  when i = " << i << "  and j = " << j << endl;
				}
			}	
			if (!dup){
				int temp = 0;
				sol[index] = i;
				//cout << "index: " << index << "  ";
				temp = accuracy(index + 1);
				if (temp > maxCur){
					maxCur = temp;
					maxIndex = i;
				}
			}
			//cout << "i :" << i << endl;
		}

		
		if (maxCur > maxTot){
			sol[index] = maxIndex;
			maxTot = maxCur;
		}
		else
			less = true;
		index++;
		cout << endl;
		cout << "best solution is this iteration is: {";
	        for (int i = 0; i < index; i++)
        	        cout << sol[i] << " ";
        	
		cout << "} with accuracy: " << maxCur << "%" << endl << endl;
		if (less)
			break;

	}
	cout << "-------------------------------------------" << endl << endl;
	cout << "best solution is made using features: {";
        for (int i = 0; i < index - 1; i++)
                cout << sol[i] << " ";
	cout << "} with accuracy: " << maxTot << "%" << endl;	

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
	delete[] sol;
}
