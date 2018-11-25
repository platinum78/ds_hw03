#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"
#include "./queue.h"
#include "./edge.h"
#include "./node.h"


void bstTraverse(TreeNode* root, Queue* queue)
{
    if (root != NULL)
    {
        bstTraverse(root->leftChild, queue);
        AddQ(queue, root);
        // printf("Added %d \n", root->key);
        bstTraverse(root->rightChild, queue);
    }
}

void bstWrite(FILE* output, TreeNode* root)
{
    if (root != NULL)
    {
        if (root->parent == NULL)
            fprintf(output, "%d \n", root->key);
        else
            fprintf(output, "%d %d \n", root->parent->key, root->key);
        bstWrite(output, root->leftChild);
        bstWrite(output, root->rightChild);
    }
}

void bstWriteLevelOrder(FILE* output, TreeNode* root)
{
    TreeNode* pNode = root;
    Queue* traverseQ = QInit();
    AddQ(traverseQ, pNode);
    while (1)
    {
        pNode = (TreeNode*)DeleteQ(traverseQ);
        if (pNode == NULL) break;

        if (pNode->parent == NULL)
            fprintf(output, "%d \n", pNode->key);
        else
            fprintf(output, "%d %d \n", pNode->parent->key, pNode->key);

        if (pNode->leftChild) AddQ(traverseQ, pNode->leftChild);
        if (pNode->rightChild) AddQ(traverseQ, pNode->rightChild);
    }
}

int bstRead(FILE* input, TreeNode** bst1, TreeNode** bst2)
{
    char cCharBuf;
    char cStrBuf[100] = { '\0', };

    int nReadLen = 0; int treeCnt = 0; int nLineLen = 0; int nCursor = 0; int nBuf = 0; int idx = 0;
    int nKeyBuf[2] = { 0, 0 }; int nTreeSize[2] = { 0, 0 };

    TreeNode* pNode; TreeNode* pNext;
    TreeNode* tree = *bst1;

    fseek(input, 0, SEEK_END);
    int nFileLen = ftell(input);
    fseek(input, 0, SEEK_SET);

    EdgeList* bst1Edge = EdgeListInit();
    EdgeList* bst2Edge = EdgeListInit();
    NodeList* bst1Node = nodeListInit();
    NodeList* bst2Node = nodeListInit();
    
    while (ftell(input) < nFileLen)
    {
        nCursor = 0;
        while (1)
        {
            nReadLen = fread(&cCharBuf, 1, 1, input);
            if (cCharBuf == '\n' || nReadLen == 0) break;
            cStrBuf[nCursor++] = cCharBuf;
        }
        cStrBuf[nCursor] = '\0';
        nLineLen = sscanf(cStrBuf, "%d %d", nKeyBuf, nKeyBuf + 1);

        if (nLineLen == 1)
        {
            nBuf = 0;
            treeCnt++;
            if (treeCnt == 1) nTreeSize[0] = nKeyBuf[0];
            else if (treeCnt == 2) nTreeSize[1] = nKeyBuf[0];
        }
        else
        {
            if (treeCnt == 1)
            {
                pNode = nodeExists(bst1Node, nKeyBuf[0]);
                pNext = nodeExists(bst1Node, nKeyBuf[1]);

                if (pNode == NULL)
                {
                    pNode = bstNodeInit(NULL, NULL, NULL, nKeyBuf[0], 0);
                    nodeInsert(bst1Node, pNode);
                }
                if (pNext == NULL)
                {
                    pNext = bstNodeInit(NULL, NULL, NULL, nKeyBuf[1], 0);
                    nodeInsert(bst1Node, pNext);
                }

                EdgeListInsert(bst1Edge, pNode, pNext);
            }
            else if (treeCnt == 2)
            {
                pNode = nodeExists(bst2Node, nKeyBuf[0]);
                pNext = nodeExists(bst2Node, nKeyBuf[1]);

                if (pNode == NULL)
                {
                    pNode = bstNodeInit(NULL, NULL, NULL, nKeyBuf[0], 0);
                    nodeInsert(bst2Node, pNode);
                }
                if (pNext == NULL)
                {
                    pNext = bstNodeInit(NULL, NULL, NULL, nKeyBuf[1], 0);
                    nodeInsert(bst2Node, pNext);
                }

                EdgeListInsert(bst2Edge, pNode, pNext);
            }
        }
    }


    for (idx = 0; idx < bst1Edge->size; idx++)
    {
        if (bst1Edge->head[idx].parent->key > bst1Edge->head[idx].child->key)
            bst1Edge->head[idx].parent->leftChild = bst1Edge->head[idx].child;
        else
            bst1Edge->head[idx].parent->rightChild = bst1Edge->head[idx].child;
        
        bst1Edge->head[idx].child->parent = bst1Edge->head[idx].parent;
    }
    *bst1 = bstFindRoot(bst1Edge->head[0].parent);
    bstPrint(*bst1);

    for (idx = 0; idx < bst2Edge->size; idx++)
    {
        if (bst2Edge->head[idx].parent->key > bst2Edge->head[idx].child->key)
            bst2Edge->head[idx].parent->leftChild = bst2Edge->head[idx].child;
        else
            bst2Edge->head[idx].parent->rightChild = bst2Edge->head[idx].child;
        
        bst2Edge->head[idx].child->parent = bst2Edge->head[idx].parent;
    }
    *bst2 = bstFindRoot(bst2Edge->head[0].parent);
    bstPrint(*bst2);


    if (nTreeSize[0] != bstGetSize(*bst1))
        printf("Node size of first BST does not match! \n");
    else
        printf("Node size of first BST does match. \n");
    if (nTreeSize[1] != bstGetSize(*bst2))
        printf("Node size of second BST does not match! \n");
    else
        printf("Node size of second BST does match. \n");
}


// Merge two binary search trees
TreeNode* bstMerge(TreeNode* bst1, TreeNode* bst2)
{
    // Get information of first and second BST
    int bst1Size = bstGetSize(bst1);
    int bst2Size = bstGetSize(bst2);
    printf("BST 1 size: %d, BST 2 size: %d \n", bst1Size, bst2Size);
    
    TreeNode* pOriginal;
    TreeNode* pAugmentation;
    if (bst1Size > bst2Size)
    {
        pOriginal = bst1;
        pAugmentation = bst2;
    }
    else
    {
        pOriginal = bst2;
        pAugmentation = bst1;
    }

    // Iterate the smaller BST and add each value to the larger BST
    Queue* iterQ = QInit();
    // printf("Adding all elements in augmentation tree to a queue... \n");
    bstTraverse(pAugmentation, iterQ);
    TreeNode* pNode;
    int opCnt = 0;
    
    // printf("====== Original BST ====== \n");
    // bstPrint(pOriginal);
    // printf("====== Augmented BST ====== \n");
    // bstPrint(pAugmentation);

    printf("Adding elements of augmented BST to original BST... \n");
    while (1)
    {
        pNode = (TreeNode*)DeleteQ(iterQ);
        if (pNode == NULL) break;
        // printf("%d %d \n", pNode->key, pNode->data);
        bstInsert(pOriginal, pNode->key, pNode->data);
        opCnt++;
    }

    return pOriginal;
}

void outputWrite(FILE* output, TreeNode* bstNew)
{
    bstWriteLevelOrder(output, bstNew);
    fprintf(output, "%d\n%d\n", bstGetSize(bstNew), bstGetSize(bstNew));
}



#endif