#include "../h/fileIO.h"

#include <fstream>

#include <sstream>

#include <iostream>
using std::cout;
using std::endl;

#include <dirent.h> //used for getting file in folder lists
#include <sys/stat.h> //used for telling if a file is really a folder

bool loadEntireFile(string inName, bool printOutput, string& out)
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
		return false;
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
		return true;
	}
}

bool getAllFilesInFolder(string folder, vector<string>& filepathsOut)
{
	DIR *dp;
	struct dirent *dirp;
	struct stat filestat;
	
	if(!(dp  = opendir(folder.c_str()))) {
		cout << "Error opening applications directory" << endl;
		return false;
	}
	
	while ((dirp = readdir(dp))) {
		
		string filename=dirp->d_name;
		
		//Skip current object if it is this directory or parent directory
		if(filename.size()>0 && filename[0]!='.')
		{
			string path=folder+"/"+filename;
			
			//get stats on file/folder
			if (stat(path.c_str(), &filestat))
			{
				cout << "error getting stats!" << endl;
				return false;
			}
			
			//Recursively call this function if current object is a directory
			if(S_ISDIR(filestat.st_mode))
			{
				getAllFilesInFolder(path, filepathsOut);
			}
			else
			{
				filepathsOut.push_back(path);
			}
		}
	}
	
	closedir(dp);
	return true;
}
