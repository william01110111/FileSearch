#include <iostream>
using std::cout;
using std::endl;

#include "Index.h"

int main(int argc, char** argv)
{
	cout << "adding file to index..." << endl;
	
	index.addFile("main.cpp");
	
	cout << "searching for file.." << endl;
	
	vector<RangeInFile> results;
	
	index.searchFor("#", results);
	
	cout << "results:" << endl;
	
	for (auto i: results)
	{
		cout << "_____________________________________________________________" << endl << endl;
		
		cout << i.getLineString() << endl;
	}
}
