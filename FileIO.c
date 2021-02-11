//
// Created by nathan on 1/19/2021.
// This File contatins all funxtions for File IO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemData.h"
#include "FileIO.h"



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
    printf("%li: Size of text File %i\n",ftell(file),(*pnode)->item.tfile->size);
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

//--------------------------------file reading (code ignore this)---------------------------------------------------//
void loadData(char *dirname,node *head,FILE *file);

char *getText(FILE *file, int size){
    char *text = (char *) malloc(size);
    for (int i=0;i<size;i++){
        fread(&text[i],sizeof(char),1,file);
    }
    return text;
}

void load_TextFile_data(FILE *file,Data *item){
    int size;
    fread(&size,sizeof(int),1,file);
    item->tfile->size=size;
    item->tfile->text=getText(file,size);
}

void load_ProgramFile_data(FILE *file,Data *item){
    fread(&item->pfile->cpu,sizeof(int),1,file);
    fread(&item->pfile->mem,sizeof(int),1,file);
}

void load_Dir_data(FILE *file,Data *item){
    fread(&item->dir->numFiles,sizeof(int),1,file);
    loadData(item->dir->name,item->dir->head,file);
}
 char *getEndDirName(char *name){
    char *endName = (char *) malloc(11);
    memset(endName,'\0',11);
    strcpy(endName,"End");
    for(int i =0;name[i]!='\0'||name[i]!='.'&& i<8;i++){
        endName[i+3]=name[i];
    }
     return endName;
}
void loadData(char *dirname,node *head,FILE *file) {
    //need a loop untill you get to dir end
    Data data;
    char name[11];
    memset(name, '\0', 11);
    char *end = getEndDirName(dirname);
    // data and name diff
    while (name != end) {
        fread(name, sizeof(name), 1, file);
        if (name[9] == 't') {
            strcpy(data.tfile->name, name);
            load_TextFile_data(file, &data);
        } else if (name[9] == 'p') {
            strcpy(data.pfile->name, name);
            load_ProgramFile_data(file, &data);
        } else if (name[9] == 'd') {
            strcpy(data.dir->name, name);
            load_Dir_data(file, &data);
        } else {
            printf("Error then reading name. data:%s ", name);
        }
    }
}
void loadFile(char *filename, node *head){
    FILE *file;
    file=fopen(filename,"rb");
    if(file==NULL){
        printf("file doesn't exist");
        exit(-2);
    }
    char name[11];
    fread(name,sizeof(name),1,file);
    loadData(name,head,file);


}
