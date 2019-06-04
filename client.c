#include <stdio.h>
#include <stdlib.h>
#include "a.h"

int main()
{
	 allocate(1000);
	 display_mem_map();
	 printf("\n");

	 char* x = (char*)mymalloc(100 * sizeof(char));
	 display_mem_map();
	 printf("\n");

	 char* q = (char*)mymalloc(200 * sizeof(char));
	 display_mem_map();
	 printf("\n");

	 char* r = (char*)mymalloc(150 * sizeof(char));
	 display_mem_map();
	 printf("\n");

	 myfree(q);
	 display_mem_map();
	 printf("\n");

	 print_book();
	 printf("\n"); 
}
	/*allocate(50);
	for(int i = 0; i < 50; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n"); 


	char *q1 = mymalloc(2 * sizeof(char));
	// q1[0] = 0x1;
	// q1[1] = 0x1;
	for(int i = 0; i < 20; ++i)
	{
		printf("%d ", q1[i]);
	}
	printf("\n"); 

	char *q2 = mymalloc(3 * sizeof(char));
	// q2[0] = 0x2;
	// q2[1] = 0x2;
	for(int i = 0; i < 20; ++i)
	{
		printf("%d ", q2[i]);
	}
	printf("\n");

	char *q3 = mymalloc(5 * sizeof(char));

	for(int i = 0; i < 50; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n");

	for(int i = 0; i < 80; ++i)
	{
		printf("%d ", p[i]);
	} 
	//printf("\n\n\n");

	myfree(q2);
	
	for(int i = 0; i < 80; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n\n\n");

	char *q4 = mymalloc(5 * sizeof(char));
	// myfree(q3);
	for(int i = 0; i < 50; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
	

	display_mem_map(); */


