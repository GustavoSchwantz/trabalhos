/* 
 * Node class
 * @author: Gustavo Schwantz Oliveira
 */

template<typename State, typename Action>
class Node {
public:
    Node (const Action& a, const State& s, Node* const f)
	    :action{a}, state{s}, father{f}
	{
		
	}

	~Node ()
	{

	}

	const Action& get_action ()
    {
    	return action;
    }

	const State& get_state ()
	{
		return state;
	}
    
    Node* const get_father ()
    {
    	return father;
    }
    
private:
	const Action action;
    const State state;
    Node* const father;
};