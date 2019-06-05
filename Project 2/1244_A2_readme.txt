How to COMPLILE and EXECUTE my code:
 	step1:  gcc -Wall 1244_A2.c -c
	step2:  gcc -Wall client.c  1244_A2.o -o client.out
	step3:  ./client.out

DATA STRUCTURES used to implement the binary counter:
	-array of pointers to node posters
	-linked list storing the numbers
Basically, I'm using an adjacency list.

e.g. say input is 4 ..then no. of slots or size of that array is 3 and
	1st slot will have a header to linked list of size 1, 2nd slot of array will
	have the header to a linked list of size 2 and so on...
	after the algorithm has done its job, the last slot has a linked list with the 
	winner i.e the largest element as its first element/node and the rest of the nodes 	are the losers to the winner and hence contains the second largest number.

WORKING:
If the length is 4
And numbers are 42 14 35 47

42 is read and the slot 0 is empty so its linked there

Next, 14 is read. Slot 0 is empty so its compared with 42. In slot 1 42-14 linked list is added.

Next, 35 is read and since slot 0 is empty it is added there as a linked list.

Next, 47 is read. Slot 0 is empty so 47 and 35 are compared and 47-35 list is formed and since slot 1 is full, 47-35 is compared with 42-14 and forms 47-42-35 list and added to empty slot 2.

The largest element is 47 and second largest is 42.