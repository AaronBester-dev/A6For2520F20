#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

void val2KeyMiniVersion(int fileSize, FILE * valFile, FILE * keyAndValFile, char * whatToLookFor,int hashNum,char * whereToPutIt);
void key2ValMiniVersion(int fileSize, FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor,int hashNum, char * whereToPutIt);
int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf( stderr, "Usage: %s 'search term'\n", argv[0]);
        exit(-1);
    }

    FILE * titlePrincipalsValue = fopen("title.principals.vhs","rb");
    FILE * titlePrincipalsKeyAndValues = fopen("title.principals.kv","rb");
    FILE * titlePrincipalsKey = fopen("title.principals.khs","rb");
    FILE * nameBasicsValues = fopen("name.basics.vhs","rb");
    FILE * nameBasicsKeyAndValues = fopen("name.basics.kv","rb");
    FILE * titleBasicsValue = fopen("title.basics.vhs","rb");
    FILE * titleBasicsKeyAndValues = fopen("title.basics.kv","rb");
    FILE * titleBasicsKey = fopen("title.basics.khs","rb");

    int fileSizeOFPrincipalsValue = get_capacity(titlePrincipalsValue);
    int fileSizeOfNameBasicsValue = get_capacity(nameBasicsValues);
    int fileSizeOfTitleBasicsValue = get_capacity(titleBasicsValue);
    int fileSizeOfNameBasicsKey = get_capacity(titleBasicsKey);
    int fileSizeOFPrincipalsKey = get_capacity(titlePrincipalsKey);

    int hashNum = 0; 
    char whatToLookFor[256] = "Kevin Bacon";
    char whereToPutIt[256];
    char tempString[256];
    char keyOfActorWhoStarsWithKevinBacon[256];
    char keyOfMovieKevinBaconIsIn[256];
 
    /*Getting users person key*/
    hashNum = hashfn(argv[1],fileSizeOfNameBasicsValue);
    val2KeyMiniVersion(fileSizeOfNameBasicsValue,nameBasicsValues,nameBasicsKeyAndValues,argv[1],&hashNum,keyOfActorWhoStarsWithKevinBacon);

    /*Getting kevin bacons key*/
    hashNum = hashfn(whatToLookFor,fileSizeOfNameBasicsValue);
    val2KeyMiniVersion(fileSizeOfNameBasicsValue,nameBasicsValues,nameBasicsKeyAndValues,whatToLookFor,&hashNum,whereToPutIt);


    /*getting key of movie kevin bacon is in*/
    swapStrings(whatToLookFor,whereToPutIt);
    hashNum = hashfn(whatToLookFor,fileSizeOfNameBasicsValue)
    val2KeyMiniVersion(fileSizeOFPrincipalsValue,titleBasicsValue,titlePrincipalsKeyAndValues,whatToLookFor,&hashNum,whereToPutIt);
    strcpy(keyOfMovieKevinBaconIsIn,whereToPutIt);

    /*getting key of people in said movie*/
    swapStrings(whatToLookFor,whereToPutIt);
    hashNum = hashfn(whatToLookFor,fileSizeOfTitleBasicsKey);
    key2ValMiniVersion(fileSizeOFPrincipalsKey,titlePrincipalsKey,titlePrincipalsKeyAndValues,whatToLookFor,&hashNum,whereToPutIt);

    swapStrings(whatToLookFor,whereToPutIt);
    if(strcmp(whatToLookFor,keyOfActorWhoStarsWithKevinBacon) == 0){
        hashNum = (keyOfMovieKevinBaconIsIn,fileSizeOfTitleBasicsKey)
        key2ValMiniVersion(fileSizeOfTitleBasicsKey,titleBasicsKey,titleBasicsKeyAndValues,keyOfMovieKevinBaconIsIn,&hashNum,whereToPutIt);
        printf("%s\n"whereToPutIt);
        return(0);
    }
    
    

}

void val2KeyMiniVersion(int fileSize, FILE * valFile, FILE * keyAndValFile, char * whatToLookFor,int * hashNum,char * whereToPutIt){
    int counter = 0;
    int index = 0;
    char valString[256];
    int foundOne = 0;

    while(counter < fileSize && foundOne != 1){
        read_index(valFile,hashNum,&index);
        read_val(keyAndValFile,index,valString);
        if(strcmp(valString,whatToLookFor) == 0){
            read_key(keyAndValFile,index,whereToPutIt);
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
    strcpy(whereToPutIt,"NOTHING FOUND");
}

void key2ValMiniVersion(int fileSize, FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor,int * hashNum, char * whereToPutIt){
    int counter = 0;
    int index = 0;
    char keyString[256];
    char valString[256];
    int foundOne = 0;

     while(counter < fileSize && foundOne != 1){
        read_index(keyFile,hashNum,&index);
        read_key(keyAndValFile,index,keyString);
        if(strcmp(keyString,whatToLookFor) == 0){
            read_val(keyAndValFile,index,whereToPutIt);
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
    strcpy(whereToPutIt,"NOTHING FOUND");
}

void swapStrings(char * string1, char * string2){
    char  tempString[256];
    strcpy(tempString,string1);
    strcpy(string1,string2);
    strcpy(string2,tempString);
}