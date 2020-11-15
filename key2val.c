#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int getSizeOfFile(FILE * fp);

int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
        exit(-1);
    }
    
    char fileName[sizeof(argv[1])+1];
    char * searchTerm = argv[2];
    char keyString[256];
    char valString[256];
    int fileSize = 0;
    FILE * keyAndValFile;
    FILE * keyFile;
    int index = 0;
    int hashNum = 0;
    int counter = 0;

    keyAndValFile = fopen(argv[1],"rb");
    strcpy(fileName,argv[1]);
    fileName[strlen(fileName)-1] = 'h';
    fileName[strlen(fileName)] = 's';
    keyFile = fopen(fileName,"rb");

    fileSize = get_capacity(keyFile);
 
    hashNum = hashfn(searchTerm,fileSize);
    
    while(counter >= fileSize){
        read_index(keyFile,hashNum,&index);
        read_key(keyAndValFile,index,keyString);
        if(strcmp(keyString,searchTerm) == 0){
            read_val(keyAndValFile,index,valString);
            printf("%s\n",valString);
            fclose(keyAndValFile);
            fclose(keyFile);
            return(0);
        }
        else{
            hashNum++;
            counter++;
            if(hashNum >= fileSize){
                hashNum = 0;
            }
        }
    }
    fclose(keyAndValFile);
    fclose(keyFile);
    printf("NOT FOUND\n");
    return(0);
}

