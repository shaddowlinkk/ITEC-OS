//
// Created by nathan on 1/19/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SystemData.h"

#include "FileIO.h"


char *getText(FILE *file, int size){
    char *text = malloc(size);
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
    //
}

void loadData(char *dirname,node *head,FILE *file){
    //need a loop untill you get to dir end
    Data data;
    char name[11];
    fread(name,sizeof(name),1,file);
    if(name[9] == 't'){
        strcpy(data.tfile->name,name);
        load_TextFile_data(file,&data);
    }else if(name[9] == 'p'){
        strcpy(data.pfile->name,name);
        load_ProgramFile_data(file,&data);
    }else if(name[9] == 'd'){
        strcpy(data.dir->name,name);
        load_Dir_data(file,&data);
    }else{
        printf("Error then reading name. data:%s ",name);
    }

}
void loadFile(char *filename, node *head){
    FILE *file;
    file=fopen(filename,"rb");
    if(file==NULL){
        printf("file doesn't exist");
        exit(-2);
    }


}