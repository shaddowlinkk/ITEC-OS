//
// Created by nathan on 1/19/2021.
// This File contatins all funxtions for File IO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemData.h"
#include "FileIO.h"
#include "linkedlist.h"



//--------------------------------file saving code ------------------------------------------------------------//

/**
 * writes the file name to the bin file
 * @param file The file descriptor to save to
 * @param filename The name of the file
 * @param type The type of the file
 */
void writeName(FILE *file,char filename[11],char type){
    char name[11];
    memset(name,'\0', sizeof(name));
    memcpy(name,filename,strlen(filename)-2);
    name[8]='.';
    name[9]=type;
    fwrite(name,11,1,file);
}
/**
 * writes the End dir to the bin file
 * @param file The file descriptor to save to
 * @param filename The name of the dir
 */
void writeEndDir(FILE *file,char filename[11]){
    //temp vars for string manip
    char end[11];
    char name[8];
    memset(name, '\0', 8);
    memset(end,'\0',11);
    memcpy(name, filename, strlen(filename) - 2);
    strcpy(end,"End");
    strcat(end, name);
    fwrite(end,sizeof(end),1,file);

}
/**
 * writes the data in a dir to bin file
 * @param file The file descriptor to save to
 * @param pnode a pointer to a node of the dir
 */
void write_dir_data(FILE *file,node **pnode){
    printf("%li: Directory %s\n",ftell(file),(*pnode)->item.dir->name);
    writeName(file, (*pnode)->item.dir->name, 'd');
    printf("%li: Directory %s contains %i file/dir\n", ftell(file), (*pnode)->item.dir->name, (*pnode)->item.dir->numFiles);
    fwrite(&(*pnode)->item.dir->numFiles, sizeof(int), 1, file);
    saveFile(file,&(*pnode)->item.dir->head);
    printf("%li: End of Directory %s\n",ftell(file),(*pnode)->item.dir->name);
    writeEndDir(file,(*pnode)->item.dir->name);

}
/**
 *
 * writes the data in a test file to bin file
 * @param file The file descriptor to save to
 * @param pnode A pointer to a node of the dir
 */
void write_text_data(FILE *file,node **pnode){
    printf("%li: Filename %s\n",ftell(file),(*pnode)->item.dir->name);
    printf("Type: text file\n");
    writeName(file, (*pnode)->item.tfile->name, 't');
    printf("%li: Size of text File %i byte\n",ftell(file),(*pnode)->item.tfile->size);
    fwrite(&(*pnode)->item.tfile->size, sizeof(int), 1, file);
    char text[(*pnode)->item.tfile->size];
    memcpy(text, (*pnode)->item.tfile->text, (*pnode)->item.tfile->size);
    printf("%li: Content of text File %s\n",ftell(file),(*pnode)->item.tfile->text);
    fwrite(text, sizeof(text),1,file);
}
/**
 *
 * writes the data in a prog file to bin file
 * @param file The file descriptor to save to
 * @param pnode A pointer to a node of the dir
 */
void write_porg_data(FILE *file,node **pNode){
    printf("%li: Filename %s\n",ftell(file),(*pNode)->item.dir->name);
    printf("Type: program file\n");
    writeName(file, (*pNode)->item.tfile->name, 'p');
    printf("%li: Contents: CPU Requirement: %d,Memory Requirement:%i\n", ftell(file), (*pNode)->item.pfile->cpu, (*pNode)->item.pfile->mem);
    fwrite(&(*pNode)->item.pfile->cpu, sizeof(int), 1, file);
    fwrite(&(*pNode)->item.pfile->mem, sizeof(int), 1, file);
}
/**
 * saves the data of a dir to a bin file
 * @param file The file to save to
 * @param head A pointer to the begining of the list
 */
void saveFile(FILE *file, node **head){
    for(;(*head);head=&(*head)->next){
        char type = (*head)->item.dir->name[strlen((*head)->item.dir->name)-1];
        if (type=='d')
            write_dir_data(file,head);
        else if (type=='t')
            write_text_data(file,head);
        else if (type=='p')
            write_porg_data(file,head);
        else
            printf("error file type %c not valid",type);
    }

}

void loadData(char *dirname,node **head,FILE *file,char *pwd);
/**
 * this function unpads the name that you get from reading the file
 * @param name the name that you want to unpad
 */
