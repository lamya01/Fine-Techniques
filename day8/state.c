#include <stdio.h>
#include "state.h"


// done 
void set_state(state_t *ptr_state, int e, int f, int t)
{
	ptr_state->eight = e;
	ptr_state->five = f;
	ptr_state->three = t;
	ptr_state->fn_index = 0;
}

// done 
void init_state(state_t *ptr_state)
{
	ptr_state->eight = 8;
	ptr_state->five = 0;
	ptr_state->three = 0;
	ptr_state->fn_index = 0;
}

// done 
void disp_state(const state_t *ptr_state)
{
	printf("8 : %d 5 : %d 3 : %d\n", ptr_state->eight, ptr_state->five, ptr_state->three);
}

void pour_8to5(const state_t *src, state_t *dst)
{
	if(src->eight)
	{
		if((src->eight + src->five) <= 5)
		{
			dst->eight = 0;
			dst->three = dst->eight + src->three;
		}
		else
		{
			dst->eight = src->eight - (5 - src->five);
			dst->five = 5;
		}
		dst->three = src->three;
		dst->fn_index = 0;		
	}
}
void pour_8to3(const state_t *src, state_t *dst)
{
	if(src->eight)
	{
		if((src->eight + src->three) <= 3)
		{
			dst->three = src->eight + dst->three;
			dst->eight = 0;
		}
		else
		{
			dst->eight = src->eight - (3 - src->three);
			dst->three = 3;
		}
		dst->five = src->five;
		dst->fn_index = 0;
	}
}
void pour_5to8(const state_t *src, state_t *dst)
{
	if(src->five)
	{
		dst->three = src->three;
		dst->eight = src->eight + src->five;
		dst->five = 0;
		dst->fn_index = 0;
	}

}

void pour_5to3(const state_t *src, state_t *dst)
{
	if(src->five)
	{
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
		
	}
}
void pour_3to8(const state_t *src, state_t *dst)
{
	if(src->three)
	{
		dst->three = 0;
		dst->eight = src->eight + src->three;
		dst->five = src->five;
		dst->fn_index = 0;
	}
}

void pour_3to5(const state_t *src, state_t *dst)
{
	if(src->three)
	{
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
	}
}



// done
int is_safe(const state_t* ptr_state)
{
	/*return ((ptr_state->mis == 3) || (ptr_state->mis == 0) ||
			(ptr_state->mis == ptr_state->can)) &&
			(ptr_state->mis >= 0 && ptr_state->mis <= 3) &&
			(ptr_state->can >= 0 && ptr_state->can <= 3); */

	return (ptr_state->eight >= 0 && ptr_state->eight <= 8 && ptr_state->five >= 0 && ptr_state->five <= 5 &&
	ptr_state->three >= 0 && ptr_state->three <= 3 && ptr_state->eight + ptr_state->five + ptr_state->three == 8);

}

// done
int are_same(const state_t *a, const state_t *b)
{
	// return lhs->mis == rhs->mis && lhs->can == rhs->can && lhs->pos == rhs->pos;
	return a->eight == b->eight && a->five == b->five && a->three == b->three;
}






