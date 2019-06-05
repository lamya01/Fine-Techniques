How to COMPLILE and EXECUTE my code:
 	step1:  gcc -Wall 1244_impl_A3.c -c
	step2:  gcc -Wall 1244_impl_A3.o 1244_client_A3.c -o client.out
	step3:  ./client.out
To see the output file execute :
	step4: cat 1244_output_A3.txt 

DATA STRUCTURES used to implement the state space search:
	-linked lists (of nodes)
	-array (of pointers to functions)

WORKING:
A valid state is generated and then checked if it isn't already repeated. If not then add that state to list of states. If yes then discard that state and generate the next state. A pointer to array of function pointers is created and each time a state is not valid next function is called via its function pointer. Also, each state is checked if its the goal state i.e 4 4 0. If yes it has found a solution and displays. If no generates next new state.
A total of 16 states are found for this problem.
