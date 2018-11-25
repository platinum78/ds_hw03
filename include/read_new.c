#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"
#include "./queue.h"
#include "./edge.h"
#include "./node.h"

#define TRUE 1
#define FALSE 0

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

                if (pNode)
                {
                    pNode = bstNodeInit(NULL, NULL, NULL, nKeyBuf[0], 0);
                    nodeInsert(bst1Node, pNode);
                if (pNext)
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

                if (pNode)
                {
                    pNode = bstNodeInit(NULL, NULL, NULL, nKeyBuf[0], 0);
                    nodeInsert(bst2Node, pNode);
                }
                if (pNext)
                {
                    pNext = bstNodeInit(NULL, NULL, NULL, nKeyBuf[1], 0);
                    nodeInsert(bst2Node, pNext);
                }

                EdgeListInsert(bst2Edge, pNode, pNext);
            }
        }

        for (idx = 0; idx < bst1Edge->size; idx++)
        {
            if (bst1Edge->head[idx].parent > bst2Edge->head[idx].child)
                bst1Edge->head[idx].parent->leftChild = bst2Edge->head[idx].child;
            else
                bst1Edge->head[idx].parent->rightChild = bst2Edge->head[idx].child;
            
            bst1Edge->head[idx].child->parent = bst2Edge->head[idx].parent;
        }
        *bst1 = bstFindRoot(bst1Edge->head[idx].child->parent);

        for (idx = 0; idx < bst2Edge->size; idx++)
        {
            if (bst2Edge->head[idx].parent > bst2Edge->head[idx].child)
                bst2Edge->head[idx].parent->leftChild = bst2Edge->head[idx].child;
            else
                bst2Edge->head[idx].parent->rightChild = bst2Edge->head[idx].child;
            
            bst2Edge->head[idx].child->parent = bst2Edge->head[idx].parent;
        }
        *bst2 = bstFindRoot(bst2Edge->head[idx].child->parent);
    }

    if (nTreeSize[0] != bstGetSize(*bst1))
        printf("Node size of first BST does not match! \n");
    if (nTreeSize[1] != bstGetSize(*bst2))
        printf("Node size of second BST does not match! \n");
}




int bstRead(FILE* input, TreeNode** bst1, TreeNode** bst2)
{
    char cStrBuf[100] = { '\0', };
    char cCharBuf;
    int nReadLen = 0; int treeCnt = 0; int nLineLen = 0; int nCursor = 0;
    int nKeyBuf[2] = { 0, 0 }; int nTreeSize[2] = { 0, 0 };
    int firstLine = FALSE;
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
            printf("New tree with %d nodes + leafs \n", nKeyBuf[0]);
            treeCnt++;
            printf("TreeCnt: %d \n", treeCnt);
            if (treeCnt == 1)
            {
                bstInit(bst1, nKeyBuf[0], 0);
                nTreeSize[0] = nKeyBuf[0];
            }
            else if (treeCnt == 2)
            {
                bstInit(bst2, nKeyBuf[0], 0);
                nTreeSize[1] = nKeyBuf[0];
            }
            firstLine = TRUE;
        }
        else
        {
            if (treeCnt == 1)
            {
                if (firstLine == TRUE) bstInit(bst1, nKeyBuf[0], 0);
                pNode = bstFindElemAddr(*bst1, nKeyBuf[0]);
                if (pNode) bstInsertEdge(pNode, nKeyBuf[1], 0);
                else printf("Node not found! \n");
                // else
                // {
                //     bstInsert(*bst1, nKeyBuf[0], 0);
                //     bstInsert(*bst1, nKeyBuf[1], 0);
                // }
            }
            else if (treeCnt == 2)
            {
                if (firstLine == TRUE) bstInit(bst2, nKeyBuf[0], 0);
                pNode = bstFindElemAddr(*bst2, nKeyBuf[0]);
                if (pNode) bstInsertEdge(pNode, nKeyBuf[1], 0);
                else printf("Node not found! \n");
                // else
                // {
                //     bstInsert(*bst2, nKeyBuf[0], 0);
                //     bstInsert(*bst2, nKeyBuf[1], 0);
                // }
            }
            firstLine = FALSE;
        }
    }

    if (nTreeSize[0] != bstGetSize(*bst1))
        printf("Node size of first BST does not match! \n");
    if (nTreeSize[1] != bstGetSize(*bst2))
        printf("Node size of second BST does not match! \n");
}