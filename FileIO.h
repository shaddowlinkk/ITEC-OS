//
// Created by nathan on 1/19/2021.
//

#ifndef ITEC371_FILEIO_H
#define ITEC371_FILEIO_H
//void loadFile(char *filename, node *head);
void load_Dir_data(node **head,char name[10],FILE *file,char *pwd);
void saveFile(FILE *file, node **head);
#endif //ITEC371_FILEIO_H
