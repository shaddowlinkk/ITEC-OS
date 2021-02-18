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

//todo need to make it so that nameing format is constent
node *findNode(node **head,char name[11]){
    char targetName[8];
    strncpy(targetName,name,8);
    node **trace = head;
    char curName[8];
    strncpy(curName,(*trace)->item.dir->name,8);
    curName[strlen(curName)-1]='\0';
    curName[strlen(curName)-1]='\0';
    while ((*trace)&&(strcmp(targetName,curName)!=0)){
        trace = &(*trace)->next;
        strncpy(curName,(*trace)->item.dir->name,8);
        curName[strlen(curName)-1]='\0';
        curName[strlen(curName)-1]='\0';
    }
    return (*trace);
}
void listNodeNames(node **head){
    node **trace = head;
    while ((*trace)){
        printf("%s ",(*trace)->item.dir->name);
        trace = &(*trace)->next;
    }
    printf("\n");
}
#include "linkedlist.h"
