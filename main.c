#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemData.h"
#include "linkedlist.h"

int commandInput(node **head);

void getName(char name[10]){
    static char tmp[10];
    fflush(stdin);
    fgets(tmp,10,stdin);
    if(tmp[strlen(tmp)-1]!='\n'){
        int count=0;
        while (fgetc(stdin) != '\n')
            count++;
        if (count>0){
            printf("file name to big");
        }
    }
    tmp[strlen(tmp)-1]='\0';
    strcpy(name,tmp);
}

void createTextFile(node **head,char name[10]){
    Data item;
    item.tfile=malloc(sizeof (TextFile));
    char text[100];
    printf("Enter contents>");
    scanf("%s",text);
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
    scanf("%d",&item.pfile->cpu);
    printf("Enter memory requirements>");
    scanf("%d",&item.pfile->mem);
    insertNode(head,newNode(item));
}

void createDir(node **head,char name[10]){
    Data item;
    item.dir=malloc(sizeof (Directroy));
    strcpy(item.dir->name,name);
    item.dir->head=NULL;
    item.dir->numFiles=commandInput((node **)&item.dir->head);
    insertNode(head,newNode(item));
}

int commandInput(node **head){
    char command[50];
    int fileCount=0;
    while (1){
        char name[10];
        printf("Command>");
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
            createDir(head,name);
            fileCount ++;
        }
        else if(strcmp(command,"Enddir")==0){
            return fileCount;
        }
        else if(strcmp(command,"quit")==0){
            // todo need to end better
            exit(0);
        }
    }

}

int main(int argc, char **argv){
    //checking if thare is a secone arg to reage
    if(argc>=2){
        FILE *file;
       file=fopen(argv[1],"rb+");
        if (file==NULL){
            printf("no file by that name found creating file");
            file=fopen(argv[1],"wb");
        }
        Data root;
        root.dir=malloc(sizeof(Directroy));
        char name[6]="root.d";
        strcpy(root.dir->name,name);
        root.dir->head=NULL;
        root.dir->numFiles=commandInput(&root.dir->head);
        printf("print:%s:%s",root.dir->head->item.dir->name,root.dir->head->item.dir->head->item.tfile->name);
    }else{
        // if now promp and ecit programe
        printf("%s","No file specified\n");
        exit(-2);
    }
}