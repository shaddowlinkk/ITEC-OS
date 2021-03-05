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
    item.dir->pwd=(char *)malloc(pwdSize);
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
    int fileCount=dir->dir->numFiles;
    while (1){
        dir->dir->numFiles = fileCount;
        if (done){
            dir->dir->numFiles=fileCount;
            return;
        }
        char name[11];
        memset(name,'\0', sizeof(name));
        printf("Command@%s>",dname);
        fflush(stdin);
        scanf("%s",command);
        getchar();
        //what to do the the CreatFile command and do something that for that file type
        //todo remove ability to make dupe files
        if(strcmp(command,"createFile")==0){
            scanf("%s",name);
            if(!(findNode(&dir->dir->head,name))) {
                if (checkNameComp(name) == 0) {
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
            }else{
                printf("file already exist\n");
            }
            //what to do for the mkdir command
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
            //what to do for the cat command
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
            //what to do for the run command
        }else if(strcmp(command,"run")==0){
            char sc[11];
            memset(sc,'\0', sizeof(sc));
            scanf("%s",sc);
            if (checkNameComp(sc) == 2 && strlen(sc) <= 8) {
                strcat(sc, ".p");
            }
            node *found=findNode(&dir->dir->head,sc);
            if(found)
                printf("running program %s\n",found->item.pfile->name);
            //what to do for the start command
        }else if(strcmp(command,"start")==0){
            char sc[11];
            memset(sc,'\0', sizeof(sc));
            scanf("%s",sc);
            if (checkNameComp(sc) == 2 && strlen(sc) <= 8) {
                strcat(sc, ".p");
            }
            node *found=findNode(&dir->dir->head,sc);
            if(found)
                printf("starting program %s\n",found->item.pfile->name);
            //what to do for the step command
        }else if(strcmp(command,"step")==0){
            char sc[11];
            memset(sc,'\0', sizeof(sc));
            scanf("%s",sc);
            if (checkNameComp(sc) == 2 && strlen(sc) <= 8) {
                strcat(sc, ".p");
            }
            node *found=findNode(&dir->dir->head,sc);
            if(found)
                printf("stepinging program %s\n",found->item.pfile->name);
            //what to do for the ls command
        }else if(strcmp(command,"ls")==0){
            printf("Directory name:%s\n",dir->dir->name);
            listNodeNames(&dir->dir->head);
            //what to do for the pwd command
        }else if(strcmp(command,"pwd")==0){
            printf("%s\n",dir->dir->pwd);
            //what to do for the printInfo command
        }else if(strcmp(command,"printInfo")==0){
            printf("Binary file structure is:\n");
            fseek(file,0,SEEK_SET);
            saveFile(file,&start);
            fseek(file,0,SEEK_SET);
            //what to do for the cd command
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
        }else{
            printf("no such command as %s\n",command);
        }
    }

}
/**
 * this funtion is used for when now file name exist or the file is empty
 * @param argv the command line args
 */
void newData(char **argv){
    Data root;
    root.dir=(Directroy *)malloc(sizeof(Directroy));
    file=fopen(argv[1],"wb");
    char name[11]="root.d\0\0\0\0";
    strcpy(root.dir->name,name);
    root.dir->head=NULL;
    root.dir->pwd= (char *) malloc(4);
    strcpy(root.dir->pwd,"\\root");
    //start the shell for root dir
    insertNode(&start,newNode(root));
    commandInput(&root, root.dir->name);
}
/*
 * the main
 */
int main(int argc, char **argv){
    //checking if there is a second arg

    if(argc>=2){
        // opening a file in wb
       file=fopen(argv[1],"rb+");//rb+ <- not that?
        if (file==NULL){
            newData(argv);
        }else {
            fseek(file, 0, SEEK_END);
            if (ftell(file) != 0) {
                fseek(file, 0, SEEK_SET);
                char name[11];
                fread(name, sizeof(name), 1, file);
                name[4] = name[8];
                name[5] = name[9];
                name[8] = '\0';
                name[9] = '\0';
                load_Dir_data(&start, name, file, "");
                fseek(file, 0, SEEK_SET);
                commandInput(&start->item, start->item.dir->name);
            }else{
                newData(argv);
            }
        }
        fclose(stdout);
            saveFile(file, &start);
    }else{
        // if now promp and ecit programe
        printf("%s","No file specified\n");
        exit(-2);
    }
}