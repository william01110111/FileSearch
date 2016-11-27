
#include "../h/TrieNode.h"

#include "../h/stringHelpers.h"

#include <unordered_map>
using std::unordered_map;

class TrieNodeMultiChar: public TrieNode
{
public:
	
	TrieNodeMultiChar(RangeInFile rangeIn, unique_ptr<TrieNode> nodeIn): myRange(rangeIn)
	{
		//chars=charsIn;
		node=move(nodeIn);
	}
	
	virtual unique_ptr<TrieNode> add(RangeInFile& range)
	{
		for (int i=myRange.start; i<myRange.end;)
		{
			char c=range.getCharAfterEnd();
			
			if (c!=myRange.file->get(i))
			{
				unique_ptr<TrieNode> lastNode;
				
				if (i==myRange.end-1)
				{
					lastNode=move(node);
				}
				else
				{
					//vector<char> lastNodeChars(chars.begin()+i+1, chars.end());
					lastNode=makeMultiChar(RangeInFile(myRange.file, i+1, myRange.end, myRange.lineNumber), move(node));
				}
				
				auto hashMapNode=makeHashmap(myRange.file->get(i), move(lastNode));
				hashMapNode->add(range);
				
				unique_ptr<TrieNode> nextNode;
				
				if (i==myRange.start)
				{
					nextNode=move(hashMapNode);
				}
				else
				{
					//vector<char> nextNodeChars(chars.begin(), chars.begin()+i);
					nextNode=makeMultiChar(RangeInFile(myRange.file, myRange.start, i, myRange.lineNumber), move(hashMapNode));
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
	
	virtual string getString()
	{
		string out="multi-char\n   ";
		
		for (int i=myRange.start; i<myRange.end; i++)
		{
			out+=myRange.file->get(i);
		}
		
		out+=" "+indentString(node->getString(), false, "   ");
		
		return out;
	}
	
	virtual void get(string query, vector<RangeInFile>& out)
	{
		if (myRange.getLength()>query.size())
		{
			node->get("", out);
		}
		else
		{
			for (int i=myRange.start; i<myRange.end; i++)
			{
				if (myRange.file->get(i)!=query[i-myRange.start])
				{
					return;
				}
			}
			
			node->get(query.substr(myRange.getLength(), string::npos), out);
		}
	}
	
private:
	
	//vector<char> chars;
	RangeInFile myRange;
	unique_ptr<TrieNode> node;
};

unique_ptr<TrieNode> TrieNode::makeMultiChar(RangeInFile range, unique_ptr<TrieNode> nodeIn)
{
	return unique_ptr<TrieNode>(new TrieNodeMultiChar(range, move(nodeIn)));
}


