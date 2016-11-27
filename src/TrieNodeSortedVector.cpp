#include "../h/TrieNode.h"

#include "../h/stringHelpers.h"

#include <vector>
using std::vector;

#include <algorithm>

class TrieNodeSortedVector: public TrieNode
{
public:
	
	struct KeyVal
	{
		char key;
		unique_ptr<TrieNode> val;
	};
	
	TrieNodeSortedVector()=default;
	
	TrieNodeSortedVector(char c, unique_ptr<TrieNode> node)
	{
		nodes.push_back(KeyVal{c, move(node)});
	}
	
	inline int searchFor(char target)
	{
		int low=0;
		int hgh=nodes.size();
		
		while(hgh-low>1)
		{
			int mid=(hgh+low)/2;
			
			if (nodes[mid].key>target)
			{
				hgh=mid;
			}
			else
			{
				low=mid;
			}
		}
		
		return low;
	}
	
	inline void place(char key, unique_ptr<TrieNode> val)
	{
		nodes.push_back(KeyVal{key, move(val)});
		
		auto i=nodes.end();
		i--;
		
		while (i!=nodes.begin() && i->key>key)
		{
			std::iter_swap(i, i-1);
			i--;
		}
	}
	
	unique_ptr<TrieNode> add(RangeInFile& range)
	{
		char c=range.getCharAfterEnd();
		
		range.incrementEnd();
		
		int i=searchFor(c);
		
		if (i<0)
		{
			place(c, makeLeaf(range));
		}
		else
		{
			if (auto newNode=nodes[i].val->add(range))
			{
				nodes[i].val=move(newNode);
			}
		}
		
		return nullptr;
	}
	
	string getString()
	{
		string out="sorted vector";
		
		for (auto i=nodes.begin(); i!=nodes.end(); i++)
		{
			//if (i!=nodes.begin())
				//out+="\n";
			out+="\n";
			
			out+=string()+"   "+"["+i->key+"] "+indentString(i->val->getString(), false, "   ");
		}
		
		//out+="\n";
		
		return out;
	}
	
	void get(string query, vector<RangeInFile>& out)
	{
		if (!query.empty())
		{
			auto i=searchFor(query[0]);
			
			if (!(i<0))
			{
				nodes[i].val->get(query.substr(1, string::npos), out);
			}
		}
		else
		{
			for (auto i=nodes.begin(); i!=nodes.end(); i++)
			{
				(*i).val->get("", out);
			}
		}
	}
	
private:
	
	vector<KeyVal> nodes;
};

unique_ptr<TrieNode> TrieNode::makeSortedVector()
{
	return unique_ptr<TrieNode>(new TrieNodeSortedVector());
}

unique_ptr<TrieNode> TrieNode::makeSortedVector(char c, unique_ptr<TrieNode> node)
{
	return unique_ptr<TrieNode>(new TrieNodeSortedVector(c, move(node)));
}

