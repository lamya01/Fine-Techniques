#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "a2.h"

typedef struct Node
{
    int data;
    struct Node* next;
}node;

// allocates space to a node
node* createNode()
{
    node* temp;
    temp = malloc(sizeof(node));
    temp->next = NULL;
    return temp;
}

// creates a list of size n and returns the head that points to this list
node* createList(int n)
{
    node *head = createNode();
    node *temp = head;
    node *temp1 = NULL;
    for(int i = 0; i < n - 1; ++i)
    {
        temp1 = createNode();
        temp->next = temp1;
        temp = temp1;
    }
    return head;
}

// displays the comparisions according to expected format to stdout 
void display(node *slot_ll, node* prev_ll, node* temp_ll)
{
    node* temp;
    temp = slot_ll;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("x ");
    temp = prev_ll;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("= ");
    temp = temp_ll;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

}


void sec_big(int *numbers, int length)
{
    // calculating total slots i.e indices for the adjacency list
    int tot_slots = ceil(log(length)/log(2)) + 1;
    
    // allocating space for the adjacency list
    node **al = malloc(sizeof(node*) * tot_slots);

    // initialising the adjacency list 
    for(int i = 0; i < tot_slots; ++i)
    {
        al[i] = NULL;
    }

    // slot is the index of adjacency list
    int slot = 0;
    // previous linked list
    node *prev_ll = NULL;

    for(int i = 0; i < length; ++i)
    {
        prev_ll = createNode();
        prev_ll->data = numbers[i];
        
        while(al[slot] != NULL && slot <= tot_slots)
        {
            // have a function createList that makes a temporary linked list of desired size(i.e slot no. + 2) and 
            // populates by comparing prev_ll with current slots list
            // then checks if next slot is empty 
            // no then repeat 
            // yes insert list in that slot

            
            node *temp_ll = createList(slot + 2);
            node *temp, *temp1;

            // compare prev_ll and slots ll
            // check this part again
            if(prev_ll->data > al[slot]->data)
            {
                temp_ll->data = prev_ll->data;
                temp_ll->next->data = al[slot]->data;
                temp = prev_ll->next;
                temp1 = temp_ll->next->next;
                // copy rest of prev_ll to temp_ll               
            }
            else
            {
                temp_ll->data = al[slot]->data;
                temp_ll->next->data = prev_ll->data;
                temp = al[slot]->next;
                temp1 = temp_ll->next->next;
                // copy rest of al[slot]_ll to temp_ll                   
            }
            // copies rest of prev_ll/al[slot]_ll to temp_ll     
            while(temp != NULL)
            {
                temp1->data = temp->data;
                temp1 = temp1->next;
                temp = temp->next;
            } 
            // temp_ll is populated

                
            // display comparisions
            display(al[slot], prev_ll, temp_ll);

            // free slots list
            free(al[slot]);
            al[slot] = NULL;
            // free previous linked list
            free(prev_ll);

            // saving temp_ll by copying to prev_ll
            prev_ll = temp_ll;

            ++slot;
        }

        // if slot is empty add previous list to it
        if(al[slot] == NULL)
        {
            al[slot] = prev_ll;
        }

        // re initialise slot to 0 
        slot = 0;

        // go to next element and repeat the process
    }
    printf("\n");

    // searching and printing the second largest number
    node* temp = al[tot_slots - 1];
    // let 2nd element in last slots list be max (say)
    int max = temp->next->data;
    temp = temp->next->next;
    while(temp != NULL)
    {
        if(temp->data > max)
        {
            max = temp->data;
        }
        temp = temp->next;
    }
    printf("%d", max);
}
