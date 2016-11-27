#include <iostream>
using std::cout;
using std::endl;

#include "../h/Index.h"
#include "../h/stringHelpers.h"

int main(int argc, char** argv)
{
	vector<string> filepaths;
	
	getAllFilesInFolder(".", filepaths);
	
	cout << "filepaths:" << endl;
	
	cout << "adding files to index..." << endl;
	
	for (auto i: filepaths)
	{
		index.addFile(i);
	}
	
	//index.addFile("src/main.cpp");
	//index.addFile("testSearchFile.txt");
	
	cout << "searching for file.." << endl;
	
	vector<RangeInFile> results;
	
	index.searchFor("include", results);
	
	cout << "results:" << endl;
	
	for (auto i: results)
	{
		string labelString;
		
		labelString+=i.getFile()->getFilepath();
		labelString+=" line ";
		labelString+=std::to_string(i.getLineNumber());
		
		cout << putStringInBox(i.getLineString(), false, labelString) << endl;
	}
}
