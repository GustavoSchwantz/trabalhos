#include <iostream>
#include <array>
#include "../problem.h"
#include "../moves.h"

struct FO {
    void sucessor_fun (std::array<int, 4>& e) const 
    {
    	e[0] = e[0]*2;
        e[1] = e[1]*2;
        e[2] = e[2]*2;
        e[3] = e[3]*2; 
    }
};

void test ()
{
	FO object;

	Problem<std::array<int, 4>, Moves, FO> problem (std::array<int, 4>{1, 1, 1, 1},
	   std::array<int, 4>{16, 16, 16, 16}, object);

	std::array<int, 4> arr{1, 1, 1, 1};
    
    problem.get_fun_obj ().sucessor_fun (arr);

    std::cout<< arr[0] << " "
    << arr[1] << " "
    << arr[2] << " "
    << arr[3] << std::endl;

    problem.get_fun_obj ().sucessor_fun (arr);

    std::cout<< arr[0] << " "
    << arr[1] << " "
    << arr[2] << " "
    << arr[3] << std::endl;
}

int main(int argc, char const *argv[])
{
	test ();

	return 0;
}