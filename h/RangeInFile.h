#pragma once

#include "FileData.h"

class RangeInFile
{
public:
	RangeInFile(FileData* fileIn, int startIn, int endIn)//, int lineNumberIn)
	{
		file=fileIn;
		start=startIn;
		end=endIn;
		//lineNumber=lineNumberIn;
	}
	
	//inline FileData* getFile() {return file;}
	//inline int getStart() {return startIndex;}
	//inline int getEnd() {return endIndex;}
	inline int getLength() {return end-start;}
	//inline int getLineNumber() {return lineNumber;}
	inline char getCharAfterEnd() {return file->get(end);}
	inline void incrementEnd() {end++;}
	string getString();
	string getLineString();
	RangeInFile copyWithSize(int newSize); // makes a copy of this objet with the same start but of the specified size
	
public:
	FileData* file; // the file
	int start; // the position of the first character in the range (inclusive)
	int end; // the position of the last character in the range (exclusive)
	//int lineNumber;
};
