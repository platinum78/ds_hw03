#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"
#include "./queue.h"


void bstTraverse(TreeNode* root, Queue* queue)
{
    if (root != NULL)
    {
        bstTraverse(root->leftChild, queue);
        AddQ(queue, root);
        printf("Added %d \n", root->key);
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
    char cStrBuf[100] = { '\0', };
    char cCharBuf;
    int nReadLen = 0;
    int nLineLen = 0; int nCursor = 0; int nKeyBuf[2] = { 0, 0 };
    int treeCnt = 0;
    int EOL = FALSE;
    TreeNode* pNode; TreeNode* tree = *bst1;
    fseek(input, 0, SEEK_END);
    int nFileLen = ftell(input);
    fseek(input, 0, SEEK_SET);
    
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
            printf("New tree with root key %d \n", nKeyBuf[0]);
            treeCnt++;
            printf("TreeCnt: %d \n", treeCnt);
            if (treeCnt == 1)
                bstInit(bst1, nKeyBuf[0], 0);
            else if (treeCnt == 2)
                bstInit(bst2, nKeyBuf[0], 0);
        }
        else
        {
            if (treeCnt == 1) pNode = bstFindElemAddr(*bst1, nKeyBuf[0]);
            else if (treeCnt == 2) pNode = bstFindElemAddr(*bst2, nKeyBuf[0]);
            bstInsertEdge(pNode, nKeyBuf[1], 0);
        }
    }
}


// Merge two binary search trees
void bstMerge(TreeNode* bst1, TreeNode* bst2)
{
    // Get information of first and second BST
    int bst1Size = bstGetSize(bst1);
    int bst2Size = bstGetSize(bst2);
    printf("%d, %d \n", bst1Size, bst2Size);
    
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
    printf("Checkpoint! \n");
    bstTraverse(pAugmentation, iterQ);
    TreeNode* pNode;
    int opCnt = 0;
    
    bstPrint(pOriginal);
    bstPrint(pAugmentation);

    while (1)
    {
        pNode = (TreeNode*)DeleteQ(iterQ);
        if (pNode == NULL) break;
        printf("%d %d \n", pNode->key, pNode->data);
        bstInsert(pOriginal, pNode->key, pNode->data);
        opCnt++;
    }
}

void outputWrite(FILE* output, TreeNode* bstNew)
{
    bstWriteLevelOrder(output, bstNew);
    printf("Checkpoint! \n");
    fprintf(output, "%d\n%d\n", bstGetSize(bstNew), bstGetSize(bstNew));
    printf("Checkpoint! \n");
}

#endif