#pragma once

#include "../h/RangeInFile.h"

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
	static unique_ptr<TrieNode> makeHashmap(char c, unique_ptr<TrieNode> node);
	static unique_ptr<TrieNode> makeLeaf(RangeInFile& range);
	static unique_ptr<TrieNode> makeMultiLeaf();
	static unique_ptr<TrieNode> makeMultiChar(vector<char> charsIn, unique_ptr<TrieNode> nodeIn);
	
	virtual unique_ptr<TrieNode> add(RangeInFile& range)=0;
	
	virtual string getString()=0;
	
	virtual void get(string query, vector<RangeInFile>& out)=0;
};
