// File: gdll.h
// Author: Alex Barney
//
// Description: Header file defining generic doubly linked data structure

// Struct: GDLNode
// Version: gdll_0.1.23
//
// Description: Doubly Linked Data Structure that
struct GDLNode
{
    unsigned int index; // Index of node in list
    struct GDLNode *prev; // Pointer to previous node : NULL if head
    struct GDLNode *next; // Pointer to next node : NULL if tail
    struct GDLNode **head; // Pointer to the address of the head of the list
    void *val; // Void Pointer to the value stored in the list
};

// Function: createNode
//
// Description: Instantiates a head node with no linked nodes
struct GDLNode* createNode(void *val);

// Function: appendNode
//
// Description: Instantiates a new node and links it to the next
//              position of the node passed in
struct GDLNode* appendNode(struct GDLNode *node, void *val);


///////////////////////////////////////////////////////////////////////////////
/*------------------------------NEED TO BE TESTED----------------------------*/
///////////////////////////////////////////////////////////////////////////////

// Function: removeNode
//
// Description: Removes and frees a node from the linked structure and 
//              reconstructs the data structure
void removeNode(struct GDLNode *node);

void destroyList(struct GDLNode *node);

///////////////////////////////////////////////////////////////////////////////
/*-------------------------------HELPERFUNCTIONS-----------------------------*/
///////////////////////////////////////////////////////////////////////////////

// Function: updateIndex
//
// Description: Updates the position of a GDLNode in the sequence linked to
unsigned int updateIndex(struct GDLNode *node);
