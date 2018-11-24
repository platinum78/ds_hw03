#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"

typedef void* dtype;

typedef struct QElem_
{
    dtype data;
    struct QElem_* next;
} QElem;

typedef struct Queue
{
    int length;
    QElem* head;
    QElem* tail;
} Queue;

Queue* QInit();
void AddQ(Queue*, dtype);
dtype DeleteQ(Queue*);
int PurgeQ(Queue*);
int IndexQ(Queue* queue, dtype val);

// Initialize Queue instance and return it.
Queue* QInit()
{
    Queue* pQueue = (Queue*)malloc(sizeof(Queue));
    pQueue->head = NULL;
    pQueue->tail = NULL;
    pQueue->length = 0;

    return pQueue;
}

// Add element to the Queue
void AddQ(Queue* queue, dtype val)
{
    QElem* pElem = (QElem*)malloc(sizeof(QElem));
    pElem->next = NULL;
    pElem->data = val;

    if (queue->head == NULL)
    {
        queue->head = pElem;
        queue->tail = pElem;
    }
    else
    {
        queue->tail->next = pElem;
        queue->tail = pElem;
    }
}

// Remove element from the Queue
dtype DeleteQ(Queue* queue)
{
    dtype data = queue->head->data;
    QElem* pElem = queue->head;
    queue->head = pElem->next;
    free(pElem);
    return data;
}

// Purge Queue
int PurgeQ(Queue* queue)
{
    QElem* pElem = NULL;
    QElem* pNext = queue->head;
    int delCnt = 0;
    
    while (pNext)
    {
        pElem = pNext;
        pNext = pNext->next;
        free(pElem);
        delCnt++;
    }

    free(queue);
    return delCnt;
}

int IndexQ(Queue* queue, dtype val)
{
    int idx = 0;
    QElem* pQElem = queue->head;
    while (idx < queue->length)
    {
        if (pQElem->data == val) return idx;
        idx++;
    }
    
    return -1;
}


#endif