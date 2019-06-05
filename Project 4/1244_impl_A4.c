#include "a4.h"
#include <stdio.h>
#include <stdlib.h>



// finds min value in the right sub tree of node with 2 children to be deleted
int minRSTvalue(int root, FILE* fp);
// helper function of display_inorder
void inorder(int root, FILE *fp);
// helper function of display_preorder
void preorder(int root, FILE* fp);
// helper function of delete key
int delete(int root, int key, FILE* fp);

// initialises tree in new file 
FILE* init_tree(tree_t* trptr, const char* file_name)
{
    FILE* fp = fopen(file_name, "r+"); // opening the given file
	if(fp == NULL) // if file not there or empty
	{
		// printf("empty file\n");
		fp = fopen(file_name, "w"); // creates the file
        // initialise header info : -1 means NULL
		trptr->root = -1;
		trptr->free_head = -1;
        // write header to file
		fwrite(trptr, sizeof(tree_t), 1, fp);
		fclose(fp);
		fp = fopen(file_name, "r+"); // open in update mode
	}
	fread(trptr, sizeof(tree_t), 1, fp); // reading the header info if already exits 
	return fp;
}

// inserts a key in the BST 
void insert_key(tree_t *ptr_tree, int key, FILE *fp)
{
    // traverse
    // compare with tree nodes to get insertion location
    // if that roots child offset is -1 then insert the given node there
    // else go to offset position and repeat steps

    int loff, roff; // right and left node offsets
    loff = roff = -1;

    int temp = -1; // stores position of file ptr
    int idx_nn = -1; // index of new node

    node_t temp_node; // stores key to be inserted
    temp_node.key = key;
    temp_node.left_off = temp_node.right_off = -1;

    // empty tree
    if(ptr_tree->root == -1)
    {
        fseek(fp, 0, SEEK_SET); // go to beg of file
        fwrite(ptr_tree, sizeof(tree_t), 1, fp); // write header info
        temp = ftell(fp); // get position of file cursor i.e first node position
        ptr_tree->root = temp; // root points to first postion
        fseek(fp, 0, SEEK_SET); // goto beg
        fwrite(ptr_tree, sizeof(tree_t), 1, fp); // write new header
        fseek(fp, temp, SEEK_SET); // go to node pos
        fwrite(&temp_node, sizeof(node_t), 1, fp); // write new node to file

    }
    else // tree is there
    {
        fseek(fp, 0, SEEK_END); // go to end
        idx_nn = ftell(fp); // new node offset
        fwrite(&temp_node, sizeof(temp_node), 1, fp); // written nn to the end of the file

        node_t curr_node;
        int off;
        off = ptr_tree->root; // stores current offset

        while(off != -1)
        {
            fseek(fp, off, SEEK_SET); // go to the node position
            fread(&curr_node, sizeof(node_t), 1, fp); // read node into curr_node
            // printf("read ..%d \n", curr_node.key); // printing whats read ..for debugging

            if(key > curr_node.key) // then traverse the right subtree
            {
                roff = curr_node.right_off; // right child position
                if(roff == -1)
                {
                    curr_node.right_off = idx_nn; // curr node now points to new node right child
                    fseek(fp, off, SEEK_SET); 
                    fwrite(&curr_node, sizeof(temp_node), 1, fp); // write the updated parent node after inserting 
                    break;
                }
                else
                {
                    off = roff;
                }
                
            }
            else if(key < curr_node.key) // then traverse the left subtree
            {
                loff = curr_node.left_off; // left child position
                if(loff == -1)
                {
                    curr_node.left_off = idx_nn; // curr node now points to new node left child
                    fseek(fp, off, SEEK_SET); 
                    fwrite(&curr_node, sizeof(temp_node), 1, fp); // write the updated parent node after inserting 
                    break;
                }
                else
                {
                    off = loff;
                }
                
            }
        }
        
    }
    
}

// close file
void close_tree(tree_t *t, FILE *fp)
{
    fclose(fp);
}


