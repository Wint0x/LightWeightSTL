#ifndef H_TREE
#define H_TREE

#include <stddef.h>

typedef struct TreeNode
{
	void *value;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct Tree
{
	TreeNode *root;
	size_t size;
} Tree;

int cmp_int(const void *a, const void *b);

// Init
void init_tree(Tree *tree);

// Insertion
void insert_tree(Tree *tree, void *value, int (*cmp)(const void *, const void *));
TreeNode *insert_node(TreeNode *node, void *value, int (*cmp)(const void *, const void *), size_t *size);

// Trasversal
void traverse_tree_inorder(TreeNode *node, void (*visit)(void *));
void traverse_tree_preorder(TreeNode *node, void (*visit)(void *));
void traverse_tree_postorder(TreeNode *node, void (*visit)(void *));

// Cleanup
void free_tree(Tree *tree, void (*free_value)(void *));

#endif