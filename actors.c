#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

void val2KeyMiniVersion(int fileSize, FILE * valFile, FILE * keyAndValFile, char * whatToLookFor);
int key2ValMiniVersion(int fileSize, FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor);

/*Gets the list of every single actor that worked on a specific movie*/
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


    char keyString[STRLEN];
    char valString[STRLEN];

    int counter = 0;
    int index = 0;
    int hashNum = 0;

    int fileSizeOFPrincipalsKey = get_capacity(titlePrincipalsKey);
    int fileSizeOfNameBasicsKey = get_capacity(nameBasicsKey);
    int fileSizeOfTitleBasicsValue = get_capacity(titleBasicsValue);

    /*Gets the key of the movie*/
    val2KeyMiniVersion(fileSizeOfTitleBasicsValue,titleBasicsValue,titleBasicsKeyAndValues,argv[1]);
    hashNum = hashfn(argv[1],fileSizeOFPrincipalsKey);
    /*Gets the key of every single actor in that movie*/
    while( (counter < fileSizeOFPrincipalsKey)){
        read_index(titlePrincipalsKey,hashNum,&index);
        read_key(titlePrincipalsKeyAndValues,index,keyString);
        if(strcmp(keyString,argv[1]) == 0){
            read_val(titlePrincipalsKeyAndValues,index,valString);
            /*Gets the name of said actor and prints it out*/
            key2ValMiniVersion(fileSizeOfNameBasicsKey,nameBasicsKey,nameBasicsKeyAndValues,valString);  
            hashNum++;
            counter++;
            if(hashNum >= fileSizeOFPrincipalsKey){
                hashNum = 0;
            }
        }
        else{
            hashNum++;
            counter++;
            if(hashNum >= fileSizeOFPrincipalsKey){
                hashNum = 0;
            }
        }
        
    }

    fclose(titleBasicsKeyAndValues);
    fclose(titleBasicsValue);
    fclose(titlePrincipalsKey);
    fclose(titlePrincipalsKeyAndValues);
    fclose(nameBasicsKey);
    fclose(nameBasicsKeyAndValues);
    return(0);

}
/*Gets the value from a kv file at the index given to by the key*/
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
/*Gets the key from a kv file at the index given to by the value*/
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