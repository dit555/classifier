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
			string temp;
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
					cout << value << "  ";
					i += 3;
				}
				
				i++;
			}
			cout << endl;

		}

	}
	else
		cout << "file failed to open" << endl;

	file.close();
}
