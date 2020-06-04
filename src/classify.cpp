#include <iostream>
#include <string>

#include "../header/DataSet.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

int main(){

	string input;
	cout << "Welcome to Dumitru Chiriac's feature search algorithm." << endl << endl;
	cout << "enter the file path>> ";
	cin >> input;

	cout << input << endl; // so that the trace has a record of what file is inputted


	int k = 5;
	
	DataSet a(input);
	a.normalize();
	//a.printAll();
	//cout << a.nearNeighbor(2, -1.55064) << endl;
	cout << endl << "Running nearest neighbor with LOO classification for for all features." << endl << "Accuracy is " << a.loo(k) << "% when spliting training set into " << k << "." << endl << endl << endl;
	a.forwardSelection(30);
	return 0;
}
