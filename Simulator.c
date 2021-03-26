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
void runburst(node *working, SimEnviro *enviro,int stopStep){
    printReport(working,enviro);
    for (int i = 0; i < enviro->burst; ++i) {
        if(working) {
            if (working->item.SimNode->timeran == working->item.SimNode->timeStartIO) {
                working->item.SimNode->timeNeedIO += enviro->time;
                working->item.SimNode->timeStartIO=-1;
                insertNode(&enviro->IO, working);
                working = NULL;
                return;
            }
            //this is to see if thare is any thing in the IO list that needs to come off at this time
/*            found = findFinishIO(&enviro->IO, enviro->time);
            while ((*found)) {
                node *tmp = (*found);
                (*found) = (*found)->next;
                insertNode(&enviro->queue, tmp);
            }*/
            if(enviro->time>=stopStep&&stopStep!=-1){
                if (working->item.SimNode->time != working->item.SimNode->timeran) {
                    pushToTop(&enviro->queue,working);
                    enviro->stop=1;
                }
                return;
            }
            working->item.SimNode->timeran++;
            enviro->time++;

            if (working->item.SimNode->time == working->item.SimNode->timeran) {
                working->item.SimNode->time = enviro->time;
                insertNode(&enviro->finished, working);
                //printf("\tfinished:%s<%d>",working->item.SimNode->name,enviro->time);
                working = NULL;
                return;
            }
        }else{
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
}
void simrun(SimEnviro *enviro){
    stepTill(enviro,-1);
}
void checkFinishdeIO(SimEnviro *enviro){

}
node **findStartIO(node **head,int timeIO){

    node **trace = head;
    while ((*trace)&&(*trace)->item.SimNode->timeStartIO!=timeIO){
        trace = &(*trace)->next;
    }
    return (trace);
}
node **findFinishIO(node **head,int systime){

    node **trace = head;
    while ((*trace)&&(*trace)->item.SimNode->timeNeedIO!=systime){
        trace = &(*trace)->next;
    }
    return (trace);
}
void printReport(node *working,SimEnviro *enviro){
    printf("Current time<%d>\n",enviro->time);
    if(working)
        printf("running job %s has %d units left and is useing %d memory resources\n",working->item.SimNode->name,(working->item.SimNode->time-working->item.SimNode->timeran),working->item.SimNode->mem);
    node **trace =&enviro->queue;
    int pos=1;
    printf("the queue is:\n");
    while ((*trace)){
        printf("\tPosition %d: job %s has %d units left and is useing %d memory resources.\n",pos,(*trace)->item.SimNode->name,((*trace)->item.SimNode->time-(*trace)->item.SimNode->timeran),(*trace)->item.SimNode->mem);
        pos++;
        trace=&(*trace)->next;
    }
    trace =&enviro->IO;
    printf("the IO is:\n");
    while ((*trace)){
        printf("\tThe process %s is obtaining IO and will be back in %d unit.\n",(*trace)->item.SimNode->name,((*trace)->item.SimNode->timeNeedIO-enviro->time));
        pos++;
        trace=&(*trace)->next;
    }
    trace =&enviro->finished;
    printf("Finished jobs are:\n");
    while ((*trace)){
        printf("\t %s %d %d\n",(*trace)->item.SimNode->name,(*trace)->item.SimNode->timeran,(*trace)->item.SimNode->time);
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
