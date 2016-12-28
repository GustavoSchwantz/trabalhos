#include "uninformedsearch.h"

template<typename Fringe>
void UninformedSearch::tree_search (const Problem& p, Fringe f)
{
	Node* node{new Node (p.initial_state (), nullptr)};

	while (node->state() != p.final_state ()) {
		f.insert_all_on_end (expand (node, p));
		node = f.remove_first ();
	}
}

std::vector<Node*> expand (Node* const n, const Problem& p)
{
	std::vector<Node*> sucessors;

    for (auto p : p.get_fun_obj().sucessor_fun (n->state ())) {
    	Node* s{new Node (p->first, p->second, n)}
    	sucessors.push_back (s);
    }

    return sucessors;
}