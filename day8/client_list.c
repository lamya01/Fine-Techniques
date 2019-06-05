#include <stdio.h>
#include "list.h"
#include "state.h"

int main()
{
	int no_of_solns;
	no_of_solns = 0;
#if 0
	list_t l;
	init_list(&l);
	add_at_end(&l, 11);
	disp_list(&l);
	add_at_end(&l, 22);
	disp_list(&l);
	add_at_end(&l, 33);
	disp_list(&l);
	remove_at_end(&l);
	remove_at_end(&l);
	remove_at_end(&l);
#endif
#if 0
	list_t l;
	init_list(&l);
	state_t temp;
	set_state(&temp, 3, 3, 0); 
	add_at_end(&l, &temp);
	set_state(&temp, 2, 2, 0); 
	add_at_end(&l, &temp);
	set_state(&temp, 1, 1, 0); 
	add_at_end(&l, &temp);
	disp_list(&l);

	remove_at_end(&l);
	remove_at_end(&l);
	remove_at_end(&l);
#endif

// init start state
// init final state
// while not solution do
//	find the next transition(new state)
//	if the new state is safe and not repeated then
//		add to the soln
//		if new state is same as final state
//			solution is found
//  else
//		try the next transition
//		while no more transition
//			backtrack

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

	int n = 6;

	// array of pointers to functions
	void (*move[])(const state_t *src, state_t *dst) = 
	{	
		pour_8to5, pour_8to3, pour_5to8, pour_5to3, pour_3to8, pour_3to5
	};

while(no_of_solns != 16)
{
	while(! soln)
	{
		index = l.tail->st.fn_index;
		move[index](&l.tail->st , &temp);
		if(is_safe(&temp) && ! is_repeated(&l, &temp))
		{
			printf("adding\n");
			add_at_end(&l, &temp);

			soln = are_same(&temp, &goal_state);
			if(soln) ++ no_of_solns;
		}
		else
		{
			// list empty not checked
			while(++l.tail->st.fn_index == 6)
			{
				l.tail->st.fn_index = 0;
				printf("back tracking\n");
				remove_at_end(&l);
			}			
		}
	}
	disp_list(&l);
	init_list(&l);
	soln = 0;
	
	}
}


#if 0
	//while(! soln)
	{
		index = l.tail->st.fn_index;
		move[index](&l.tail->st , &temp);
		add_at_end(&l, &temp);
		//disp_list(&l);
		++l.tail->st.fn_index;
		index = l.tail->st.fn_index;
		move[index](&l.tail->st , &temp);
		add_at_end(&l, &temp);
		disp_list(&l);

		
	}
#endif

/*
for (j = 1; j <= n; j++) 
{
    for (i = 0; i < n-1; i++) 
	{
        temp = num[i];
        num[i] = num[i+1];
        num[i+1] = temp;
        print(num, n);
	}
}
*/