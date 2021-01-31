#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemData.h"
#include "linkedlist.h"
#include "FileIO.h"
#include "Utils.h"
int done=0;
int commandInput(node **head,char dname[10]);

void createTextFile(node **head,char name[10]){
    Data item;
    item.tfile=malloc(sizeof (TextFile));
    char text[100];
    printf("Enter contents>");
    scanf("%s",text);
    item.tfile->text=malloc(strlen(text));
    strcpy(item.tfile->text,text);
    item.tfile->size=strlen(text);
    strcpy(item.tfile->name,name);
  //  return item;
    insertNode(head,newNode(item));
}

void createProgrameFile(node **head,char name[10]){
    Data item;
    item.pfile=malloc(sizeof (ProgramFile));
    strcpy(item.pfile->name,name);
    printf("Enter CPU requirements>");
    item.pfile->cpu=getInt();
    printf("Enter memory requirements>");
    item.pfile->mem=getInt();
    insertNode(head,newNode(item));
}

void createDir(node **head,char name[10]){
    Data item;
    item.dir=malloc(sizeof (Directroy));
    strcpy(item.dir->name,name);
    item.dir->head=NULL;
    item.dir->numFiles=commandInput((node **)&item.dir->head,name);
    insertNode(head,newNode(item));
}

int commandInput(node **head,char dname[10]){
    char command[50];
    int fileCount=0;
    while (1){
        if (done){
            return fileCount;
        }
        char name[10];
        memset(name,'\0', sizeof(name));
        printf("Command@%s>",dname);
        scanf("%s",command);
        if(strcmp(command,"CreateFile")==0){
            printf("Enter filename>");
            getName(name);
            char filetypes = name[strlen(name)-1];
            if(filetypes=='p'){
                createProgrameFile(head,name);
            }else if(filetypes=='t'){
                createTextFile(head,name);
            }
            fileCount ++;
        }else if(strcmp(command,"CreateDir")==0){
            printf("Enter directory name>");
            getName(name);
            while (name[strlen(name)-1]!='d'){
                printf("filename needs to end in .d\nEnter directory name>");
                getName(name);
            }
            createDir(head,name);
            fileCount ++;
        }
        else if(strcmp(command,"Enddir")==0){
            return fileCount;
        }
        else if(strcmp(command,"quit")==0){
            done=1;
            return fileCount;
        }
    }

}

int main(int argc, char **argv){
    //checking if thare is a secone arg to reage
    if(argc>=2){
        FILE *file;
       file=fopen(argv[1],"wb");//rb+ <- not that?
        if (file==NULL){
            printf("no file by that name found creating file");
            file=fopen(argv[1],"wb");
        }
        node *start=NULL;
        Data root;
        root.dir=malloc(sizeof(Directroy));
        char name[10]="root.d\0\0\0\0";
        strcpy(root.dir->name,name);
        root.dir->head=NULL;
        root.dir->numFiles=commandInput(&root.dir->head,root.dir->name);
        insertNode(&start,newNode(root));
        saveFile(file,&start);
    }else{
        // if now promp and ecit programe
        printf("%s","No file specified\n");
        exit(-2);
    }
}