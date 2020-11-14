#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(-1);
    }
    else{
        char * fileName = argv[1];
        char * capacityString = argv[2];
        char * tempPtr;
        long capacity = strtol(capacityString,&tempPtr,10);
        FILE * fp;
        if()

    }
}