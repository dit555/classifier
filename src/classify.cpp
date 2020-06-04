#include <iostream>
#include <string>

#include "../header/DataSet.h"

using std::string;

int main(){
	string input = "_sets/cs_170_large17.txt";
	DataSet a(input);
	a.normalize();
	return 0;
}
