#include <stdio.h>
#include <stdlib.h>
#include "a.h"

char *p;
int N;

void display_mem_map() 
{
    int count;
    count = 0;
    int i;
    i = 0;
    int curr_size;
    int start_indx;
    int end_indx;
    int book_indx;
    int book_size = sizeof(int) + sizeof(char);
    char *all_status;
    
    while(count < N)
    {
        curr_size = *((int*)(p + i + 1));
        start_indx = (i + sizeof(int) + 1); 
        book_indx = i; 
        end_indx = (i + sizeof(int) + curr_size); 

        if(p[i] == '+') 
        {
            // all_status = 1;
            all_status = "allocated"; 
        }
        else
        {
            // all_status = 0;
            all_status = "free";
        }

        printf("%d %d %s\n", book_indx, book_size, "book");
        printf("%d %d %s\n", start_indx, curr_size, all_status);
        
        count += (curr_size + book_size);

        if(count < N)
        {
            i = i + sizeof(int) + curr_size + 1; // next header index
        }
    }
}


static void shiftLeft(int start_indx)
{
    int book_size = sizeof(int) + sizeof(char);
    int end_indx = N - 1;
    
    for(int i = start_indx; i <= end_indx; ++i)
    {
        p[i - book_size] = p[i];
    }

}

static void joinFreeBlocks()
{
	int counter; // to count consecutive joins
	counter = 0;
    int count;
    count = 0;
    int i;
    i = 0;
    int flag; // to signify that a join has occured
    flag = 0;
    int nxt_header;
	nxt_header = 0;
	int book_size;
	int size_next;
	size_next = 0;
	book_size = sizeof(int) + sizeof(char);
    int size;
	size = 0;

    while(count < N)
    {
        if(p[i] == '-')
        {
            size = *((int*)(p + i + 1));
            nxt_header = i + sizeof(int) + size + 1;
            if(p[nxt_header] == '-')
            {
                // update prev header 
                size_next = *((int*)(p + nxt_header + 1));
                *((int*)(p + i + 1)) += size_next;  
                p[nxt_header] = 0;
                *((int*)(p + nxt_header + 1)) = 0;
                // shift by header_no_of bytes to the left
                shiftLeft(nxt_header + sizeof(int) + 1);
                flag = 1;
				++counter;
            }
            else
            {
                flag = 0;
            }
              
        }
        if(flag == 0)
        {
            count = count + *((int*)(p + i + 1)) + book_size;
        }
        else 
        {
            if(counter == 2) // can have only 2 consecutive joins 
			{
				*((int*)(p + i + 1)) += 2 * book_size;
				break;
			}                                     
        }
        
        if(count < N && flag == 0)
        {
            i = i + sizeof(int) + *((int*)(p + i + 1)) + 1; // next header index
        }     
    }
}

void myfree(void *p) // free the block pointed to by the parameter
{
    char *p1 = (char*)p;
    *(p1 - (sizeof(int) + sizeof(char))) = '-'; 
    int curr_size = *((int*)(p1 - sizeof(int)));
    for(int i = 0; i < curr_size; ++i)
    {
        p1[i] = 0x0;
    }
    joinFreeBlocks();
}


static void shiftRight(int start_indx)
{
    int end_indx;
    int book_size = sizeof(int) + sizeof(char);
    end_indx = N - 1;
    
    for(int i = end_indx - book_size; i >= start_indx; --i)
    {
        p[i + book_size] = p[i];
    }
}

void allocate(int n) // function to allocate memory for the global array p based on the value of n
{
    // book - 5 bytes 
    // char - allocation status : + for allocated, - for unallocated
    // int - size of block .. int
    p = malloc(n);
    int book_size = sizeof(int) + sizeof(char);

    // initialising first book
    p[0] = '-'; 
    *((int*)(p + 1)) = n - book_size;
	// initialising locations to 0
	for(int i = 5; i < n; ++i)
	{
		p[i] = 0x0;
	}
	
    N = n - book_size;
    
}

void* mymalloc(int size) // function to allocate a block of size "size"... FIRST FIT
{
    int i;
    i = 0;
    int count;
    count = 0;
    int curr_size = 0;
    int book_size = 0;
    book_size = sizeof(int) + sizeof(char);
    char all_status;

    while(count < N)
    {
        curr_size = *((int*)(p + i + 1));
        all_status = *(p + i);
        if(all_status == '-')
        {
            if(curr_size > size)
            {
                // update current block
                *(p + i) = '+';
                *((int*)(p + i + 1)) = size;

                // shift right by  book size to make space for new book 
                // that keeps track of the unallocated memory part
                shiftRight(i + sizeof(int) + curr_size + 1);

                // update next book
                *(p + i + sizeof(int) + size + 1) = '-';
                *((int*)(p + i + sizeof(int) + size + 2)) = curr_size - size;

                // to update last book which keeps track of unallocated memory
                // traverse from current index till last book
                int count1;
                count1 = count;
                int i1;
                i1 = i;
                int curr_size1;
                while(count1 < N - book_size)
                {
                    curr_size1 = *((int*)(p + i1 + 1));
                    count1 = count1 + curr_size1 + book_size;
                    
                    if(count1 < N - book_size)
                    {
                        // calc index of next block
                        i1 = i1 + curr_size1 + sizeof(int) + 1;
                    }
                }
                *((int*)(p + i1 + 1)) -= book_size;
                break;               
            }
            else if(curr_size == size)
            {
                *(p + i) = '+';
            }
			else
			{
				count = count + curr_size + book_size;
            	if(count < N)
            	{
                	// traverse next block
                	i = i + sizeof(int) + curr_size + 1;
            	}	
			}
			  
        }
        else
        {
            count = count + curr_size + book_size;
            if(count < N)
            {
                // traverse next block
                i = i + sizeof(int) + curr_size + 1;
            }
        }
    }
    return (p + i + sizeof(int) + 1);
}

void print_book()
{
    int bking_size;
    bking_size = sizeof(int) + sizeof(char); 
    printf("%d\n%d",bking_size, bking_size);
}

