#include <iostream>
#include <string>

#include "../header/DataSet.h"

using std::string;

int main(){
	string input = "_sets/cs_170_small17.txt";
	DataSet a(input);
	a.normalize();
	//a.printAll();
	a.genTestSet(1);
	return 0;
}
