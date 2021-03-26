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
    newNode = (node *) malloc(sizeof (node));
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
/**
 * this function returnes the fist node and moves the head down one
 * @param head the head of th list that you want to mode
 * @return
 */
node *popnode(node **head){
    node *tmp=(*head);
    (*head)=(*head)->next;
    (*tmp).next=NULL;
    return (tmp);
}
/**
 *  this function is used to put a node at the begining of the list
 * @param head the head of the list that you want to add to
 * @param node the node that you want to add
 */
void pushToTop(node **head, node *node){
    node->next=(*head);
    (*head)=node;
}

/**
 * this function is used to search the linked list for the name of the file
 * @param head the head of the list that you want to search
 * @param name the name of the file that you are looking for
 * @return a pointer to that node so one can modify it
 */
node *findNode(node **head,char name[11]){
    char targetName[11];
    memset(targetName,'\0',11);
    strncpy(targetName,name,8);
    node **trace = head;
    char curName[11];
    memset(curName,'\0',11);

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
/**
 * this function list all that files that are in a dir linked list
 * @param head the head of the list that you want to list
 */
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