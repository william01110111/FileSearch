#include "../h/RangeInFile.h"

string RangeInFile::getString()
{
	return file->str().substr(start, end-start);
}

string RangeInFile::getLineString()
{
	int s=start;
	
	while (s>=0 && file->get(s)!='\n')
		s--;
	
	s++;
	
	int e=end;
	
	while (e<int(file->str().size()) && file->get(e)!='\n' && file->get(e)!=10)
		e++;
	
	return file->str().substr(s, e-s);
}

RangeInFile RangeInFile::copyWithSize(int newSize)
{
	return RangeInFile(file, start, start+newSize);//, lineNumber);
}
