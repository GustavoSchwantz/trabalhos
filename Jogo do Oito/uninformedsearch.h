/* 
 * UninformedSearch class
 * @author: Gustavo Schwantz Oliveira
 */

#include <memory>
#include "problem.h"
#include "node.h"

class UninformedSearch {
public:
	UninformedSearch()
	{

	}

	~UninformedSearch()
	{

	}
    
    template<typename Fringe>
	void tree_search (const Problem& p, Fringe f);
	std::vector<Node*> expand (Node* const n, const Problem& p);
};