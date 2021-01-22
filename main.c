#include <stdio.h>
#include <stdlib.h>
#include "SystemData.h"




int main(int argc, char **argv){
    //checking if thare is a secone arg to reage
    if(argc>=2){
        // if thare is then use that arg as a file name and read that file
        //fileReader(argv[1]);
    }else{
        // if now promp and ecit programe
        printf("%s","No file specified\n");
        exit(-2);
    }
}