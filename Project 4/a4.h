#ifndef a4_h
#define a4_h

#include <stdio.h>

struct node
{
	int key;
	int left_off;
	int right_off;
};
typedef struct node node_t;

struct tree
{
	int free_head;
	int root;
};
typedef struct tree tree_t;

FILE* init_tree(tree_t*, const char* name); // done

void close_tree(tree_t *, FILE *fp); // done

void display_inorder(const tree_t *ptr_tree, FILE *fp); // done
	// Space separated keys. Last key followed by '\n'

void display_preorder(const tree_t *ptr_tree, FILE *fp); // done
	// Space separated keys. Last key followed by '\n'

void insert_key(tree_t *ptr_tree, int key, FILE *fp); // done

void delete_key(tree_t *ptr_tree, int key, FILE *fp); // done

#endif
