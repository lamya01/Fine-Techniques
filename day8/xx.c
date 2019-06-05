#include <stdio.h>
#include <stdlib.h>

typedef struct state
{
    int eight; 
    int five; 
    int three;
    int fn_index;
}state_t;

typedef struct node
{
    state_t st;
    struct node *next;
    struct node *prev;
}node_t;


typedef struct list
{
    node_t* head;
    node_t* tail;
}list_t;

/*
void init_state(state_t *ptr_state)
{
	ptr_state->eight = 8;
	ptr_state->five = 0;
	ptr_state->three = 0;
	ptr_state->fn_index = 0;
}
*/
 
void disp_state(const state_t *ptr_state)
{
	printf("%d %d %d\n", ptr_state->eight, ptr_state->five, ptr_state->three);
}

void pour_8to5(const state_t *src, state_t *dst)
{
	//if(src->eight){
		if((src->eight + src->five) <= 5)
		{
			dst->eight = 0;
			dst->five = src->eight + src->five;
		}
		else
		{
			dst->eight = src->eight - (5 - src->five);
			dst->five = 5;
		}
		dst->three = src->three;
		dst->fn_index = 0;		
	//}
}
void pour_8to3(const state_t *src, state_t *dst)
{
	//if(src->eight){
		if((src->eight + src->three) <= 3)
		{
			dst->eight = 0;
			dst->three = src->eight + dst->three;
		}
		else
		{
			dst->eight = src->eight - (3 - src->three);
			dst->three = 3;
		}
		dst->five = src->five;
		dst->fn_index = 0;
	//}
}
void pour_5to8(const state_t *src, state_t *dst)
{
	//if(src->five){
		dst->three = src->three;
		dst->eight = src->eight + src->five;
		dst->five = 0;
		dst->fn_index = 0;
	//}

}
void pour_5to3(const state_t *src, state_t *dst)
{
	//if(src->five)
	// {
		if((src->five + src->three) <=3)
		{
			dst->five = 0;
			dst->three = src->three + src->five;
		}
		else
		{
			dst->five = src->five - (3 - src->three);
			dst->three = 3;
		}
		dst->eight = src->eight;
		dst->fn_index = 0;
		
	// }
}
void pour_3to8(const state_t *src, state_t *dst)
{
	//if(src->three){
		dst->three = 0;
		dst->eight = src->eight + src->three;
		dst->five = src->five;
		dst->fn_index = 0;
	//}
}

void pour_3to5(const state_t *src, state_t *dst)
{
	//if(src->three){
		if((src->five + src->three) <= 5)
		{
			dst->five = src->five + src->three;
			dst->three = 0;
		}
		else
		{
			dst->five = 5;
			dst->three = src->three - (5 - src->five);
		}
		dst->eight = src->eight;
		dst->fn_index = 0;		
	//}
}

// done 
void set_state(state_t *ptr_state, int e, int f, int t)
{
	ptr_state->eight = e;
	ptr_state->five = f;
	ptr_state->three = t;
    ptr_state->fn_index = 0;
}

// done
int is_safe(const state_t* ptr_state)
{
	/*return ((ptr_state->mis == 3) || (ptr_state->mis == 0) ||
			(ptr_state->mis == ptr_state->can)) &&
			(ptr_state->mis >= 0 && ptr_state->mis <= 3) &&
			(ptr_state->can >= 0 && ptr_state->can <= 3); */

	return ((ptr_state->eight >= 0 && ptr_state->eight <= 8) && (ptr_state->five >= 0 && ptr_state->five <= 5) &&
	(ptr_state->three >= 0 && ptr_state->three <= 3) && (ptr_state->eight + ptr_state->five + ptr_state->three == 8));

}

// done
int are_same(const state_t *a, const state_t *b)
{
	// return lhs->mis == rhs->mis && lhs->can == rhs->can && lhs->pos == rhs->pos;
	return a->eight == b->eight && a->five == b->five && a->three == b->three;
}


void init_list(list_t *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

//void add_at_end(list_t *ptr_list, int key)
void add_at_end(list_t *ptr_list, const state_t* ptr_state)

{
	node_t* temp = (node_t*) malloc(sizeof(node_t));
	//temp->key = key;
	temp->st = *ptr_state; 
	temp->next = temp->prev = NULL;

	if(ptr_list->tail == NULL)
	{
		temp->prev = temp->next = NULL;
		ptr_list->head = ptr_list->tail = temp;
	}
	else
	{
		temp->prev = ptr_list->tail;
		temp->next = NULL;
		ptr_list->tail = ptr_list->tail->next = temp;
	}
}
void remove_at_end(list_t *ptr_list)
{
	if(ptr_list->tail == NULL)
	{
		printf("empty list\n");
	}
	else  
	{
		node_t* temp = ptr_list->tail;
		//printf("removing %d\n", temp->key);
		//disp_state(&temp->st);
		ptr_list->tail = ptr_list->tail->prev;	
		if(ptr_list->tail == NULL)
		{
			ptr_list->head = NULL;
		}
		else
		{
			ptr_list->tail->next = NULL;
		}
		free(temp);		
	}
}

void disp_list(const list_t *ptr_list)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{
		//printf("%d ", temp->key);
		disp_state(&temp->st);
		temp = temp->next;
	}
	printf("\n");
}

int is_repeated(const list_t* ptr_list, const state_t* ptr_state)
{
	node_t* temp = ptr_list->head;
	int found = 0;
	while(temp && !found)
	{
		found  = are_same(&(temp->st), ptr_state);
		temp = temp->next;
	}
	return found;
}


int main()
{

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
    int no_of_solns;
	no_of_solns = 0;
	int n = 6;

	// array of pointers to functions
	void (*move[])(const state_t *src, state_t *dst) = 
	{	
		pour_8to5, pour_8to3, pour_5to8, pour_5to3, pour_3to8, pour_3to5
	};

	
    // freopen("output.txt", "w", stdout);
while(l.head)
//while(no_of_solns != 16)
{
    //int counter = 0;
	//while(!soln)
	//{
		index = l.tail->st.fn_index;
		move[index](&l.tail->st, &temp);
		if(is_safe(&temp) && ! is_repeated(&l, &temp))
		{
			// printf("adding state %d\n", ++counter);
			add_at_end(&l, &temp);
            

			soln = are_same(&temp, &goal_state);
            // state_t temp; // re initialize temp
            // set_state(&temp, 0, 0, 0);
			if(soln) {
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
				//l.tail->st.fn_index = 0;
				// printf("back tracking\n");
				remove_at_end(&l);
			}
		}
	//}
    //if(no_of_solns > 1)
    //{
      //  disp_state(&start_state);
    //}
    // printf("%d \n", no_of_solns);
	// init_list(&l);
}
printf("%d \n", no_of_solns);

}
