#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"
#include "./queue.h"
#include "./stack.h"


void bstTraverse(TreeNode* root, Queue* queue)
{
    if (root != NULL)
    {
        bstTraverse(root->leftChild, queue);
        AddQ(queue, root);
        bstTraverse(root->rightChild, queue);
    }
}

int bstRead(FILE* file, TreeNode* bst1, TreeNode* bst2)
{
    char cStrBuf[100] = { '\n', };
    char cCharBuf;
    int nLineLen = 0; int nCursor = 0; int nKeyBuf[2] = { 0, 0 };
    int EOL = FALSE;
    TreeNode* pNode; TreeNode* tree = bst1;
    fseek(file, 0, SEEK_SET);

    while (fread(&cCharBuf, 1, 1, file))
    {
        // Switch cases through input character value
        switch (cCharBuf)
        {
            case ' ':
                if (nCursor)
                {
                    cStrBuf[nCursor] = '\n';
                    nKeyBuf[nLineLen++] = atoi(cStrBuf);
                    nCursor = 0;
                    nLineLen++;
                }
                break;
            case '\n':
                if (nCursor)
                {
                    cStrBuf[nCursor] = '\0';
                    nKeyBuf[nLineLen++] = atoi(cStrBuf);
                    nCursor = 0;
                    nLineLen++;
                    EOL = TRUE;
                }
                break;
            default:
                cStrBuf[nCursor++] = cCharBuf;
                break;
        }

        // Do parsing operation when reached EOL
        if (EOL)
        {
            if (nLineLen == 1)  // Only one argument given: this is the root node
            {
                bstInit(bst1, nKeyBuf[0], 0);
            }
            else  // Two arguments are given: this is a parent-leaf tuple
            {
                pNode = bstFindElemAddr(nKeyBuf[0]);
                // bstInsertEdge();
            }
            EOL = FALSE;
        }
    }
}


// Merge two binary search trees
void bstMerge(TreeNode* bst1, TreeNode* bst2)
{
    // Get information of first and second BST
    int bst1Size = bstGetSize(bst1);
    int bst2Size = bstGetSize(bst2);
    int bst1Range[2] = { bstLeftMost(bst1)->key, bstRightMost(bst1)->key };
    int bst2Range[2] = { bstLeftMost(bst2)->key, bstRightMost(bst2)->key };

    // Step 01: Find the place where the second BST is to be attached.
    int bst2RootKey = bst2->key;
    TreeNode* pNode; TreeNode* pNext = bst1;
    while (pNext)
    {
        pNode = pNext;
        if (pNext->key < bst2RootKey) pNext = pNext->leftChild;
        else if (pNext->key == bst2RootKey) return;
        else pNext = pNext->rightChild;
    }
    TreeNode* pAttachNode = pNode;

    // Step 02: Create a stack that stores the address of the attachment node
    Stack* iterStack = StackInit();
    while (pNext)
    {
        pNode = pNext;
        pNext = pNext->parent;
        StackPush(iterStack, pNode);
    }
    StackFlip(iterStack);

    // Step 03: Traverse the BST inorder, descending order, and find incompliant nodes.
    // Create queue to store elements to be trimmed
    Queue* dataQ = QInit();
    Queue* trimQ = QInit();
    bstTraverse(bst1, dataQ);

    int nAttachNodeIdx = IndexQ(dataQ, pAttachNode);
    int idx = 0;
    QElem* pQElem = dataQ->head;

    for (idx = 0; idx < dataQ->length; idx++)
    {
        if (idx < nAttachNodeIdx)
            if (pQElem->data->key > pAttachNode->key)
                AddQ(trimQ, pQElem);
        else if (idx > nAttachNodeIdx)
            if (pQElem->data->key < pAttachNode->key)
                AddQ(trimQ, pQElem);
        pQElem = pQElem->next;
    }

    // Attach the smaller BST to somewhere appropriate in the larger BST
    
}

#endif