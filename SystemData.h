//
// Created by nathan on 1/19/2021.
// this file conntanes the structs for the system

#ifndef ITEC371_SYSTEMDATA_H
#define ITEC371_SYSTEMDATA_H
struct _node;
typedef struct _textFile{
    char name[11];
    int size;
    char *text;//needs freed
}TextFile;
/*typedef struct _programFile{
    char name[11];
    int cpu;
    int mem;
}ProgramFile;*/
typedef struct _directroy {
    char name[11];
    int numFiles;
    char *pwd;
    struct _node *head;
}Directroy;
typedef struct _simnode{
    char name[11];
    int time;
    int timeran;
    int mem;
    int timeStartIO;
    int timeNeedIO;
}SimNode;
typedef union _data{
    Directroy *dir;
   // ProgramFile *pfile;
    TextFile *tfile;
    SimNode *simNode;
}Data;
typedef struct _simenviro{
    int time;
    struct _node *queue;
    struct _node *IO;
    struct _node *finished;
    int burst;
    int mem;
    int usemem;
    int stop;
}SimEnviro;
typedef struct _node {
    Data item;
    struct _node *next;
}node;
#endif //ITEC371_SYSTEMDATA_H
