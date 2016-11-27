#include "../h/Index.h"

#include <iostream>
using std::cout;
using std::endl;

#include "../h/TrieNode.h"
#include "../h/fileIO.h"
#include "../h/stringHelpers.h"

Index index;

Index::Index()
{
	root=unique_ptr<TrieNode>(TrieNode::makeHashmap());
}

void Index::addFile(string filePath)
{
	FileData* file=new FileData(filePath);
	
	files.push_back(unique_ptr<FileData>(file));
	
	string str=file->str();
	
	int lineNumber=1;
	
	for (int i=0; i<int(str.size()); i++)
	{
		if (file->get(i)=='\n')
			lineNumber++;
		
		RangeInFile range{file, i, i, lineNumber};
		
		unique_ptr<TrieNode> newRoot=root->add(range);
		
		if (newRoot)
		{
			root.swap(newRoot);
		}
	}
}

void Index::addAllFilesWithPostfix(vector<string>& filepaths, vector<string>& postfix)
{
	for (int i=0; i<int(filepaths.size()); i++)
	{
		for (auto j=postfix.begin(); j!=postfix.end(); j++)
		{
			if (substringMatches(filepaths[i], filepaths[i].size()-j->size(), *j))
			{
				cout << i << "/" << filepaths.size() << " (" << i*100/filepaths.size() << "%) - indexing " << filepaths[i] << "..." << endl;
				
				addFile(filepaths[i]);
			}
		}
	}
}

void Index::searchFor(string query, vector<RangeInFile>& out)
{
	root->get(query, out);
	
	for (int i=0; i<int(out.size()); i++)
	{
		out[i]=out[i].copyWithSize(query.size());
	}
}


