
#include "../h/TrieNode.h"

class TrieNodeMultiLeaf: public TrieNode
{
public:
	
	unique_ptr<TrieNode> add(RangeInFile& range)
	{
		myRanges.push_back(range);
		return nullptr;
	}
	
	string getString()
	{
		return std::to_string(myRanges.size())+" leaves";
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


unique_ptr<TrieNode> TrieNode::makeMultiLeaf()
{
	return unique_ptr<TrieNode>(new TrieNodeMultiLeaf());
}

