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

TreeNode* bstInit(int);
TreeNode* bstFindElemAddr(int key);
int bstIndexOf(int data);
int bstInsert(TreeNode* root, int, int);


TreeNode* bstInit(int rootKey)
{
    TreeNode* pNode = (TreeNode*)malloc(sizeof(TreeNode));
    pNode->leftChild = NULL; pNode->rightChild = NULL;
    pNode->leftCnt = 0;
    pNode->key = rootKey;
    pNode->data = 0;
    
    return pNode;
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

int bstInsert(TreeNode* root, int key, int data)
{
    // Copy pointer to root
    TreeNode* pNode = root;
    TreeNode* pNext = root;

    // Iterate until insertion position
    while (pNext != NULL)
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

#endif