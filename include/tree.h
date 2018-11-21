#ifndef __TREE_H__
#define __TREE_H__

#define LEFT 1
#define RIGHT 2

#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode_
{
    struct TreeNode_* leftChild;
    struct TreeNode_* rightChild;
    struct TreeNode_* parent;
    int leftCnt;
    int key;
    int data;
} TreeNode;

void bstInit(TreeNode*, int, int);
TreeNode* bstFindElemAddr(int key);
int bstIndexOf(int data);
int bstAttach(TreeNode* root, TreeNode* node);
int bstInsert(TreeNode* root, int, int);
int bstInsertEdge(TreeNode* node, int, int);
TreeNode* bstLeftMost(TreeNode* node);
TreeNode* bstRightMost(TreeNode* node);
void bstMerge(TreeNode* bst1, TreeNode* bst2);

void bstInit(TreeNode* rootAddr, int rootKey, int data)
{
    rootAddr = (TreeNode*)malloc(sizeof(TreeNode));
    rootAddr->leftChild = NULL; rootAddr->rightChild = NULL;
    rootAddr->leftCnt = 0;
    rootAddr->key = rootKey;
    rootAddr->data = data;
}

TreeNode* bstFindElemAddr(TreeNode* root, int key)
{
    // Return NULL, if seeked for a nonexisting leaf
    if (root == NULL) return NULL;

    if (key < root->key)
        bstFindElemAddr(root->leftChild, key);
    else if (key == root->key)
        return root;
    else if (key > root->key)
        bstFindElemAddr(root->rightChild, key);
}

int bstAttach(TreeNode* root, TreeNode* node)
{
    // Copy pointer to root
    TreeNode* pNode = root;
    TreeNode* pNext = root;

    // Iterate until insertion position
    while (pNext != NULL)
    {
        pNode = pNext;
        if (node->key < pNext->key) pNext = pNext->leftChild;
        else if (node->key == pNext->key) return -1;
        else if (node->key > pNext->key) pNext = pNext->rightChild;
    }


    // Attach node to the leaf node
    if (node->key < pNode->key) pNode->leftChild = node;
    else if (node->key > pNode->key) pNode->rightChild = node;
    
    return 0;
}

int bstInsert(TreeNode* root, int key, int data)
{
    // Copy pointer to root
    TreeNode* pNode = root;
    TreeNode* pNext = root;

    // Iterate until insertion position
    while (pNext)
    {
        pNode = pNext;
        if (key < pNext->key) pNext = pNext->leftChild;
        else if (key == pNext->key) return -1;
        else if (key > pNext->key) pNext = pNext->rightChild;
    }

    // Insert data into desired position
    if (key < pNode->key) pNode->leftChild = (TreeNode*)malloc(sizeof(TreeNode));
    else if (key > pNode->key) pNode->rightChild = (TreeNode*)malloc(sizeof(TreeNode));

    return 0;
}

int bstInsertEdge(TreeNode* node, int key, int data)
{
    if (key < node->key) bstInit(node->leftChild, key, data);
    else if (key > node->key) bstInit(node->rightChild, key, data);
    else return -1;
    return 0;
}

// Return the address of the leftmost subsidiary node
TreeNode* bstLeftMost(TreeNode* node)
{
    TreeNode* pNode = NULL; TreeNode* pNext = node;
    
    while (pNext)
    {
        pNode = pNext;
        pNext = pNext->leftChild;
    }
    
    return pNode;
}

// Return the address of the rightmost subsidiary node
TreeNode* bstRightMost(TreeNode* node)
{
    TreeNode* pNode = NULL; TreeNode* pNext = node;

    while (pNext)
    {
        pNode = pNext;
        pNext = pNext->rightChild;
    }

    return pNode;
}


#endif