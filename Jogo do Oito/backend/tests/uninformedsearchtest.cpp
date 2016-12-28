#include <iostream>
#include "../myqueue.h"
#include "../uninformedsearch.h"
#include "../moves.h"

class Example {
public:
	Example ()
	{

	}

	~Example ()
	{

	}

	std::vector<std::pair<Moves, std::string>> sucessor_fun (const std::string& s) const
	{
		std::vector<std::pair<Moves, std::string>> suc;

		if (s == "1000") {

			suc.push_back (std::make_pair (Moves::no_action, "0100"));
			suc.push_back (std::make_pair (Moves::no_action, "0010"));
			suc.push_back (std::make_pair (Moves::no_action, "0001"));
		}

        if (s == "0100") {

			suc.push_back (std::make_pair (Moves::no_action, "1000"));
			suc.push_back (std::make_pair (Moves::no_action, "0010"));
			suc.push_back (std::make_pair (Moves::no_action, "0001"));
		}
		if (s == "0010") {

			suc.push_back (std::make_pair (Moves::no_action, "1000"));
			suc.push_back (std::make_pair (Moves::no_action, "0100"));
			suc.push_back (std::make_pair (Moves::no_action, "0001"));
		}
		if (s == "0001") {

			suc.push_back (std::make_pair (Moves::no_action, "0100"));
			suc.push_back (std::make_pair (Moves::no_action, "0010"));
			suc.push_back (std::make_pair (Moves::no_action, "1000"));
		}

		return suc;
	}
};

void test ()
{
	Example example;
	Problem<std::string, Example> problem ("1000", "0001", example);
    MyQueue<std::string> myqueue;
    UninformedSearch us;

    us.tree_search (problem, myqueue);
}

int main(int argc, char const *argv[])
{
	test ();

	return 0;
}