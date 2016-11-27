
#include "TrieNode.h"

#include <unordered_map>
using std::unordered_map;

class TrieNodeHashmap: TrieNode
{
public:
	
	virtual unique_ptr<TrieNode> add(RangeInFile& range)
	{
		char c=range.file->get(range.endIndex);
		
		range.endIndex++;
		
		auto i=nodes.find(c);
		
		if (i==nodes.end())
		{
			nodes[c]=makeLeaf(range);
		}
		else
		{
			if (auto newNode=nodes[c]->add(range))
			{
				nodes[c].swap(newNode);
			}
		}
		
		return nullptr;
	}
	
	virtual void get(string query, vector<RangeInFile>& out)
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
			for (auto i: nodes)
			{
				i->get("", out);
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

