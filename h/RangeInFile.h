#pragma once

#include "FileData.h"

class RangeInFile
{
public:
	RangeInFile(FileData* fileIn, int startIn, int endIn, int lineNumberIn)
	{
		file=fileIn;
		startIndex=startIn;
		endIndex=endIn;
		lineNumber=lineNumberIn;
	}
	
	inline FileData* getFile() {return file;}
	inline int getStart() {return startIndex;}
	inline int getEnd() {return endIndex;}
	inline int getLineNumber() {return lineNumber;}
	inline char getCharAfterEnd() {return file->get(endIndex);}
	inline void incrementEnd() {endIndex++;}
	string getString();
	string getLineString();
	RangeInFile copyWithSize(int newSize); // makes a copy of this objet with the same start but of the specified size
	
private:
	FileData* file; // the file
	int startIndex; // the position of the first character in the range (inclusive)
	int endIndex; // the position of the last character in the range (exclusive)
	int lineNumber;
};
