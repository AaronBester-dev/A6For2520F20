#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"
#include "helper.h"

void getFilename(char * fileName,char * fileExtension,char * placeToStoreFileName);

int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);
        exit(-1);
    }
    else{
        char fileName[strlen(argv[1])+1];
        char * capacityString = argv[2];
        char * tempPtr;
        char keyString[256];
        char valueString[256];
        long capacity = strtol(capacityString,&tempPtr,10);
        int i = 0;
        int index = 0;
        unsigned int keyHashNum = 0;
        unsigned int valHashNum = 0;
        FILE * keyAndValueFile = NULL;
        FILE * keyFile = NULL;
        FILE * valueFile = NULL;
       
        if((keyAndValueFile = fopen(argv[1],"rb")) != NULL){
            getFilename(argv[1],".khs",fileName);
            keyFile = fopen(fileName,"wb+");
            getFilename(argv[1],".vhs",fileName);
            
            valueFile = fopen(fileName,"wb+");
            write_empty(keyFile,capacity);
           
            write_empty(valueFile,capacity);
         
            while(read_keyval(keyAndValueFile,keyString,valueString) == 2){
                keyHashNum = hashfn(keyString,capacity);
                valHashNum = hashfn(valueString,capacity);
                index = i;
                read_index(keyFile,keyHashNum,&index);
              
                while(index != -1){
                    read_index(keyFile,keyHashNum,&index);
                    keyHashNum++;
                    if(keyHashNum >= capacity){
                        keyHashNum = 0;
                    }
                }

                write_index(keyFile,i,keyHashNum);
                index = i;
                read_index(valueFile,valHashNum,&index); 
                while(index != -1){
                    read_index(valueFile,valHashNum,&index);    
                    valHashNum++;
                    if(valHashNum >= capacity){
                        valHashNum = 0;
                    }
                }
                write_index(valueFile,i,valHashNum);
                i++;
            }
        }
        else{
            fprintf( stderr, "Error: %s can't be found\n", argv[1]);
            exit(-1);
        }
        fclose(keyAndValueFile);
        fclose(keyFile);
        fclose(valueFile);
        

    }
}

void getFilename(char * fileName,char * fileExtension,char * placeToStoreFileName){
    strcpy(placeToStoreFileName,fileName);
    placeToStoreFileName[strlen(fileName)-4] = '\0';
    strcat(placeToStoreFileName,fileExtension);
}