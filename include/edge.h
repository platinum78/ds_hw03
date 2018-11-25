#ifndef __EDGE_H__
#define __EDGE_H__

#include "./tree.h"

typedef struct Edge_
{
    TreeNode* parent;
    TreeNode* child;
} Edge;

typedef struct EdgeList_
{
    Edge* head;
    int capacity;
    int size;
} EdgeList;

EdgeList* EdgeListInit()
{
    EdgeList* pList = (EdgeList*)malloc(sizeof(EdgeList));
    pList->head = (Edge*)malloc(sizeof(Edge) * 4);
    pList->capacity = 4;
    pList->size = 0;
    return pList;
}

EdgeList* EdgeDoubleList(EdgeList* list)
{
    (list->capacity) *= 2;
    list->head = realloc(list->head, sizeof(Edge) * (list->capacity));
}

void EdgeListInsert(EdgeList* list, TreeNode* parent, TreeNode* child)
{
    (list->head)[list->size] = (Edge){ .parent = parent, .child = child };
    (list->size)++;
    if (list->size == list->capacity) EdgeDoubleList(list);
}


#endif