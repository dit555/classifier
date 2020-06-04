#include <iostream>
#include <string>

#include "../header/DataSet.h"

using std::string;
using std::cout;
using std::endl;

int main(){
	string input = "_sets/cs_170_small17.txt";
	DataSet a(input);
	a.normalize();
	//a.printAll();
	cout << a.nearNeighbor(2, -1.55064) << endl;
	return 0;
}
