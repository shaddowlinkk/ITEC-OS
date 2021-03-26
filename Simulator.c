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
void runburst(node *working, SimEnviro *enviro,int stopStep){
    for (int i = 0; i < enviro->burst; ++i) {
        if(working) {
            // tooks at the queue if thare need to be anything added to the IO list
            // this may not be how this works to be addes to the io it may be based of the working node so the node need to io on its 3ed step
            // the if that is the case the implement this sudo code
            /*
             * first check to see if timeran == timeStartIO
             * then add enviro.time to timeNeedIO to get what Enviro time that you need to tack it of on
             * then add the working node to IO
             * then return
             */
            node **found=findStartIO(&enviro->queue,enviro->time);
            while ((*found)){
                node *tmp=(*found);
                (*found)=(*found)->next;
                insertNode(&enviro->IO,tmp);
                found=NULL;
                found=findStartIO(&enviro->queue,enviro->time);
            }
            //this is to see if thare is any thing in the IO list that needs to come off at this time
            found=findFinishIO(&enviro->IO,enviro->time);
            while ((*found)){
                node *tmp=(*found);
                (*found)=(*found)->next;
                insertNode(&enviro->queue,tmp);
                found=NULL;
                found=findStartIO(&enviro->IO,enviro->time);
            }
            found=findStartIO(&working,enviro->time);
            if((*found)){
                node *tmp=(*found);
                (*found)=(*found)->next;
                insertNode(&enviro->IO,tmp);
                i=enviro->burst;
                enviro->time++;
                return;
            }
            working->item.SimNode->timeran++;
            if (working->item.SimNode->time == working->item.SimNode->timeran) {
                working->item.SimNode->time=enviro->time;
                insertNode(&enviro->finished, working);
                working=NULL;
                enviro->time++;
                return;
            }
        }
        if(enviro->time>=stopStep&&stopStep!=-1){
            if (working->item.SimNode->time != working->item.SimNode->timeran) {
                pushToTop(&enviro->queue,working);

            }
            return;
        }
        enviro->time++;
    }
    insertNode(&enviro->queue,working);
}
void stepTill(SimEnviro *enviro, int stopStep){
    node *working;
    while (enviro->queue||enviro->IO) {
        if(enviro->queue) {
            working = popnode(&enviro->queue);
        }
        //add print out here will need to be a method
        runburst(working,enviro,stopStep);
        if(enviro->time>=stopStep&&stopStep!=-1){
            return;
        }
    }

}
void simrun(SimEnviro *enviro){
    stepTill(enviro,-1);
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
    while ((*trace)&&((*trace)->item.SimNode->timeStartIO+(*trace)->item.SimNode->timeNeedIO)!=systime){
        trace = &(*trace)->next;
    }
    return (trace);
}
/*
void queueadd(node *data){
    insertNode(&queue,data);
}
void setBurst(int data){
    burst=data;
}*/
