#include "../h/TrieNode.h"

class TrieNodeLeaf: public TrieNode
{
public:
	
	TrieNodeLeaf(RangeInFile& rangeIn): myRange(rangeIn) {}
	
	unique_ptr<TrieNode> add(RangeInFile& range)
	{
		int start=myRange.end;
		
		while(myRange.getCharAfterEnd()==range.getCharAfterEnd() && myRange.getCharAfterEnd()!=0)
		{
			myRange.incrementEnd();
			range.incrementEnd();
		}
		
		unique_ptr<TrieNode> newNode;
		
		if (myRange.getCharAfterEnd()==0 && range.getCharAfterEnd()==0)
		{
			newNode=makeMultiLeaf();
		}
		else
		{
			newNode=makeDefaultBranch();
		}
		
		//	do not increment ranges as the new node will replace this one, not go below it
		
		RangeInFile rangeCopy=myRange;
		
		newNode->add(myRange);
		newNode->add(range);
		
		if (start==rangeCopy.end)
		{
			return newNode;
		}
		else
		{
			return makeMultiChar(RangeInFile(rangeCopy.file, start, rangeCopy.end), move(newNode));
		}
	}
	
	string getString()
	{
		return "leaf";
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

