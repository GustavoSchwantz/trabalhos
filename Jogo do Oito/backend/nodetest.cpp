#include <iostream>
#include <array>
#include "moves.h"
#include "node.h"

void test ()
{
	std::array<int, 9> arr0 = {0, 1,
	    2, 3, 4, 5, 6, 7, 8};

	std::array<int, 9> arr1 = {8, 1,
	    2, 3, 4, 5, 6, 7, 0};    

	Node<std::array<int, 9>, Moves> node0 (arr1, nullptr);
	Node<std::array<int, 9>, Moves> node1 (arr0, &node0);
    Node<std::array<int, 9>, Moves> node2 (arr0, &node1);
    
    auto n = &node2;
    
    std::cout << n->get_state ()[0] << " " 
    << n->get_state ()[1] << " " 
    << n->get_state ()[2] << " " 
    << n->get_state ()[3] << " " 
    << n->get_state ()[4] << " "
    << n->get_state ()[5] << " " 
    << n->get_state ()[6] << " "
    << n->get_state ()[7] << " " 
    << n->get_state ()[8] << std::endl;

    n = n->get_father ();

    std::cout << n->get_state ()[0] << " " 
    << n->get_state ()[1] << " " 
    << n->get_state ()[2] << " " 
    << n->get_state ()[3] << " " 
    << n->get_state ()[4] << " "
    << n->get_state ()[5] << " " 
    << n->get_state ()[6] << " "
    << n->get_state ()[7] << " " 
    << n->get_state ()[8] << std::endl;

    n = n->get_father ();

    std::cout << n->get_state ()[0] << " " 
    << n->get_state ()[1] << " " 
    << n->get_state ()[2] << " " 
    << n->get_state ()[3] << " " 
    << n->get_state ()[4] << " "
    << n->get_state ()[5] << " " 
    << n->get_state ()[6] << " "
    << n->get_state ()[7] << " " 
    << n->get_state ()[8] << std::endl;
}

int main(int argc, char const *argv[])
{
	test ();

	return 0;
}