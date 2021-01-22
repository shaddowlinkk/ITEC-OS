//
// Created by nathan on 1/19/2021.
//

#ifndef ITEC371_SYSTEMDATA_H
#define ITEC371_SYSTEMDATA_H
typedef struct _textFile{
    char name[11];
    int size;
    char *text;
}TextFile;
typedef struct _programFile{
    char name[11];
    int cpu;
    int mem;
}ProgramFile;
typedef struct _directroy {
    char name[11];
    int size;
    //node point but cant declare
    void *head;
}Directroy;
typedef union _data{
    Directroy *dir;
    ProgramFile *pfile;
    TextFile *tfile;
}Data;


typedef struct _node {
    Data item;
    struct _node *next;
}node;
#endif //ITEC371_SYSTEMDATA_H
