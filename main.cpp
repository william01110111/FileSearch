#include <iostream>
using std::cout;
using std::endl;

#include "Index.h"

int main(int argc, char** argv)
{
	Index index;
	
	cout << "adding file to index..." << endl;
	
	index.addFile("main.cpp");
	
	cout << "searching for file.." << endl;
	
	vector<PositionInFile> results;
	
	index.searchFor("dex", results);
	
	cout << "results:" << endl;
	
	for (auto i: results)
	{
		cout << i.charPos << endl;
	}
}
