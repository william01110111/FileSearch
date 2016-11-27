
#include "../h/TrieNode.h"

#include <unordered_map>
using std::unordered_map;

class TrieNodeMultiChar: public TrieNode
{
public:
	
	TrieNodeMultiChar(vector<char> charsIn, unique_ptr<TrieNode> nodeIn)
	{
		chars=charsIn;
		node.swap(nodeIn);
	}
	
	virtual unique_ptr<TrieNode> add(RangeInFile& range)
	{
		for (int i=0; i<int(chars.size());)
		{
			char c=range.getCharAfterEnd();
			
			if (c!=chars[i])
			{
				unique_ptr<TrieNode> lastNode;
				
				if (i>=int(chars.size())-1)
				{
					lastNode.swap(node);
				}
				else
				{
					vector<chars> lastNodeChars(chars.begin()+i+1, chars.end());
					lastNode=makeMultiChar(lastNodeChars, node);
				}
				
				auto hashMapNode=makeHashmap(chars[i], lastNode);
				hashMapNode.add(range);
				
				unique_ptr<TrieNode> nextNode;
				
				if (i==0)
				{
					nextNode=hashMapNode;
				}
				else
				{
					vector<chars> nextNodeChars(chars.begin(), chars.begin()+i);
					nextNode=makeMultiChar(nextNodeChars, hashMapNode);
				}
				
				return nextNode;
			}
			
			range.incrementEnd();
			i++;
		}
		
		if (auto newNode=node.add(range))
		{
			node.swap(newNode);
		}
		
		return nullptr;
	}
	
	virtual void get(string query, vector<RangeInFile>& out)
	{
		if (chars.size()>query.size())
		{
			node.add("", out);
		}
		else
		{
			for (int i=0; i<chars.size(); i++)
			{
				if (chars[i]!=query[i])
				{
					return;
				}
			}
			
			node.add(query.substr(chars.size(), string::npos));
		}
	}
	
private:
	
	vector<char> chars;
	unique_ptr<TrieNode> node;
};

unique_ptr<TrieNode> TrieNode::makeMultiChar(vector<char> charsIn, unique_ptr<TrieNode> nodeIn)
{
	return unique_ptr<TrieNode>(new TrieNodeMultiChar(charsIn, nodeIn));
}


