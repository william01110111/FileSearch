#pragma once

#include <string>
using std::string;

#include <memory>
using std::unique_ptr;

#include "fileIO.h"

class FileData
{
public:
	//	does not load file until the file data is requested
	FileData(string filepathIn)
	{
		filepath=filepathIn;
	}
	
	//	get the file data, loading file if needed
	inline string& str()
	{
		if (!fileData)
		{
			fileData=unique_ptr<string>(new string);
			
			loadEntireFile(filepath, true, *fileData);
		}
		
		return *fileData;
	}
	
	inline char get(int index)
	{
		string& fileStr=str();
		
		if (index<int(fileStr.size()))
		{
			return fileStr[index];
		}
		else
		{
			return 0;
		}
	}
	
	string getFilepath()
	{
		return filepath;
	}
	
	//	drop the files data if it is loaded (presumably to save memory)
	void dropData()
	{
		fileData=unique_ptr<string>(nullptr);
	}
	
private:
	string filepath;
	unique_ptr<string> fileData{nullptr};
};
