#ifndef __TREE_UTILS_H__
#define __TREE_UTILS_H__

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"


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
    // First, just attach the second BST to somewhere pertinent
    bstAttach(bst1, bst2);
    
}


#endif