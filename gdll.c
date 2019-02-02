#include <stdio.h>
#include <stdlib.h>
#include "gdll.h"

struct GDLNode* createNode(void *val)
{
    struct GDLNode *newnode = (struct GDLNode*) malloc(sizeof(struct GDLNode));
    newnode->index = 0;
    newnode->val = val;
    newnode->prev = NULL;
    newnode->next = NULL;
    newnode->head = &newnode;
    return newnode;
}

unsigned int updateIndex(struct GDLNode *node)
{
    unsigned int i = 0;
    while(node->prev != NULL)
    {
        node = node->prev;
        i++;
    }
    return i;
}

struct GDLNode* appendNode(struct GDLNode *node, void *val)
{
    struct GDLNode *newnode = (struct GDLNode*) malloc(sizeof(struct GDLNode));
    newnode->val = val;

    if(node->next != NULL)
    {
        newnode->next = node->next;
        node->next->prev = newnode;
        node->next = newnode;
        newnode->prev = node;
        newnode->head = node->head;
        newnode->index = updateIndex(newnode);
        newnode->next->index = newnode->index + 1;
    }
    else
    {
        node->next = newnode;
        newnode->prev = node;
        newnode->next = NULL;
        newnode->head = node->head;
        newnode->index = node->index + 1;
    }
    return newnode;
}

void removeNode(struct GDLNode *node)
{
    if(node->next != NULL) 
    {
        node->prev->next = NULL;
        node->prev->next = node->next;
        node->next->prev = NULL;
        node->next->prev = node->prev;
        printf("FREE: %p : %d\n", node, node->index);
    }
    else if(&node == node->head)
    {
        free(node);
    }
    else
    {
        if(node->prev != NULL)
        {
            node->prev->next = NULL;
        }
        printf("FREE: %p : %d\n", node, node->index);
    }
    updateIndex(node);
    free(node);
}

void destroyList(struct GDLNode *node)
{
    while(node->next != NULL)
    {
        node = node->next;
        printf("%p : %d\n", node, node->index);
    }
    printf("\n");
    while(node != NULL)
    {
        printf("%p : %d\n", node, node->index);
        removeNode(node);
        node = node->prev;
    }
}

void printContents(struct GDLNode *gdll)
{
    while(gdll != NULL)
    {
        printf("[%p : %d]\n", gdll->val, gdll->index);
        gdll = gdll->next;
    }
    printf("\n");
}

/*TESTS*/
void test()
{
    float f = 60.5;
    float *fp = &f;
    struct GDLNode *head = createNode('a');
    struct GDLNode *integerN = appendNode(head, 8);
    struct GDLNode *strN = appendNode(head, "string");
    struct GDLNode *nullN = appendNode(integerN, NULL);
    struct GDLNode *pthd = appendNode(nullN, nullN->head);
    struct GDLNode *tail = appendNode(pthd, fp);
    printf("%d\n", sizeof(head));
    printf("Index: %d\n", integerN->index);
    printf("[%c, %s, %d, %p, %p, %f]\n\n", head->val, head->next->val,
            head->next->next->val, head->next->next->next->val, 
            nullN->next->val, pthd->next->val);
    
    printContents(head);
    destroyList(head);
    
    /*
    removeNode(tail);
    printContents(head);
    removeNode(pthd);
    printContents(head);
    removeNode(nullN);
    printContents(head);
    removeNode(integerN);
    printContents(head);
    removeNode(strN);
    printContents(head);
    removeNode(head);
    */

    /*
    free(tail);
    free(pthd);
    free(nullN);
    free(strN);
    free(integerN);
    free(head);
    */
    //destroyList(head);
    //printf("%c\n", head->*head->val);
}
/*
void test2()
{
    struct GLDNode *n = createNode('$');
    struct GLDNode *nn = appendNode(n, "head_addr:");

    printf("%s %p\n", nn->val, nn->head);

    free(nn);
    free(n);
}
*/

void testrem()
{
    struct GDLNode *head = createNode('a');
    struct GDLNode *integerN = appendNode(head, 8);
    struct GDLNode *strN = appendNode(head, "string");
    struct GDLNode *nullN = appendNode(integerN, 7777777);

    printContents(head);
    printf("\n");
    removeNode(strN);
    printContents(head);
}

int main()
{
    test();
}
