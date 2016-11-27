
#include "../h/TrieNode.h"

#include "../h/stringHelpers.h"

#include <unordered_map>
using std::unordered_map;

class TrieNodeHashmap: public TrieNode
{
public:
	
	TrieNodeHashmap()=default;
	
	TrieNodeHashmap(char c, unique_ptr<TrieNode> node)
	{
		nodes[c]=move(node);
	}
	
	unique_ptr<TrieNode> add(RangeInFile& range)
	{
		char c=range.getCharAfterEnd();
		
		range.incrementEnd();
		
		auto i=nodes.find(c);
		
		if (i==nodes.end())
		{
			nodes[c]=makeLeaf(range);
		}
		else
		{
			if (auto newNode=nodes[c]->add(range))
			{
				nodes[c]=move(newNode);
			}
		}
		
		return nullptr;
	}
	
	string getString()
	{
		string out="hashmap";
		
		for (auto i=nodes.begin(); i!=nodes.end(); i++)
		{
			//if (i!=nodes.begin())
				//out+="\n";
			out+="\n";
			
			out+=string()+"   "+"["+i->first+"] "+indentString(i->second->getString(), false, "   ");
		}
		
		//out+="\n";
		
		return out;
	}
	
	void get(string query, vector<RangeInFile>& out)
	{
		if (!query.empty())
		{
			auto i=nodes.find(query[0]);
			
			if (i!=nodes.end())
			{
				i->second->get(query.substr(1, string::npos), out);
			}
		}
		else
		{
			for (auto i=nodes.begin(); i!=nodes.end(); i++)
			{
				(*i).second->get("", out);
			}
		}
	}
	
private:
	
	unordered_map<char, unique_ptr<TrieNode>> nodes;
};

unique_ptr<TrieNode> TrieNode::makeHashmap()
{
	return unique_ptr<TrieNode>(new TrieNodeHashmap());
}

unique_ptr<TrieNode> TrieNode::makeHashmap(char c, unique_ptr<TrieNode> node)
{
	return unique_ptr<TrieNode>(new TrieNodeHashmap(c, move(node)));
}

