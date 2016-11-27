#include "../h/Index.h"

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>

#include "../h/TrieNode.h"
#include "../h/fileIO.h"
#include "../h/stringHelpers.h"

Index index;

Index::Index()
{
	root=TrieNode::makeDefaultBranch();
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
		
		RangeInFile range{file, i, i};
		
		unique_ptr<TrieNode> newRoot=root->add(range);
		
		if (newRoot)
		{
			root=move(newRoot);
		}
	}
}

void Index::addTextFilesInDirectory(string directory)
{
	vector<string> filepaths;
	
	cout << "finding files in " << directory << "..." << endl;
	
	getAllFilesInFolder(directory, filepaths);
	
	vector<string> extensions;
	string textFiles=".txt .c .cpp .h .hpp .py .swift .css .html .htm .html5 .java .xml .plist";
	sliceStringBy(textFiles, " ", extensions);
	
	filepaths.erase(
		std::remove_if(
			filepaths.begin(),
			filepaths.end(),
			[&]( const string& i ) // lambda
			{
				for (auto j=extensions.begin(); j!=extensions.end(); j++)
				{
					if (substringMatches(i, i.size()-j->size(), *j))
						return false;
				}
				
				return true;
			}
		),
		filepaths.end()
	);
	
	cout << "indexing files..." << endl;
	
	for (int i=0; i<int(filepaths.size()); i++)
	{
		cout << i << "/" << filepaths.size() << " (" << (i*10000/filepaths.size())/100.0 << "%) " << filepaths[i] << "..." << endl;
		
		addFile(filepaths[i]);
	}
	
	cout << "done indexing" << endl;
}

void Index::searchFor(string query, vector<RangeInFile>& out)
{
	root->get(query, out);
	
	for (int i=0; i<int(out.size()); i++)
	{
		out[i]=out[i].copyWithSize(query.size());
	}
}


