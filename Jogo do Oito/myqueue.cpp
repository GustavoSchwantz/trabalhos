#include "myqueue.h"

template<typename T>
T MyQueue<T>::remove_first ()
{
	T element = this->back ();
    this->pop_back ();
    return element;
}