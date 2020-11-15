#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

void val2KeyMiniVersion(int fileSize, FILE * valFile, FILE * keyAndValFile, char * whatToLookFor);
int key2ValMiniVersion(int fileSize, FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor);
int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf( stderr, "Usage: %s 'search term'\n", argv[0]);
        exit(-1);
    }

    FILE * titlePrincipalsKey = fopen("title.principals.khs","rb");
    FILE * titlePrincipalsKeyAndValues = fopen("title.principals.kv","rb");
    FILE * nameBasicsKey = fopen("name.basics.khs","rb");
    FILE * nameBasicsKeyAndValues = fopen("name.basics.kv","rb");
    FILE * titleBasicsValue = fopen("title.basics.vhs","rb");
    FILE * titleBasicsKeyAndValues = fopen("title.basics.kv","rb");


    char keyString[256];
    char valString[256];

    int fileSizeOFPrincipalsKey = 0;
    int fileSizeOfNameBasicsKey = 0;
    int fileSizeOfTitleBasicsValue = 0;
    int counter = 0;
    int index = 0;
    int hashNum = 0;
    int foundOne = 0;
    fileSizeOFPrincipalsKey = get_capacity(titlePrincipalsKey);
    fileSizeOfNameBasicsKey = get_capacity(nameBasicsKey);
    fileSizeOfTitleBasicsValue = get_capacity(titleBasicsValue);
    
    val2KeyMiniVersion(fileSizeOfTitleBasicsValue,titleBasicsValue,titleBasicsKeyAndValues,argv[1]);

    while( (counter < fileSizeOFPrincipalsKey) && ((foundOne != 1) || (strcmp(keyString,argv[1]) == 0))){
        read_index(titlePrincipalsKey,hashNum,&index);
        read_key(titlePrincipalsKeyAndValues,index,keyString);
        if(strcmp(keyString,argv[1]) == 0){
            foundOne = 1;
            read_val(titlePrincipalsKeyAndValues,index,valString);
            key2ValMiniVersion(fileSizeOfNameBasicsKey,nameBasicsKey,nameBasicsKeyAndValues,valString);
        }
        else{
            hashNum++;
            counter++;
            if(hashNum >= fileSizeOFPrincipalsKey){
                hashNum = 0;
            }
        }
    }

    return(0);

}

int key2ValMiniVersion(int fileSize, FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor){
    int counter = 0;
    int index = 0;
    char keyString[256];
    char valString[256];
    int hashNum = 0;
    hashNum = hashfn(whatToLookFor,fileSize);
     while(counter < fileSize){
        read_index(keyFile,hashNum,&index);
        read_key(keyAndValFile,index,keyString);
        if(strcmp(keyString,whatToLookFor) == 0){
            read_val(keyAndValFile,index,valString);
            printf("%s\n",valString);
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
    return(-1);
}

void val2KeyMiniVersion(int fileSize, FILE * valFile, FILE * keyAndValFile, char * whatToLookFor){
    int counter = 0;
    int index = 0;
    char valString[256];
    int hashNum = 0;
    int foundOne = 0;
    hashNum = hashfn(whatToLookFor,fileSize);

    while(counter < fileSize && foundOne != 1){
        read_index(valFile,hashNum,&index);
        read_val(keyAndValFile,index,valString);
        if(strcmp(valString,whatToLookFor) == 0){
            read_key(keyAndValFile,index,whatToLookFor);
            foundOne = 1;
        }
        else{
            hashNum++;
            counter++;
            if(hashNum >= fileSize){
                hashNum = 0;
            }
        }
    }
}