#include <array>

class Node {
public:
	Node (const std::array<int, 9>& i, Node *p)
	{
		estado = i;
        pai = p;
	}

	~Node ()
	{

	}

	std::array<int, 9> get_estado ()
	{
		return estado;
	}
    
    Node* get_pai ()
    {
    	return pai;
    }
    
private:
    std::array<int, 9> estado;
    Node *pai;
};