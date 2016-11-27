#include "../h/RangeInFile.h"

string RangeInFile::getString()
{
	return file->str().substr(startIndex, endIndex-startIndex);
}

string RangeInFile::getLineString()
{
	int s=startIndex;
	
	while (s>=0 && file->get(s)!='\n')
		s--;
	
	s++;
	
	int e=endIndex;
	
	while (e<int(file->str().size()) && file->get(e)!='\n' && file->get(e)!=10)
		e++;
	
	return file->str().substr(s, e-s);
}

RangeInFile RangeInFile::copyWithSize(int newSize)
{
	return RangeInFile(file, startIndex, startIndex+newSize, lineNumber);
}
