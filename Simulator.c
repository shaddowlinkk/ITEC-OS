//
// Created by nathan on 3/25/2021.
//

#include "Simulator.h"
#include <stdio.h>
/*int time=0;
node *queue=NULL;
node *IO=NULL;
node *finished=NULL;
int burst=0;*/

node **findFinishIO(node **head,int systime);
node **findStartIO(node **head,int timeIO);
void printReport(node *working,SimEnviro *enviro);
void checkFinishdeIO(SimEnviro *enviro);
int getSysMem(node **head){
    node *last;
    node **tracer= head;
    while ((*tracer)){
        if((*tracer)->item.simNode->inVMem==0){
            last=(*tracer);
        }
        tracer=&(*tracer)->next;
    }
    last->item.simNode->inVMem=1;
    return last->item.simNode->mem;
}
/**
 * this runs on burst to keep track of time
 * @param working the node to be worked on
 * @param enviro the simulaion environment that you are runnning in
 * @param stopStep the time setp that you want to stop at or -1 to ru  thrue
 */
void runburst(node *working, SimEnviro *enviro,int stopStep){
    printReport(working,enviro);
    int memGet=0;
    if(working&&working->item.simNode->inVMem==1) {
        while ((enviro->usemem - working->item.simNode->mem) < 0) {
            enviro->usemem += getSysMem(&enviro->queue);
        }
        working->item.simNode->inVMem = 0;
        enviro->usemem -= working->item.simNode->mem;
        memGet = 2;
    }
    for (int i = 0; i < enviro->burst; ++i) {
        if(working&&(memGet==0)) {
            if (working->item.simNode->timeran == working->item.simNode->timeStartIO) {
                working->item.simNode->timeNeedIO += enviro->time;
                working->item.simNode->timeStartIO=-1;
                insertNode(&enviro->IO, working);
                working = NULL;
                return;
            }
            if(enviro->time>=stopStep&&stopStep!=-1){
                if (working->item.simNode->time != working->item.simNode->timeran) {
                    pushToTop(&enviro->queue,working);
                    enviro->stop=1;
                }
                return;
            }
            working->item.simNode->timeran++;
            enviro->time++;

            if (working->item.simNode->time == working->item.simNode->timeran) {
                working->item.simNode->time = enviro->time;
                insertNode(&enviro->finished, working);
                enviro->usemem+=working->item.simNode->mem;
                //printf("\tfinished:%s<%d>",working->item.simNode->name,enviro->time);
                working = NULL;
                return;
            }
        }else{
            if(memGet!=0)
                memGet--;
            enviro->time++;
        }
        node **found=findFinishIO(&enviro->IO,enviro->time);
        while ((*found)){
            node *tmp=(*found);
            (*found)=(*found)->next;
            insertNode(&enviro->queue,tmp);
            if(!working){
                return;
            }
        }

    }
    if(working)
        insertNode(&enviro->queue,working);
    working=NULL;
    //printf("\n");
}
/**
 * this fuctuin runs burst till it reaches the stop time
 * @param enviro the enviroment that you want to run
 * @param stopStep the time to stop
 */
void stepTill(SimEnviro *enviro, int stopStep){
    node *working;
    while (enviro->queue||enviro->IO) {
        if(enviro->queue) {
            working = popnode(&enviro->queue);
        }
        //add print out here will need to be a method
        runburst(working,enviro,stopStep);
        working=NULL;
        if(enviro->stop==1){
            enviro->stop=0;
            return;
        }
    }

    printReport(working,enviro);
    enviro->time=0;
    enviro->stop=0;
    enviro->queue=NULL;
    enviro->IO=NULL;
    enviro->finished=NULL;
    enviro->usemem=enviro->mem;
}
/**
 * this function runnes the enviroment to the end
 * @param enviro the enviroment that you want to run
 */
void simrun(SimEnviro *enviro){
    stepTill(enviro,-1);
    enviro->time=0;
    enviro->stop=0;
    enviro->queue=NULL;
    enviro->IO=NULL;
    enviro->finished=NULL;
    enviro->usemem=enviro->mem;
}
/*void checkFinishdeIO(SimEnviro *enviro){

}
node **findStartIO(node **head,int timeIO){

    node **trace = head;
    while ((*trace)&& (*trace)->item.simNode->timeStartIO != timeIO){
        trace = &(*trace)->next;
    }
    return (trace);
}*/
/**
 * this function look the IO list to see is any it prossess sre done
 * @param head the head of IO list
 * @param systime the time that you want to check
 * @return a pointer tp the mode that is done
 */
node **findFinishIO(node **head,int systime){

    node **trace = head;
    while ((*trace)&& (*trace)->item.simNode->timeNeedIO != systime){
        trace = &(*trace)->next;
    }
    return (trace);
}
/**
 * tnis prints a report for the start of a burst
 * @param working the node to be worked on
 * @param enviro the enviroment that you are using
 */
void printReport(node *working,SimEnviro *enviro){
    printf("Current time<%d>\n",enviro->time);
    if(working)
        printf("running job %s has %d units left and is useing %d memory resources\n", working->item.simNode->name, (working->item.simNode->time - working->item.simNode->timeran), working->item.simNode->mem);
    node **trace =&enviro->queue;
    int pos=1;
    printf("the queue is:\n");
    //add new line for vm mem
    while ((*trace)){
        if((*trace)->item.simNode->inVMem==1)
            printf("\tPosition %d: job %s has %d units left and is useing %d resource on disk.\n", pos, (*trace)->item.simNode->name, ((*trace)->item.simNode->time - (*trace)->item.simNode->timeran), (*trace)->item.simNode->mem);
        else
            printf("\tPosition %d: job %s has %d units left and is useing %d memory resources.\n", pos, (*trace)->item.simNode->name, ((*trace)->item.simNode->time - (*trace)->item.simNode->timeran), (*trace)->item.simNode->mem);
        pos++;
        trace=&(*trace)->next;
    }
    trace =&enviro->IO;
    printf("the IO is:\n");
    while ((*trace)){
        printf("\tThe process %s is obtaining IO and will be back in %d unit.\n", (*trace)->item.simNode->name, ((*trace)->item.simNode->timeNeedIO - enviro->time));
        pos++;
        trace=&(*trace)->next;
    }
    trace =&enviro->finished;
    printf("Finished jobs are:\n");
    while ((*trace)){
        printf("\t %s %d %d\n", (*trace)->item.simNode->name, (*trace)->item.simNode->timeran, (*trace)->item.simNode->time);
        pos++;
        trace=&(*trace)->next;
    }
    printf("\n");
}
/*
void queueadd(node *data){
    insertNode(&queue,data);
}
void setBurst(int data){
    burst=data;
}*/
