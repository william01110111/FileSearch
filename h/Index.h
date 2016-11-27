#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <memory>
using std::unique_ptr;

#include "TrieNode.h"
#include "../h/RangeInFile.h"
#include "FileData.h"

class Index
{
public:
	
	Index();
	
	void addFile(string filePath);
	
	void searchFor(string query, vector<RangeInFile>& out);
	
private:
	
	unique_ptr<TrieNode> root;
	
	vector<unique_ptr<FileData>> files;
	
};

extern Index index;
