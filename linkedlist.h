//
// Created by nathan on 1/21/2021.
//

#ifndef ITEC371_LINKEDLIST_H
#define ITEC371_LINKEDLIST_H
#include "SystemData.h"
void removeNode(node ** item);
void insertNode(node **head, node *newNode);
node *newNode(Data item);
node *popnode(node **head);
void pushToTop(node **head, node *node);
void listNodeNames(node **head);
node *findNode(node **head,char name[11]);

#endif //ITEC371_LINKEDLIST_H
