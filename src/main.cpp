#include <iostream>
using std::cout;
using std::endl;

#include "../h/Index.h"
#include "../h/stringHelpers.h"

int main(int argc, char** argv)
{
	//index.addTextFilesInDirectory("/home/william/mscl/linux-4.8.10/");
	//index.addTextFilesInDirectory(".");
	index.addTextFilesInDirectory("testSearchFile.txt");
	
	cout << "index: " << endl << index.getString() << endl;
	
	//index.addFile("src/main.cpp");
	//index.addFile("testSearchFile.txt");
	
	cout << "searching.." << endl;
	
	vector<RangeInFile> results;
	
	//index.searchFor("part->elements[i] != FLEX_ARRAY_FREE", results);
	index.searchFor("makeHashmap(", results);
	
	cout << "results:" << endl;
	
	for (auto i: results)
	{
		string labelString;
		
		labelString+=i.file->getFilepath();
		labelString+=" line ";
		labelString+=std::to_string(i.lineNumber);
		
		cout << putStringInBox(i.getLineString(), false, labelString) << endl;
		//cout << putStringInBox(i.getString(), false, labelString) << endl;
	}
	
}
