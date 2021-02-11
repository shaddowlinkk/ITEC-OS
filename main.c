#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemData.h"
#include "linkedlist.h"
#include "FileIO.h"
#include "Utils.h"
// this file is the main running file


// tells when the program is done
int done=0;
int commandInput(node **head,char dname[10]);
/**
 * this function creates a text file for the linked list using the data union.
 * @param head The start the list that you are reading.
 * @param name The name of the file you want to make.
 */
void createTextFile(node **head,char name[10]){
    Data item;
    item.tfile=(TextFile *)malloc(sizeof (TextFile));
    char text[100];
    printf("Enter contents>");
    scanf("%s",text);
    item.tfile->text=(char *)malloc(strlen(text));
    strcpy(item.tfile->text,text);
    item.tfile->size=strlen(text);
    strcpy(item.tfile->name,name);
  //  return item;
    insertNode(head,newNode(item));
}
/**
 * This function create  program file for the linked lisk using the data union
 * @param head The start the list that you are reading.
 * @param name The name of the file you want to make.
 */
void createProgrameFile(node **head,char name[10]){
    Data item;
    item.pfile=(ProgramFile *)malloc(sizeof (ProgramFile));
    strcpy(item.pfile->name,name);
    printf("Enter CPU requirements>");
    item.pfile->cpu=getInt();
    printf("Enter memory requirements>");
    item.pfile->mem=getInt();
    insertNode(head,newNode(item));
}
/**
 * this funtion create a new directory node for the linked list it also makes the lest head for the dir list
 * @param head The start the list that you are reading.
 * @param name The name of the file you want to make.
 */
void createDir(node **head,char name[10]){
    Data item;
    item.dir=(Directroy *)malloc(sizeof (Directroy));
    strcpy(item.dir->name,name);
    item.dir->head=NULL;
    item.dir->numFiles=commandInput((node **)&item.dir->head,name);
    insertNode(head,newNode(item));
}
/**
 *  this function runs the shell for the directory that you are in.
 * @param head The start the list that you are reading.
 * @param dname the name of the directory that you are in
 * @return the file count of the directory
 */
int commandInput(node **head,char dname[10]){
    char command[50];
    int fileCount=0;
    while (1){
        if (done){
            return fileCount;
        }
        char name[11];
        memset(name,'\0', sizeof(name));
        printf("Command@%s>",dname);
        scanf("%s",command);
        getchar();
        //what to do the the CreatFile command and do something that for that file type
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
            //what to do for he Create Dir command
        }else if(strcmp(command,"CreateDir")==0){
            printf("Enter directory name>");
            getDirName(name);
            strcat(name,".d");
            //chacking that the .d got in the file name my need to remove
            while (name[strlen(name)-1]!='d'){
                printf("filename needs to end in .d\nEnter directory name>");
                memset(name,'\0', sizeof(name));
                getDirName(name);
                strcat(name,".d");
            }

            createDir(head,name);
            fileCount ++;
        }
            //what to do the the EndDir command
        else if(strcmp(command,"EndDir")==0){
            return fileCount;
        }
            //what to do the the quit command
        else if(strcmp(command,"quit")==0){
            done=1;
            return fileCount;
        }
    }

}
/*
 * the main
 */
int main(int argc, char **argv){
    //checking if there is a second arg
    if(argc>=2){
        FILE *file;
        // opening a file in wb
       file=fopen(argv[1],"wb");//rb+ <- not that?
        if (file==NULL){
            printf("no file by that name found creating file");
            file=fopen(argv[1],"wb");
        }

        // setting up the root dir
        node *start=NULL;
        Data root;
        root.dir=(Directroy *)malloc(sizeof(Directroy));
        char name[11]="root.d\0\0\0\0";
        strcpy(root.dir->name,name);
        root.dir->head=NULL;
        //start the shell for root dir
        root.dir->numFiles=commandInput(&root.dir->head,root.dir->name);
        insertNode(&start,newNode(root));

        //printing out put for the bin file
        printf("Binary file structure is:\n");
        //saving the file
        saveFile(file,&start);
    }else{
        // if now promp and ecit programe
        printf("%s","No file specified\n");
        exit(-2);
    }
}