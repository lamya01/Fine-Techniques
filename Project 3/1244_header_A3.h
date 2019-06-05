// structure to store the state of the jugs
typedef struct state
{
	int eight; // volume in 8l jug
	int five; // volume in 5l jug
	int three; // volume in 3l jug
	int fn_index; // implementation field
}state_t;

// node that holds the current state and pointers to previous and next states
typedef struct node
{
	state_t st;
	struct node *next;
	struct node *prev;
}node_t;

// structure to store list info i.e header and tail
typedef struct list
{
	node_t* head;
	node_t* tail;
}list_t;

// displays state 
void disp_state(const state_t *ptr_state);

// sets state to given values 
void set_state(state_t *ptr_state, int eight, int five, int three);

// 6 transition functions
void pour_8to5(const state_t *src, state_t *dst);
void pour_8to3(const state_t *src, state_t *dst);
void pour_5to8(const state_t *src, state_t *dst);
void pour_5to3(const state_t *src, state_t *dst);
void pour_3to8(const state_t *src, state_t *dst);
void pour_3to5(const state_t *src, state_t *dst);

// checks if 2 states are the same
int are_same(const state_t *lhs, const state_t *rhs);

// initialises list header and tail to null
void init_list(list_t *ptr_list);

// adds state to end of list 
void add_at_end(list_t *ptr_list, const state_t* ptr_state);

// removes state from list
void remove_at_end(list_t *ptr_list);

// displays list
void disp_list(const list_t *ptr_list);

// checks if state is repeated in list
int is_repeated(const list_t* ptr_list, const state_t* ptr_state);