// before calling inorder fseek past header info
// so fp points to first node if not empty
void display_inorder(const tree_t *t, FILE *fp)
{
    freopen("1244_output_A4.txt", "a+", stdout);
    fseek(fp, sizeof(*t), SEEK_SET);
    inorder(t->root, fp); 
    printf("\n");
}
void inorder(int root, FILE* fp) 
{ 
    node_t temp_node; // holds curr node info
    if(root != -1) // if root is not null
    { 
        // freopen("1244_output_A4.txt", "w", stdout);
        fseek(fp, root, SEEK_SET);
        fread(&temp_node, sizeof(temp_node), 1, fp);
        inorder(temp_node.left_off, fp); 
        printf("%d ", temp_node.key); 
        inorder(temp_node.right_off, fp); 
    } 
} 


// before calling preorder fseek past header info
// so fp points to first node if not empty
void display_preorder(const tree_t *t, FILE *fp)
{
    freopen("1244_output_A4.txt", "a+", stdout);
    fseek(fp, sizeof(*t), SEEK_SET);
    preorder(t->root, fp); 
    printf("\n");
}
void preorder(int root, FILE* fp) 
{ 
    node_t temp_node; // holds curr node info
    if(root != -1) // if root is not null
    { 
        fseek(fp, root, SEEK_SET);
        fread(&temp_node, sizeof(temp_node), 1, fp);
        printf("%d ", temp_node.key); 
        preorder(temp_node.left_off, fp); 
        
        preorder(temp_node.right_off, fp); 
    } 
} 


// deleted key given if tree not empty 
void delete_key(tree_t *t, int key, FILE *fp)
{
    freopen("1244_output_A4.txt", "a+", stdout);
    fseek(fp, sizeof(*t), SEEK_SET);
    if(t->root == -1) // checks if empty and prints -1 if so
    {
        printf("-1");
    }
    else
    {
        delete(t->root, key, fp);
    }
    
} 
// helper function for delete
int delete(int root, int key, FILE* fp)
{
    node_t temp_node;
    fseek(fp, root, SEEK_SET);
    fread(&temp_node, sizeof(temp_node), 1, fp);

    if(key > temp_node.key) // traverse right sub tree
    {
        temp_node.right_off = delete(temp_node.right_off, key, fp);
        fseek(fp, root, SEEK_SET); // to to node position 
        fwrite(&temp_node, sizeof(temp_node), 1, fp); // write updated node
    }
    else if(key < temp_node.key) // traverse left sub tree
    {
        temp_node.left_off = delete(temp_node.left_off, key, fp);
        fseek(fp, root, SEEK_SET); // to to node position 
        fwrite(&temp_node, sizeof(temp_node), 1, fp); // write updated node
    }
    else
    {
        // no child
        if(temp_node.right_off == -1 && temp_node.left_off == -1)
        {
            root = -1; 
        }
        // has left child
        else if(temp_node.right_off == -1)
        {
            root = temp_node.left_off;
        }
        // has right child
        else if(temp_node.left_off == -1)
        {
            root = temp_node.right_off;
        }
        // has both children
        else
        {
            node_t x;
            int temp = minRSTvalue(temp_node.right_off, fp); // gets min right sub tree offset
            fseek(fp, temp, SEEK_SET); // goes to that position
            fread(&x, sizeof(node_t), 1, fp); // reads that node
            temp_node.key = x.key; // overwrites the node to be deleted with that key
            fseek(fp, root, SEEK_SET); // goes to node to be deleted position
            fwrite(&temp_node, sizeof(temp_node), 1, fp); // writes updated value
            temp_node.right_off = delete(temp_node.right_off, x.key, fp); // procedes to delete the min RSTvalue
            fseek(fp, root, SEEK_SET); // goes to node to be deleted position
            fwrite(&temp_node, sizeof(temp_node), 1, fp); // writes updated value
        }      
    }
    return root; // returns the root value according to the above conditions   
}

// returns offset of the least value in the right sub tree..i.e keep traversing
// left child till it becomes -1
int minRSTvalue(int root, FILE* fp)
{
    node_t curr_node;
    fseek(fp, root, SEEK_SET);
    fread(&curr_node, sizeof(node_t), 1, fp);
    if(curr_node.left_off == -1)
    {
        return root;
    }
    else
    {
        minRSTvalue(curr_node.left_off, fp);
    }    
}




