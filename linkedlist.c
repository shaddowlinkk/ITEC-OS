//
// Created by nathan on 1/21/2021.
//
#include <stdlib.h>
#include "SystemData.h"
node *newNode(Data item){
    node *newNode;
    newNode = (node *) malloc(sizeof (Data));
    newNode->item=item;
    newNode->next=NULL;
    return newNode;
}
void insertNode(node **head, node *newNode){
    node **trace = head;
    while ((*trace)){
        trace = &(*trace)->next;
    }
    newNode->next= *trace;
    *trace=newNode;
}
// need some work
void removeNode(node ** item){
    node *tmp =(*item);
    (*item)=(*item)->next;
    free(tmp);
}
#include "linkedlist.h"
