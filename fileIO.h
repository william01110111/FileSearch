#pragma once

#include <string>
using std::string;

//	returns false if there is an error, true if file read worked
bool loadEntireFile(string fileneme, bool printOutput, string& out);
