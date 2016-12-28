#include <iostream>
#include "myqueue.h"

int main(int argc, char const *argv[])
{
	MyQueue<int> mq;

    std::cout << ((mq.empty ()) ? "Queue empty!" :
    	"Queue not empty!") << std::endl;

    mq.insert_on_end (10);

    std::cout << ((mq.empty ()) ? "Queue empty!" :
    	"Queue not empty!") << std::endl;

    mq.remove_first ();

    std::cout << ((mq.empty ()) ? "Queue empty!" :
    	"Queue not empty!") << std::endl;

    mq.insert_on_end (20);
    mq.insert_on_end (30);

    std::cout << ((mq.empty ()) ? "Queue empty!" :
    	"Queue not empty!") << std::endl;

    std::cout << mq.first () << std::endl;

    mq.insert_all_on_end ({40, 50, 60});

    for (int i = 0; i != 4; ++i) {
    	std::cout << mq.remove_first () << std::endl;
    }

     std::cout << ((mq.empty ()) ? "Queue empty!" :
    	"Queue not empty!") << std::endl;


	return 0;
}