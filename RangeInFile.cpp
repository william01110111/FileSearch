#include "PositionInFile.h"

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
	
	while (e<int(file->str().size()) && file->get(e)!='\n')
		e++;
	
	return file->str().substr(s, e-s);
}
