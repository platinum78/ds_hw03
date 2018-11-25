#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"
#define TRUE 1
#define FALSE 0

typedef struct NodeList_
{
    TreeNode** head;
    int capacity;
    int length;
} NodeList;

NodeList* nodeListInit()
{
    NodeList* pList = (NodeList*)malloc(sizeof(NodeList));
    pList->head = (TreeNode**)malloc(sizeof(TreeNode*) * 4);
    pList->capacity = 4;
    pList->length = 0;
    return pList;
}

void nodeListDouble(NodeList* list)
{
    (list->capacity) *= 2;
    list->head = realloc(list->head, sizeof(TreeNode*) * list->capacity);
}

void nodeInsert(NodeList* list, TreeNode* node)
{
    (list->head)[list->length] = node;
    (list->length)++;
    if (list->length == list->capacity) nodeListDouble(list);
}

TreeNode* nodeExists(NodeList* list, int targetKey)
{
    int idx = 0;
    for (idx = 0; idx < list->length; idx++) if ((list->head)[idx]->key == targetKey) return (list->head)[idx];
    return NULL;
}


#endif