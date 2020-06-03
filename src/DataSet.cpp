#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cout;
using std::endl;

using std::fstream;


#include "../header/DataSet.h"

DataSet::DataSet (string input){
	fstream file;
	file.open(input, std::ios::in);
	if (file.is_open()){
		string g;
		while(getline(file, g)){
			cout << g << endl;
		}
		file.close();

	}
	else
		cout << "file failed to open" << endl;
}
