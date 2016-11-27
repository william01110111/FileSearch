#include "../h/Index.h"

#include "../h/TrieNode.h"
#include "../h/fileIO.h"

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
		
		RangeInFile range{file, i, i+1, lineNumber};
		
		unique_ptr<TrieNode> newRoot=root->add(range);
		
		if (newRoot)
		{
			root.swap(newRoot);
		}
	}
}

void Index::searchFor(string query, vector<RangeInFile>& out)
{
	root->get(query, out);
}
