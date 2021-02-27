//
// Created by nathan on 1/26/2021.
//
// This file contains all of the code for utility functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFF_LEN 100
#include "Utils.h"
// need to handle \r\n better
/**
 * this make is so the user can only input integers
 * @return the integer the user entered
 */
int getInt(){
    //buffers
    char *p ,buff[MAX_BUFF_LEN];
    // the integer that we get
    long data;
    //whare we get the int
    while(fgets(buff,sizeof(buff),stdin)){
        data = strtol(buff,&p,10);
        if(p==buff||*p!='\n'){
            printf("you didn't enter just a integer plz try again\nReenter integer>");
        }else break;
    }
// sending the number back to the caller as a  integer
    return data;
}
/**
 * this functions make sure that names of files are compliant with what is expected
 * @param name the name that needs to be checked
 * @return whare it failed or 0 if the name is compliant
 */
int checkNameComp(char name[11]){
    char filetypes[3] = {'t','p','d'};
    int results=-1;
    char tmp[11];
    memset(tmp,'\0',sizeof(tmp));
    strcpy(tmp,name);
     if(strlen(tmp) <= 3){
        memset(tmp, '\0', sizeof(tmp));
         return 1;
    }
        //check the file type ie .t is a valid type
    else if((strchr(filetypes, tmp[strlen(tmp) - 1]) == NULL) || (tmp[strlen(tmp) - 2] != '.')) {
        memset(tmp, '\0', sizeof(tmp));
         return 2;
    }
    return 0;
}

//------------------------------ these functions have deprecated and should not be used-------------------------------//
void getName(char name[10]) {
    static char tmp[12];
    memset(tmp,'\0',sizeof(tmp));
    char filetypes[3] = {'t','p','d'};
    int complete=0;
    do {
        complete=1;
        fflush(stdin);
        fgets(tmp, 11, stdin);
        if (tmp[strlen(tmp) - 1] != '\n') {
            int count = 0;
            char next = fgetc(stdin);
            while  (next != '\n' && next != '\r') {
                next = fgetc(stdin);
                count++;
            }
            //checking the size is to big
            if (count > 0) {
                printf("file name to big\nReenter name>");
                memset(tmp,'\0',sizeof(tmp));
                complete=0;
            }else{
                strcat(tmp,"\n");
            }

        }
        if(tmp[strlen(tmp) - 2] == 0x0d){
            int blen=strlen(tmp);
            tmp[strlen(tmp) - 2]='\n';
            tmp[strlen(tmp) - 1]='\0';
            int len=strlen(tmp);
        }
        //checking the file name is not to small
        else if(strlen(tmp)<=3){
            memset(tmp,'\0',sizeof(tmp));
            printf("no name or file name to small\nReenter name>");
            complete=0;
        }
        //check the file type ie .t is a valid type
        else if((strchr(filetypes, tmp[strlen(tmp) - 2]) == NULL) || (tmp[strlen(tmp)-3]!='.')) {
            memset(tmp,'\0',sizeof(tmp));
            printf("file name not right\nReenter name>");
            complete = 0;
        }
    } while (!complete);
    tmp[strlen(tmp)-1]='\0';
    strcpy(name,tmp);
}

/**
 * this is where we are getting the name of a dir
 * @param name The array that the name is stored in
 */
void getDirName(char name[8]) {
    static char tmp[10];
    memset(tmp,'\0',sizeof(tmp));
    int complete=0;
    do {
        complete=1;
        fflush(stdin);
        fgets(tmp, 9, stdin);
        if (tmp[strlen(tmp) - 1] != '\n') {
            int count = 0;
            while (fgetc(stdin) != '\n')
                count++;
            //checking the size is to big
            if (count > 0) {
                printf("file name to big\nReenter name>");
                memset(tmp,'\0',sizeof(tmp));
                complete=0;
            }else{
                strcat(tmp,"\n");
            }

        }
    } while (!complete);
    tmp[strlen(tmp)-1]='\0';
    strcpy(name,tmp);
}