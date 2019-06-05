#ifndef STATE_H
#define STATE_H
struct state
{
	int eight; 
	int five; 
	int three; 
	// implementation field
	int fn_index;
};
typedef struct state state_t;

void init_state(state_t *ptr_state);
void disp_state(const state_t *ptr_state);
void set_state(state_t *ptr_state, int eight, int five, int three);
void pour_8to5(const state_t *src, state_t *dst);
void pour_8to3(const state_t *src, state_t *dst);
void pour_5to8(const state_t *src, state_t *dst);
void pour_5to3(const state_t *src, state_t *dst);
void pour_3to8(const state_t *src, state_t *dst);
void pour_3to5(const state_t *src, state_t *dst);
int is_safe(const state_t* ptr_state);
int are_same(const state_t *lhs, const state_t *rhs);
#endif