void fixname(char name[11]){
    char t1,t2;
    t1=name[8];
    t2=name[9];
    name[8]='\0';
    name[9]='\0';
    name[strlen(name)]=t1;
    name[strlen(name)]=t2;
}
/**
 * this function is used to get the contence from a file for a text file
 * @param file the file to read from
 * @param size the size of the contents to get
 * @return a string of the contents of the file
 */
char *getText(FILE *file, int size){
    char *text = (char *) malloc(size);
    memset(text,'\0',sizeof(size));
    for (int i=0;i<size;i++){
        char tmp='\0';
        fread(&tmp,sizeof(char),1,file);
        strncat(text,&tmp,1);
    }
    return text;
}
/**
 * this function reads in the data from a file if the next data is a text file
 * @param head the list you want to store in
 * @param name the name of the text file
 * @param file the file you want to read from
 */
void load_TextFile_data(node **head,char name[10],FILE *file){
    Data item;
    item.tfile=(TextFile *)malloc(sizeof (TextFile));
    int i= ftell(file);
    fread(&item.tfile->size,sizeof(int),1,file);
    item.tfile->text=(char *)malloc(item.tfile->size);
    strcpy(item.tfile->text,getText(file,item.tfile->size));
    strcpy(item.tfile->name,name);
    insertNode(head,newNode(item));
}
/**
 * this function reads in the data from a file if the next data is a program file
 * @param head the list you want ti store in
 * @param name  the name of the prog file
 * @param file the file to read from
 */
void load_ProgramFile_data(node **head,char name[10],FILE *file){
    Data item;
    item.pfile=(ProgramFile *)malloc(sizeof (ProgramFile));
    strcpy(item.pfile->name,name);
    fread(&item.pfile->cpu,sizeof(int),1,file);
    fread(&item.pfile->mem,sizeof(int),1,file);
    insertNode(head,newNode(item));
}
/**
 * this function reads in the data from a file if the next data is a dir
 * @param head the list you want to store in
 * @param name the name of the dir
 * @param file the file to read from
 */
void load_Dir_data(node **head,char name[10],FILE *file,char *pwd){
    Data item;
    item.dir=(Directroy *)malloc(sizeof (Directroy));
    fread(&item.dir->numFiles,sizeof(int),1,file);
    strcpy(item.dir->name,name);
    item.dir->head=NULL;
    name[strlen(name)-1]='\0';
    name[strlen(name)-1]='\0';
    int pwdSize=strlen(name)+strlen(pwd);
    item.dir->pwd=(char *)malloc(pwdSize);
    strcpy(item.dir->pwd,pwd);
    strcat(item.dir->pwd,"\\");
    strcat(item.dir->pwd,name);
    loadData(name,&item.dir->head,file,item.dir->pwd);
    insertNode(head,newNode(item));
}
/**
 * get the enddir tag for a dir name
 * @param name name of dir
 * @return the end dir tag
 */
char *getEndDirName(char *name){
    char *endName = (char *) malloc(11);
    memset(endName,'\0',11);
    strcpy(endName,"End");
    for(int i =0;name[i]!='\0'&&name[i]!='.'&& i<8;i++){
        endName[i+3]=name[i];
    }
    return endName;
}
/**
 * this function is used to get all the data in a dir
 * @param dirname then name if the dir that you are in
 * @param head the linked list that you what to add the data to
 * @param file the file you are reading from
 */
void loadData(char *dirname,node **head,FILE *file,char *pwd) {
    //need a loop untill you get to dir end
    Data data;
    char name[11];
    memset(name, '\0', 11);
    char *end = getEndDirName(dirname);
    // data and name diff
    fread(name, sizeof(name), 1, file);
    while (strcmp(name,end)!=0) {
        if (name[9] == 't') {
            fixname(name);
            load_TextFile_data( head,name,file);
        } else if (name[9] == 'p') {
            fixname(name);
            load_ProgramFile_data(head,name,file);
        } else if (name[9] == 'd') {
            fixname(name);
            load_Dir_data(head,name,file,pwd);
        } else {
            printf("Error then reading name. data:%s\n", name);
        }
        fread(name, sizeof(name), 1, file);
    }
}
/*void loadFile(char *filename, node *head){
    FILE *file;
    file=fopen(filename,"rb+");
    if(file==NULL){
        printf("file doesn't exist");
        exit(-2);
    }
    char name[11];
    fread(name,sizeof(name),1,file);
    loadData(name,head,file);


}*/
