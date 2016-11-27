#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

//	returns false if there is an error, true if file read worked
bool loadEntireFile(string fileneme, bool printOutput, string& out);

//	returns true if worked, false if error
bool getAllFilesInFolder(string folder, vector<string>& filepathsOut);
