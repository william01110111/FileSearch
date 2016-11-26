#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <memory>
using std::unique_ptr;

#include "TrieNode.h"
#include "PositionInFile.h"

class Index
{
public:
	
	Index();
	
	void addFile(string filePath);
	
	void searchFor(string query, vector<PositionInFile>& out);
	
private:
	
	unique_ptr<TrieNode> root;
	
	vector<string> filenames;
};
