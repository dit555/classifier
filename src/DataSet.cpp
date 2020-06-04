#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using std::string;
using std::stod;

using std::cout;
using std::endl;

using std::fstream;


#include "../header/DataSet.h"
#include "../header/Instance.h"

DataSet::DataSet (string input){
	fstream file;
	file.open(input, std::ios::in);
	if (file.is_open()){
		string g;
		string::size_type sz;
		while(getline(file, g)){
			int i = 0;
			int spaces = 0;
			//find spaces in line
			while (i < g.size()){
				if (g[i] == ' ')
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

			double* facts = new double[spaces - 1];

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
				
					int clas = 0;
	                                if(index == 0){            
        	                                clas = (int)value;
						cout << clas << "  ";
                	                        index++;
					}
					else if(index <= spaces - 2){
                                        	//cout << "value: " << value << "  " << "index: " << index << "  ";
                                        	facts[index - 1] = value;
                                        	cout << facts[index - 1] << "  ";
						//cout << "INDEX: " << index - 1 << endl;
                                        	index++;
                                	}

				
				}
				
				i++;
			}
			cout << "poop" <<endl;
			delete[] facts;
			

		}

	}
	else
		cout << "file failed to open" << endl;

	file.close();
}

void DataSet::addInstance(int i, int n, double* fact){
	Instance* a = new Instance(i, n, fact);
	tempStorage.push(a);
}

DataSet::~DataSet(){
	while(!tempStorage.empty()){
		delete[] tempStorage.top();
		tempStorage.pop();
	}
}
