t/* 
 * Problem class 
 * @author: Gustavo Schwantz Oliveira
 */

template<typename State, typename Action, typename FunObj>
class Problem {
public:
	Problem (const State& i, const State& f, const FunObj& fo)
	    :initial{i}, final{f}, fun_obj{fo}
	{

	}  

	~Problem ()
	{

	} 

	const State& initial_state ()
	{
		return initial;
	}

	const State& final_state ()
	{
		return final;
	}
    
    const FunObj& get_fun_obj ()
    {
    	return fun_obj;
    }

private:
	const State initial, final;
	const FunObj fun_obj;
};