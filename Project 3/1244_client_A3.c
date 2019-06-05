#include <stdio.h>
#include <stdlib.h>
#include "1244_header_A3.h"

int main()
{
    // init start state
    // init final state
    // while not solution do
    // find the next transition(new state)
    // if the new state is safe and not repeated then
    // add to the soln
    // if new state is same as final state
    // solution is found
    // else
    // try the next transition
    // while no more transition
    // backtrack
  
    // open file to output into
	freopen("1244_output_A3.txt", "w", stdout);
	state_t start_state;
	set_state(&start_state, 8, 0, 0);
	state_t goal_state;
	set_state(&goal_state, 4, 4, 0);
	list_t l;
	init_list(&l);
	state_t temp;
	int soln = 0;
	add_at_end(&l, &start_state);
	int index;
    int no_of_solns;
	no_of_solns = 0;


	// array of pointers to functions
	void (*move[])(const state_t *src, state_t *dst) = 
	{	
		pour_8to5, pour_8to3, pour_5to8, pour_5to3, pour_3to8, pour_3to5
	};

    // while the list is not empty
    while(l.head)
    {
		index = l.tail->st.fn_index; // getting index of array of pointers to functions
		move[index](&l.tail->st, &temp); // calling funtion at index position in move
		
		if(!is_repeated(&l, &temp))
		{
			add_at_end(&l, &temp); // adds to end of list of nodes of states
			soln = are_same(&temp, &goal_state); // if same then no soln i.e 0
			if(soln) 
            {
			    ++no_of_solns;
			    disp_list(&l);
			    soln = 0;
			}
		}
		else
		{
			// list empty is checked
			while(l.tail != NULL && ++l.tail->st.fn_index == 6)
			{
				remove_at_end(&l);
			}
	    }
    }   
    printf("%d \n", no_of_solns);
}

