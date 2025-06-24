#include "tree.h"
#include <stddef.h>
#include <stdlib.h>

void init_tree(Tree *tree)
{
	if (!tree) return;

    tree->root = NULL;
    tree->size = 0;
}

int cmp_int(const void *a, const void *b) 
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

// Trasverse
void traverse_tree_inorder(TreeNode *node, void (*visit)(void *))
{
    if (!node) return;
    traverse_tree_inorder(node->left, visit);
    visit(node->value);
    traverse_tree_inorder(node->right, visit);
}

void traverse_tree_preorder(TreeNode *node, void (*visit)(void *))
{
    if (!node) return;
    visit(node->value);
    traverse_tree_preorder(node->left, visit);
    traverse_tree_preorder(node->right, visit);
}

void traverse_tree_postorder(TreeNode *node, void (*visit)(void *))
{
    if (!node) return;
    traverse_tree_postorder(node->left, visit);
    traverse_tree_postorder(node->right, visit);
    visit(node->value);
}

// Insert
TreeNode *insert_node(TreeNode *node, void *value, int (*cmp)(const void *, const void *), size_t *size)
{
    if (!node) 
    {
        TreeNode *new_node = malloc(sizeof(TreeNode));
        if (!new_node) return NULL;
        new_node->value = value;
        new_node->left = new_node->right = NULL;
        (*size)++;
        return new_node;
    }

    int compare = cmp(value, node->value);
    if (compare < 0)
        node->left = insert_node(node->left, value, cmp, size);
    else if (compare > 0)
        node->right = insert_node(node->right, value, cmp, size);
    // Ignore duplicate keys for now

    return node;
}

void insert_tree(Tree *tree, void *value, int (*cmp)(const void *, const void *))
{
    if (!tree || !cmp) return;

    tree->root = insert_node(tree->root, value, cmp, &tree->size);
}

// Clean
static void free_tree_node(TreeNode *node, void (*free_value)(void *))
{
    if (!node) return;

    free_tree_node(node->left, free_value);
    free_tree_node(node->right, free_value);

    if (free_value)
        free_value(node->value);

    free(node);
}


void free_tree(Tree *tree, void (*free_value)(void *))
{
    if (!tree) return;

    free_tree_node(tree->root, free_value);
    tree->root = NULL;
    tree->size = 0;
}