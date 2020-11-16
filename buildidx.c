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
        char fileName[strlen(argv[1])+5];
        char keyString[STRLEN];
        char valueString[STRLEN];
        long capacity = strtol(argv[2],NULL,10);
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
                
                read_index(keyFile,keyHashNum,&index);
                
                while(index != -1){
                    keyHashNum++;
                    
                    
                    if(keyHashNum >= capacity){
                        keyHashNum = 0;
                    }
                    read_index(keyFile,keyHashNum,&index);
                     
                }
                write_index(keyFile,i,keyHashNum);
                
                read_index(valueFile,valHashNum,&index); 
                
                while(index != -1){
                       
                    valHashNum++;
                    if(valHashNum >= capacity){
                        valHashNum = 0;
                    }
                    read_index(valueFile,valHashNum,&index); 
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
    placeToStoreFileName[strlen(fileName)-3] = '\0';
    strcat(placeToStoreFileName,fileExtension);
}