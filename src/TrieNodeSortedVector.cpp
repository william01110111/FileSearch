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
		
		if (hgh==0)
			return -1;
		
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
		
		if (nodes[low].key==target)
			return low;
		else
			return -1;
	}
	
	/*inline int searchFor(char target)
	{
		for (int i=0; i<int(nodes.size()); i++)
		{
			if (nodes[i].key==target)
			{
				return i;
			}
		}
		
		return -1;
	}*/
	
	inline void place(char key, unique_ptr<TrieNode> val)
	{
		nodes.push_back(KeyVal{key, move(val)});
		
		int i=nodes.size()-1;
		
		while (i>0 && nodes[i-1].key>key)
		{
			std::swap(nodes[i], nodes[i-1]);
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
			auto newNode=nodes[i].val->add(range);
			
			if (newNode)
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
		if (query.empty())
		{
			for (auto i=nodes.begin(); i!=nodes.end(); i++)
			{
				(*i).val->get("", out);
			}
		}
		else
		{
			auto i=searchFor(query[0]);
			
			if (i>=0)
			{
				nodes[i].val->get(query.substr(1, string::npos), out);
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

