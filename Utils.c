//
// Created by nathan on 1/26/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFF_LEN 100
#include "Utils.h"
int getInt(){
    char *p ,buff[MAX_BUFF_LEN];
    long data;
    while(fgets(buff,sizeof(buff),stdin)){
        data = strtol(buff,&p,10);
        if(p==buff||*p!='\n'){
            printf("you didn't enter just a integer plz try again\nReenter integer>");
        }else break;
    }
// sending the number back to the caller as a  integer
    return data;
}

void getName(char name[10]) {
    static char tmp[10];
    char *filetypes = "tpd";
    int complete=0;
    do {
        complete=1;
        fflush(stdin);
        fgets(tmp, 10, stdin);
        if (tmp[strlen(tmp) - 1] != '\n') {
            int count = 0;
            while (fgetc(stdin) != '\n')
                count++;
            if (count > 0) {
                printf("file name to big\nReenter name>");
                complete=0;
            }

        }
        if(strlen(tmp)<=3){
            printf("no name or file name to small\nReenter name>");
            complete=0;
        }
        if((strchr(filetypes, tmp[strlen(tmp) - 2]) == NULL) || (tmp[strlen(tmp)-3]!='.')) {
            printf("file name not right\nReenter name>");
            complete = 0;
        }
    } while (!complete);
    tmp[strlen(tmp)-1]='\0';
    strcpy(name,tmp);
}