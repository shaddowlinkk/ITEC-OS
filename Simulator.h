//
// Created by nathan on 3/25/2021.
//

#ifndef ITEC371_SIMULATOR_H
#define ITEC371_SIMULATOR_H
#include "linkedlist.h"
#define INIT_SIMULATION_ENVIRONMENT(X) SimEnviro X = {.time=0,.queue=NULL,.IO=NULL,.finished=NULL,.burst=0, .mem=0, .stop=0 ,.usemem=0}
#endif //ITEC371_SIMULATOR_H
void simrun(SimEnviro *enviro);
void stepTill(SimEnviro *enviro, int stopStep);
int getSysMem(node **head);
/*
void queueadd(node *data);
void setBurst(int data);*/
