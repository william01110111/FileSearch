
#include "../h/TrieNode.h"

class TrieNodeArray: public TrieNode
{
public:
	
	unique_ptr<TrieNode> add(RangeInFile& range)
	{
		myRanges.push_back(range);
		return nullptr;
	}
	
	void get(string query, vector<RangeInFile>& out)
	{
		for (auto i: myRanges)
		{
			out.push_back(i);
		}
	}
	
private:
	
	vector<RangeInFile> myRanges;
};


unique_ptr<TrieNode> TrieNode::makeArray()
{
	return unique_ptr<TrieNode>(new TrieNodeArray());
}

