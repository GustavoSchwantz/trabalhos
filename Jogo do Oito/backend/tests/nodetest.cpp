#include <iostream>
#include <array>
#include "../moves.h"
#include "../node.h"

void test ()
{
    auto *node
        {new Node<std::array<int, 4>, Moves>
            (Moves::no_action, std::array<int, 4>{1, 1, 1, 1}, nullptr)};

    delete node;        
}

int main(int argc, char const *argv[])
{
	test ();

	return 0;
}