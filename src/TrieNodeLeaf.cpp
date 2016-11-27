#include "../h/TrieNode.h"

class TrieNodeLeaf: public TrieNode
{
public:
	
	TrieNodeLeaf(RangeInFile& rangeIn): myRange(rangeIn) {}
	
	unique_ptr<TrieNode> add(RangeInFile& range)
	{
		unique_ptr<TrieNode> newNode;
		
		if (myRange.getCharAfterEnd()==0 && range.getCharAfterEnd()==0)
		{
			newNode=makeMultiLeaf();
		}
		else
		{
			newNode=makeHashmap();
		}
		
		//	do not increment ranges as the new node will replace this one, not go below it
		
		newNode->add(myRange);
		newNode->add(range);
		
		return newNode;
	}
	
	void get(string query, vector<RangeInFile>& out)
	{
		out.push_back(myRange);
	}
	
private:
	
	RangeInFile myRange;
};


unique_ptr<TrieNode> TrieNode::makeLeaf(RangeInFile& range)
{
	return unique_ptr<TrieNode>(new TrieNodeLeaf(range));
}

