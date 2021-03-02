//
// Created by nathan on 1/21/2021.
// This file contains all functions for the linked list
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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


node *findNode(node **head,char name[11]){
    char targetName[8];
    strncpy(targetName,name,8);
    node **trace = head;
    char curName[8];
    if((*trace))
        strncpy(curName,(*trace)->item.dir->name,8);
    while ((*trace)&&(strcmp(targetName,curName)!=0)){
        trace = &(*trace)->next;
        if((*trace)) {
            strncpy(curName, (*trace)->item.dir->name, 8);
        }
    }
    return (*trace);
}
void listNodeNames(node **head){
    node **trace = head;
    while ((*trace)){
        printf("Filename: %s ",(*trace)->item.dir->name);
        char type =(*trace)->item.dir->name[strlen((*trace)->item.dir->name)-1];
        switch (type) {
            case 'p':
                printf(" Type: Program File\n");
                break;
            case 't':
                printf(" Type: Text File\n");
                break;
            case 'd':
                printf(" Type: Directory\n");
                break;
        }
        trace = &(*trace)->next;
    }
}
#include "linkedlist.h"
