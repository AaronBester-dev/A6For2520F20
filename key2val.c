#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

void getFilename(char * fileName,char * fileExtension,char * placeToStoreFileName);

/*Gets the value from a kv file at the index given to by the key*/
int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv 'search term'\n", argv[0]);
        exit(-1);
    }
    
    char fileName[strlen(argv[1])+5];
    char keyString[STRLEN];
    char valString[STRLEN];
    int fileSize = 0;
    FILE * keyAndValFile;
    FILE * keyFile;
    int index = 0;
    int hashNum = 0;
    int counter = 0;

    keyAndValFile = fopen(argv[1],"rb");

    getFilename(argv[1],".khs",fileName);

    keyFile = fopen(fileName,"rb");

    fileSize = get_capacity(keyFile);
    hashNum = hashfn(argv[2],fileSize);

    while(counter < fileSize){
        read_index(keyFile,hashNum,&index);
        read_key(keyAndValFile,index,keyString);
        if(strcmp(keyString,argv[2]) == 0){
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
/*Gets the filename of the khs and vhs files*/
void getFilename(char * fileName,char * fileExtension,char * placeToStoreFileName){
    strcpy(placeToStoreFileName,fileName);
    placeToStoreFileName[strlen(fileName)-3] = '\0';
    strcat(placeToStoreFileName,fileExtension);
}
