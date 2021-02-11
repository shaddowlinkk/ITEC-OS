//
// Created by nathan on 1/21/2021.
// This file contains all functions for the linked list
#include <stdlib.h>
#include "SystemData.h"
/**
 * This function isused to create a new node
 * @param item The data that is to be in the node
 * @return A pointer to the new node
 */
node *newNode(Data item){
    node *newNode;
    newNode = (node *) malloc(sizeof (Data));
    newNode->item=item;
    newNode->next=NULL;
    return newNode;
}
/**
 * this function is used to insert a node into the end of the list
 * @param head The head of a list to insert in to
 * @param newNode The node that you what to insert
 */
void insertNode(node **head, node *newNode){
    node **trace = head;
    while ((*trace)){
        trace = &(*trace)->next;
    }
    newNode->next= *trace;
    *trace=newNode;
}

// this function is deprecated and not used
void removeNode(node ** item){
    node *tmp =(*item);
    (*item)=(*item)->next;
    free(tmp);
}
#include "linkedlist.h"
