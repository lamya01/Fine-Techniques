How to COMPLILE and EXECUTE my code:
 	step1:  gcc -Wall 1244_impl_A4.c -c
	step2:  gcc -Wall 1244_impl_A4.o client1.c -o client.out
	step3:  ./client.out < sample_input.txt
To see the output file execute :
	step4: cat 1244_output_A3.txt 




NOTE!!! : the output file must be deleted after every execution because it is opened and written to in "a+" mode.






STRUCTURES used to implement the program:
	- nodes
	- tree header info
	

WORKING:
a menu is displayed to a user : insert, delete, ignorer, preorder traversal. According to the chosen options via the input file the program runs by going to the appropriate functions respectfully. The tree is a binary search tree i.e the nodes to the left of the root are always less than the root and the nodes to the right of the root are always greater than the root node value itself. So while traversing we always keep those conditions in mind while deleting and inserting at appropriate locations.

LOGIC FOR INSERT:
The key to be inserted has to follow the BST order conditions so the program first traverses the tree to find the position where it needs to be inserted and then inserts the key as a leaf always. If its already present in the tree then it ignores this insertion.

LOGIC FOR DELETION:
The tree should not be empty. If it is then -1 is printed else it goes ahead to delete the node. The following 3 situations may appear w.r.t the node to the node to be deleted:
	- has no children i.e leaf
	- has only 1 child
	- has both children
In the first case it simply deletes than node.
In the second, it copies the child in the node to be deleted position and then deleted the child which is a leaf.
In the third case, the min right sub tree value a.k.a the inorder successor is found and copied to node to be deleted's position and then deletes the former.

LOGIC FOR PREORDER AND INORDER TRAVERSAL:
both functions are recursive and call it in root(print), left, right and left, root(print), right respectively. Then recursive functions are invoked within wrapper functions each.
