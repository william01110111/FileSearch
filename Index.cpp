#include "Index.h"

#include "TrieNode.h"
#include "fileIO.h"

Index::Index()
{
	root=unique_ptr<TrieNode>(TrieNode::makeHashmap());
}

void Index::addFile(string filePath)
{
	string fileContents;
	
	loadEntireFile(filePath, true, fileContents);
	
	if (!fileContents.empty())
	{
		int filenameIndex=filenames.size();
		filenames.push_back(filePath);
		
		for (int i=0; i<int(fileContents.size()); i++)
		{
			root->add(fileContents, PositionInFile{filenameIndex, i});
		}
	}
}

void Index::searchFor(string query, vector<PositionInFile>& out)
{
	root->get(query, out);
}
