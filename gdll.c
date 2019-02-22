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
	return;
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
    }
    printf("\n");
    while(node != NULL)
    {
        printf("CURRENT INDEX: %d\n", node->index);
        removeNode(node);
        node = node->prev;
    }
}

/*TEST FUNCTIONS*/
void printContents(struct GDLNode *gdll)
{
    while(gdll != NULL)
    {
        printf("[%#012x : %d]\n", gdll->val, gdll->index);
        gdll = gdll->next;
    }
    printf("\n");
}

void printVisual(struct GDLNode *gdll)
{
    printf("       NULL\n");
    while(gdll != NULL)
    {
        printf("        ^\n");
        printf("        |\n");
        printf("        v\n");
        printf("[%#012x : %d]\n", gdll->val, gdll->index);
        gdll = gdll->next;
    }
    printf("        ^\n");
    printf("        |\n");
    printf("        v\n");
    printf("       NULL\n");
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
    struct GDLNode *y = appendNode(nullN, "help");
    struct GDLNode *tail = appendNode(pthd, fp);
    printf("[%c, %s, %d, %p, %s, %p, %f]\n\n", head->val, head->next->val,
            head->next->next->val, head->next->next->next->val,
            nullN->next->val, y->next->val, pthd->next->val);
    printVisual(head);
    destroyList(head);
}

void custom()
{
    /*CUSTOM TESTS HERE*/
}

int main()
{
    int t;
    printf("GDLL TEST SUITE\n");
    printf("1 | test()\n");
    printf("2 | custom()\n");
    printf("OTHER | runtime test\n");
    printf("Please choose testing method: ");
    scanf("%d", &t);
    printf("\n");
    if(t == 1)
    {
        test();
        exit(0);
    }
    else if(t == 2)
    {
        custom();
        exit(0);
    }

    struct GDLNode *head = NULL;
    void *val;
    int cmd;
    printf("Starting GDLL Runtime Test \n");
    while(1)
    {
        printf("Enter a command (help for info): ");
        scanf("%d", &cmd);
        printf("\n");

        switch(cmd)
        {
            case(0):
                printf("'1c' : Create New Node\n");
                printf("'2a' : Append New Node\n");
                printf("'r' : Remove Node\n");
                printf("'4d' : Delete All Nodes\n");
                printf("'5p' : Print Contents\n");
                printf("'6v' : Print Visual\n");
                printf("'7q' : Quit Test Suite\n");
                break;
            case(1):
                printf("Enter val for head node: \n");
                scanf("%p", val);
                head = createNode(val);
                break;
            case(2):
                printf("Enter val for appended node: \n");
                scanf("%p", val);
                *appendNode(head, val);
                break;
            case(4):
                printf("Freeing all nodes.\n");
                destroyList(head);
                break;
            case(5):
                printContents(head);
                break;
            case(6):
                printVisual(head);
                break;
            case(7):
                exit(0);
                break;
        }
    }
}
