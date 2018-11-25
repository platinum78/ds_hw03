#include <stdio.h>
#include <stdlib.h>
#include "./include/tree.h"
#include "./include/tree_utils.h"

int main(void)
{
    FILE* input = fopen("./io/input.txt", "r");
    FILE* output = fopen("./io/output.txt", "w");

    TreeNode* bst1;
    TreeNode* bst2;

    bstRead(input, &bst1, &bst2);
    TreeNode* bstMerged = bstMerge(bst1, bst2);

    printf("====== Merged BST ====== \n");
    bstPrint(bstMerged);
    outputWrite(output, bstMerged);
    
    return 0;
}