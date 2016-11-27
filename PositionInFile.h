#pragma once

#include "FileData.h"

struct RangeInFile
{
	FileData* file; // the file
	int startIndex; // the position of the first character in the range (inclusive)
	int endIndex; // the position of the last character in the range (exclusive)
};
