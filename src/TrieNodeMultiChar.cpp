
#include "../h/TrieNode.h"

#include <unordered_map>
using std::unordered_map;

class TrieNodeMultiChar: public TrieNode
{
public:
	
	TrieNodeMultiChar(vector<char> charsIn, unique_ptr<TrieNode> nodeIn)
	{
		chars=charsIn;
		node=move(nodeIn);
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
					lastNode=move(node);
				}
				else
				{
					vector<char> lastNodeChars(chars.begin()+i+1, chars.end());
					lastNode=makeMultiChar(lastNodeChars, move(node));
				}
				
				auto hashMapNode=makeHashmap(chars[i], move(lastNode));
				hashMapNode->add(range);
				
				unique_ptr<TrieNode> nextNode;
				
				if (i==0)
				{
					nextNode=move(hashMapNode);
				}
				else
				{
					vector<char> nextNodeChars(chars.begin(), chars.begin()+i);
					nextNode=makeMultiChar(nextNodeChars, move(hashMapNode));
				}
				
				return nextNode;
			}
			
			range.incrementEnd();
			i++;
		}
		
		if (auto newNode=node->add(range))
		{
			node=move(newNode);
		}
		
		return nullptr;
	}
	
	virtual void get(string query, vector<RangeInFile>& out)
	{
		if (chars.size()>query.size())
		{
			node->get("", out);
		}
		else
		{
			for (int i=0; i<int(chars.size()); i++)
			{
				if (chars[i]!=query[i])
				{
					return;
				}
			}
			
			node->get(query.substr(chars.size(), string::npos), out);
		}
	}
	
private:
	
	vector<char> chars;
	unique_ptr<TrieNode> node;
};

unique_ptr<TrieNode> TrieNode::makeMultiChar(vector<char> charsIn, unique_ptr<TrieNode> nodeIn)
{
	return unique_ptr<TrieNode>(new TrieNodeMultiChar(charsIn, move(nodeIn)));
}


