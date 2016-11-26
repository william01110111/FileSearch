#include "fileIO.h"

#include <fstream>

#include <sstream>

#include <iostream>
using std::cout;
using std::endl;

void loadEntireFile(string inName, bool printOutput, string& out)
{
	std::fstream inFile;
	
	if (printOutput)
		cout << "attempting to open '" << inName << "'..." << endl;
	
	inFile.open(inName);
	
	if (!inFile.is_open())
	{
		if (printOutput)
			cout << "'" << inName << "' failed to open :(" << endl;
		out="";
	}
	else
	{
		if (printOutput)
			cout << "file opended, reading file..." << endl;
		
		std::stringstream strStream;
		strStream << inFile.rdbuf(); // read the file
		out = strStream.str(); // str holds the content of the file
		inFile.close();
		
		if (printOutput)
			cout << "file reading done, '" << inName << "' closed" << endl;
	}
}

