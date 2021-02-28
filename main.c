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
node *start=NULL;
FILE *file;
void  commandInput(Data *dir,char dname[10]);
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
 * @param pwd The path of the directory that you are creating the new directory in
 */
void createDir(node **head,char name[10],char *pwd){
    Data item;
    item.dir=(Directroy *)malloc(sizeof (Directroy));
    strcpy(item.dir->name,name);

    //string manipulation to get the right pwd
    name[strlen(name)-1]='\0';
    name[strlen(name)-1]='\0';
    int pwdSize=strlen(name)+strlen(pwd);
    item.dir->pwd=malloc(pwdSize);
    strcpy(item.dir->pwd,pwd);
    strcat(item.dir->pwd,"\\");
    strcat(item.dir->pwd,name);

    item.dir->head=NULL;
    item.dir->numFiles=0;
    insertNode(head,newNode(item));
}
/**
 *  this function runs the shell for the directory that you are in.
 * @param dir The dir data obj of that  directory.
 * @param dname the name of the directory that you are in
 * @return the file count of the directory
 */
void commandInput(Data *dir,char dname[10]){
    node **head=&dir->dir->head;
    char command[50];
    int fileCount=0;
    while (1){
        dir->dir->numFiles = fileCount;
        if (done){
            dir->dir->numFiles=fileCount;
            return;
        }
        char name[11];
        memset(name,'\0', sizeof(name));
        printf("Command@%s>",dname);
        scanf("%s",command);
        getchar();
        //what to do the the CreatFile command and do something that for that file type
        if(strcmp(command,"CreateFile")==0){
            scanf("%s",name);
            if(checkNameComp(name)==0) {
                char filetypes = name[strlen(name) - 1];
                if (filetypes == 'p') {
                    createProgrameFile(head, name);
                } else if (filetypes == 't') {
                    createTextFile(head, name);
                }
                fileCount++;
            }else{
                printf("file name not right");
            }
            //what to do for he Create Dir command
        }else if(strcmp(command,"mkdir")==0){
            //printf("Enter directory name>");
            scanf("%s",name);
            if (checkNameComp(name) == 2 && strlen(name) <= 8) {
                strcat(name, ".d");
            }
            //chacking that the .d got in the file name my need to remove
            if(checkNameComp(name)==0) {
                createDir(head, name,dir->dir->pwd);
                fileCount++;
            }
        }else if(strcmp(command,"cat")==0){
            char sc[11];
            memset(sc,'\0', sizeof(sc));
            scanf("%s",sc);
            if (checkNameComp(sc) == 2 && strlen(sc) <= 8) {
                strcat(sc, ".t");
            }
            node *found=findNode(&dir->dir->head,sc);
            if(found)
                printf("%s\n",found->item.tfile->text);
        }else if(strcmp(command,"ls")==0){
            listNodeNames(&dir->dir->head);
        }else if(strcmp(command,"pwd")==0){
            printf("%s\n",dir->dir->pwd);
        }else if(strcmp(command,"printInfo")==0){
            printf("Binary file structure is:\n");
            fseek(file,0,SEEK_SET);
            saveFile(file,&start);//todo pull the print from the save
            fseek(file,0,SEEK_SET);
        }else if(strcmp(command,"cd")==0){
            char sc[11];
            memset(sc,'\0', sizeof(sc));
            scanf("%s",sc);
            if(strcmp(sc,"..")!=0) {
                if (checkNameComp(sc) == 2 && strlen(sc) <= 8) {
                    strcat(sc, ".d");
                }
                node *found = findNode(&dir->dir->head, sc);
                if (found)
                    commandInput(&found->item, found->item.dir->name);
            } else{
                if(strcmp(dir->dir->name,"root.d")!=0) {
                    dir->dir->numFiles = fileCount;
                    return;
                }
            }
        }
            //what to do the the quit command
        else if(strcmp(command,"quit")==0){
            done=1;
            dir->dir->numFiles=fileCount;
            return;
        }
    }

}
/*
 * the main
 */
int main(int argc, char **argv){
    //checking if there is a second arg
    Data root;
    root.dir=(Directroy *)malloc(sizeof(Directroy));
    if(argc>=2){
        // opening a file in wb
       file=fopen(argv[1],"rb+");//rb+ <- not that?
        if (file==NULL){
            file=fopen(argv[1],"wb");
            char name[11]="root.d\0\0\0\0";
            strcpy(root.dir->name,name);
            root.dir->head=NULL;
            root.dir->pwd= malloc(4);
            strcpy(root.dir->pwd,"root");
            //start the shell for root dir
            insertNode(&start,newNode(root));
            commandInput(&root, root.dir->name);
            //printing out put for the bin file
        }else{
            char name[11];
            fread(name,sizeof(name),1,file);
            name[4]=name[8];
            name[5]=name[9];
            name[8]='\0';
            name[9]='\0';
            load_Dir_data(&start,name,file);
            fseek(file,0,SEEK_SET);
            commandInput(&start->item,start->item.dir->name);
        }
        saveFile(file,&start);
        // setting up the root dir



        //saving the file
        //todo pull the prinf functionality from this function mabey not(maybe)
    }else{
        // if now promp and ecit programe
        printf("%s","No file specified\n");
        exit(-2);
    }
}