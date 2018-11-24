#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include "./tree.h"

typedef TreeNode* dtype;

typedef struct StackElem_
{
    dtype data;
    struct StackElem_* next;
    struct StackElem_* prev;
} StackElem;

typedef struct Stack_
{
    StackElem* bottom;
    StackElem* top;
    int length;
} Stack;

Stack* StackInit();
void StackPush(Stack* stack, dtype val);
dtype StackPop(Stack* stack);
void StackPurge(Stack* stack);

Stack* StackInit()
{
    Stack* pStack = (Stack*)malloc(sizeof(Stack));
    pStack->bottom = NULL;
    pStack->top = NULL;
    pStack->length = 0;
}

void StackPush(Stack* stack, dtype val)
{
    StackElem* pStackElem = (StackElem*)malloc(sizeof(StackElem));
    pStackElem->data = val;
    pStackElem->next = NULL;

    if (stack->length == 0)  // Previously stack had no element within it.
    {
        pStackElem->prev = NULL;
        stack->bottom = pStackElem;
        stack->top = pStackElem;
        (stack->length)++;
    }
    else
    {
        pStackElem->prev = stack->top;
        stack->top->next = pStackElem;
        stack->top = pStackElem;
        (stack->length)++;
    }
}

dtype StackPop(Stack* stack)
{
    dtype delData = 0;
    StackElem* pStackElem;

    if (stack->length = 0) return (dtype)NULL;
    else if (stack->length = 1)
    {
        delData = stack->top->data;
        stack->top = NULL;
        stack->bottom = NULL;
        return delData;
    }
    else
    {
        pStackElem = stack->top;
        delData = stack->top->data;
        stack->top = stack->top->prev;
        stack->top->next = NULL;
        free(pStackElem);
        return delData;
    }
}

void StackFlip(Stack* stack)
{
    StackElem* pPtrBuf = NULL;
    StackElem* pStackElem = stack->bottom;
    pPtrBuf = stack->top;
    stack->top = stack->bottom;
    stack->bottom = stack->top;

    if (stack->length >= 2)
    {
        int idx = 0;
        for (idx = 0; idx < stack->length; idx++)
        {
            pPtrBuf = pStackElem->next;
            pStackElem->next = pStackElem->prev;
            pStackElem->prev = pPtrBuf;
            pStackElem = pStackElem->prev;
        }
    }
}

#endif