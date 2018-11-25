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

void bstInit(TreeNode**, int, int);
int bstIndexOf(int data);
int bstAttach(TreeNode* root, TreeNode* node);
int bstInsert(TreeNode* root, int, int);
int bstInsertEdge(TreeNode* node, int, int);
int bstGetSize(TreeNode* root);
int bstGetHeight(TreeNode* root);
int bstNodeDelete(TreeNode* node);
int bstDelete(TreeNode* root, int key);
int bstNodeDegree(TreeNode* node);
TreeNode* bstFindElemAddr(TreeNode* root, int key);
TreeNode* bstLeftMost(TreeNode* node);
TreeNode* bstRightMost(TreeNode* node);

void bstInit(TreeNode** rootAddr, int rootKey, int data)
{
    *rootAddr = (TreeNode*)malloc(sizeof(TreeNode));
    (*rootAddr)->leftChild = NULL; (*rootAddr)->rightChild = NULL; (*rootAddr)->parent = NULL;
    (*rootAddr)->leftCnt = 0;
    (*rootAddr)->key = rootKey;
    (*rootAddr)->data = data;
}

TreeNode* bstNodeInit(TreeNode* parent, TreeNode* leftChild, TreeNode* rightChild, int key, int data)
{
    TreeNode* pNode = (TreeNode*)malloc(sizeof(TreeNode));
    pNode->parent = parent;
    pNode->leftChild = leftChild;
    pNode->rightChild = rightChild;
    pNode->key = key;
    pNode->data = data;
    return pNode;
}

TreeNode* bstFindElemAddr(TreeNode* root, int key)
{
    if (root == NULL || key == root->key) return root;
    
    if (key < root->key) return bstFindElemAddr(root->leftChild, key);
    else if (key > root->key) return bstFindElemAddr(root->rightChild, key);
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
    if (key < pNode->key)
    {
        pNode->leftChild = (TreeNode*)malloc(sizeof(TreeNode));
        pNode->leftChild->leftChild = NULL;
        pNode->leftChild->rightChild = NULL;
        pNode->leftChild->key = key;
        pNode->leftChild->data = data;
        pNode->leftChild->parent = pNode;
        printf("Insert %4d as the left  child of %4d \n", key, pNode->key);
    }
    else if (key > pNode->key)
    {
        pNode->rightChild = (TreeNode*)malloc(sizeof(TreeNode));
        pNode->rightChild->leftChild = NULL;
        pNode->rightChild->rightChild = NULL;
        pNode->rightChild->key = key;
        pNode->rightChild->data = data;
        pNode->rightChild->parent = pNode;
        printf("Insert %4d as the right child of %4d \n", key, pNode->key);
    }

    return 0;
}

int bstInsertEdge(TreeNode* node, int key, int data)
{
    if (key < node->key)
    {
        printf("Insert %4d as the left  child of %4d \n", key, node->key);
        bstInit(&(node->leftChild), key, data);
        node->leftChild->parent = node;
    }
    else if (key > node->key)
    {
        printf("Insert %4d as the right child of %4d \n", key, node->key);
        bstInit(&(node->rightChild), key, data);
        node->rightChild->parent = node;
    }
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

// Get the size of BST; using recursive function
int bstGetSize(TreeNode* root)
{
    if (root == NULL) return 0;
    if (root->leftChild == NULL && root->rightChild == NULL) return 1;
    return bstGetSize(root->leftChild) + bstGetSize(root->rightChild) + 1;
}

// Get the height of BST
int bstGetHeight(TreeNode* root)
{
    if (bstNodeDegree(root) != 0) return 1;
    if (bstGetHeight(root->leftChild));  // MODIFY THIS
}

// Get the degree of a node in a BST
int bstNodeDegree(TreeNode* node)
{
    if (node->leftChild)
    {
        if (node->rightChild) return 2;
        else return 1;
    }
    else return 0;
}

// Delete node from the BST, using the given NODE
int bstNodeDelete(TreeNode* node)
{
    int nNodeDegree = bstNodeDegree(node);
    TreeNode* pNode = NULL;
    int delKey = 0;

    if (nNodeDegree == 2)
    {
        // Use the rightmost of left subtree for the new key
        pNode = bstRightMost(node->leftChild);
        
        if (bstNodeDegree(pNode) == 1)
        {
            pNode->leftChild->parent = pNode->parent;
            pNode->parent->rightChild = pNode->leftChild;
        }
        else
        {
            pNode->parent->rightChild = NULL;
        }

        // Replace node with pNode
        pNode->leftChild = node->leftChild;
        pNode->rightChild = node->rightChild;
        pNode->parent = node->parent;
        delKey = node->key;
        free(node);
    }
    else if (nNodeDegree == 1)
    {
        if (node->leftChild)
        {
            if (node == node->parent->leftChild) node->parent->leftChild = node->leftChild;
            else if (node == node->parent->rightChild) node->parent->rightChild = node->leftChild;
        }
        else if (node->rightChild)
        {
            if (node == node->parent->leftChild) node->parent->leftChild = node->rightChild;
            else if (node == node->parent->rightChild) node->parent->rightChild = node->rightChild;
        }
        delKey = node->key;
        free(node);
    }
    else if (nNodeDegree == 0)
    {
        if (node == node->parent->leftChild) node->parent->leftChild = NULL;
        else if (node == node->parent->rightChild) node->parent->rightChild = NULL;
        delKey = node->key;
        free(node);
    }
}

// Delete node from the BST
int bstDelete(TreeNode* root, int key)
{
    TreeNode* pNode = bstFindElemAddr(root, key);
    return bstNodeDelete(pNode);
}

void bstPrint(TreeNode* root)
{
    if (root != NULL)
    {
        bstPrint(root->leftChild);
        printf("Key: %4d, Data: %4d, pointer: %p, leftChild: %p, rightChild: %p, parent: %p \n", root->key, root->data, root, root->leftChild, root->rightChild, root->parent);
        bstPrint(root->rightChild);
    }
}

TreeNode* bstFindRoot(TreeNode* root)
{
    TreeNode* pNode; TreeNode* pNext = root;

    while (pNext)
    {
        pNode = pNext;
        pNext = pNext->parent;
    }
    return pNode;
}

#endif