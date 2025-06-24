#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"
#include "tree.h"
#include <stddef.h>

int main(void)
{
	Tree mytree;

	init_tree(&mytree);
		
	for (int i = 0; i < 10; ++i)
	{
        int *value = malloc(sizeof(int));  // Required for void* storage
        *value = i * 2;
        insert_tree(&mytree, value, cmp_int);
    }	


	printf("Inorder traversal: ");
    traverse_tree_inorder(mytree.root, print_int);
    putchar('\n');

    printf("Preorder traversal: ");
    traverse_tree_preorder(mytree.root, print_int);
    putchar('\n');

    printf("Postorder traversal: ");
    traverse_tree_postorder(mytree.root, print_int);
    putchar('\n');
    
	free_tree(&mytree, free);

	return 0;
}
