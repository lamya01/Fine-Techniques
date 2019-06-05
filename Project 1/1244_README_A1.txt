
1. Allocation policy : FIRST FIT

2. I have stored the book keeping details of a memory chunk right before that memory chunk within the character array of size n.

The book comprises of a char to signify the allocation status i.e '+' for allocated and -' for unallocated memory chunk..followed by an integer which stores the size of that memory chunk.

I have allocated sizeof(int) + sizeof(char) bytes = 5bytes approx. for each book.

Management of book keeping:
- mymalloc : traverses the character array, checks the size of the unallocated chunks .. if > or = then change allocation status to '+'. If memory size is greater than needed then insert another book to keep track of the unallocated part (available_size - needed_size) by first shifting all the contents from that position to the right (function called shiftRight) by 5 bytes(book keeping size) to make space for the new book. If no memory chunk free in between then update the last book and add another book in the end of the array.

- myfree : frees the memory chunk specified by changing the allocation status to '-'. If the memory chunk adjacent to it is also unallocated then joins both and deletes book of the second free memory chunk and shifts all the data in the array to the left by 5 bytes i.e bookkeeping size (function called shiftLeft). If memory chunk to be freed has un allocated memory on both sides then it combines both with it and deletes the 2 books. (Function called joinFreeBlocks)

3. Extra functions - static void shiftLeft(int start_indx)
			  - static void shiftRight(int start_indx)
			  - static void joinFreeBlocks()

4. Compilation instructions : 
    
	step1: gcc -Wall 1244_a1.c -c
	step2: gcc -Wall client.c 1244_a1.o -o output.out
	step3: ./output.out


	



