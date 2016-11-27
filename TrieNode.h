#pragma once

#include "PositionInFile.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>
using std::unique_ptr;

class TrieNode
{
public:
	
	static unique_ptr<TrieNode> makeHashmap();
	static unique_ptr<TrieNode> makeLeaf(RangeInFile& range);
	
	virtual unique_ptr<TrieNode> add(RangeInFile& range)=0;
	
	virtual void get(string query, vector<RangeInFile>& out)=0;
};
