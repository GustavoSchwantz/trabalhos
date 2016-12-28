#include <vector>

template<typename T>
class MyQueue : private std::vector<T> {
public:
	bool empty ()
	{
		return (this->size ()) ? false : true;
	}

	T first ()
	{
        return this->back ();
	}

	T remove_first ()
	{
		T element = this->back ();
        this->pop_back ();
        return element;
	}

	void insert_on_end (T element)
    {
	    this->insert (this->begin (), element);
    }

    void insert_all_on_end (std::vector<T> elements)
    {
	    this->insert (this->begin (), elements.begin (), elements.end ());
    }
};