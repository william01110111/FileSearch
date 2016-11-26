#pragma once

#include "PositionInFile.h"

#include <string>
using std::string;

class TrieNode
{
public:
	
	static TrieNode* makeHashmap();
	
	virtual void add(string& entireFile, PositionInFile pos)=0; // this uses the pos to know where in the entireFile to start
	
	virtual void get(string query, vector<PositionInFile>& out)=0; // recursivly searches and adds any matches to the vector
};
