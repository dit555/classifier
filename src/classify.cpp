#include <iostream>
#include <string>

#include "../header/DataSet.h"

using std::string;
using std::cout;
using std::endl;

int main(){
	int k = 5;
	string input = "_sets/cs_170_small17.txt";
	DataSet a(input);
	a.normalize();
	//a.printAll();
	//cout << a.nearNeighbor(2, -1.55064) << endl;
	//cout << "Running nearest neighbor with LOO classification for for all features." << endl << "accuracy: " << a.loo(k) << "% when spliting training set into " << k << "." << endl;
	a.forwardSelection(10);
	return 0;
}
