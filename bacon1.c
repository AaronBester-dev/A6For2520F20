#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

void val2KeyMiniVersion(FILE * valFile, FILE * keyAndValFile, char * whatToLookFor,int hashNum,char * whereToPutIt);
void key2ValMiniVersion(FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor,int  hashNum, char * whereToPutIt);

/*If the given actor has worked with kevin bacon on a movie before the program returns
the name of said movie.*/
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
    FILE * titleBasicsKeyAndValues = fopen("title.basics.kv","rb");
    FILE * titleBasicsKey = fopen("title.basics.khs","rb");

    int fileSizeOFPrincipalsValue = get_capacity(titlePrincipalsValue);
    int fileSizeOfNameBasicsValue = get_capacity(nameBasicsValues);
    int fileSizeOFPrincipalsKey = get_capacity(titlePrincipalsKey);
    int fileSizeOfTitleBasicsKey = get_capacity(titleBasicsKey);
    int hashNum = 0; 
    int kevinBaconMovieHashNum = 0;
    int peopleInMovieHashNum = 0;
    int kevinBaconMovieCounter = 0;
    int peopleInMovieCounter = 0;
    int actorFound = 0;  
    int getNextMovie = 0;
    int exitProgram = 0;
    char kevinBaconMovieKey[STRLEN];
    char keyOfKevinBacon[STRLEN];
    char keyOfActorWhoStarsWithKevinBacon[STRLEN];
    char actorKey[STRLEN];
    char movieTheyAreBothIn[STRLEN];
 
    /*Getting users person key*/
    hashNum = hashfn(argv[1],fileSizeOfNameBasicsValue);
    val2KeyMiniVersion(nameBasicsValues,nameBasicsKeyAndValues,argv[1],hashNum,keyOfActorWhoStarsWithKevinBacon);

    while(strcmp(keyOfActorWhoStarsWithKevinBacon,"NOT FOUND") == 0 && kevinBaconMovieCounter <= fileSizeOfNameBasicsValue){
        val2KeyMiniVersion(nameBasicsValues,nameBasicsKeyAndValues,argv[1],hashNum,keyOfActorWhoStarsWithKevinBacon);
        hashNum++;
        kevinBaconMovieCounter++;
        if(hashNum >= fileSizeOfNameBasicsValue){
            hashNum = 0;
        }
    }
    if(kevinBaconMovieCounter >= fileSizeOfNameBasicsValue){
        return(0);
    }

    /*Getting kevin bacons key*/
    hashNum = hashfn("Kevin Bacon",fileSizeOfNameBasicsValue);
    val2KeyMiniVersion(nameBasicsValues,nameBasicsKeyAndValues,"Kevin Bacon",hashNum,keyOfKevinBacon);
    while(strcmp(keyOfKevinBacon,"NOT FOUND") == 0){
        val2KeyMiniVersion(nameBasicsValues,nameBasicsKeyAndValues,"Kevin Bacon",hashNum,keyOfKevinBacon);
        hashNum++;
        if(hashNum >= fileSizeOfNameBasicsValue){
            hashNum = 0;
        }
      
    }
    

    /*getting key of movie kevin bacon is in*/
    kevinBaconMovieHashNum = hashfn(keyOfKevinBacon,fileSizeOFPrincipalsValue);  
    kevinBaconMovieCounter = 0;    

    while( (kevinBaconMovieCounter < fileSizeOFPrincipalsValue && exitProgram != 1)){

        val2KeyMiniVersion(titlePrincipalsValue,titlePrincipalsKeyAndValues,keyOfKevinBacon,kevinBaconMovieHashNum,kevinBaconMovieKey);
        kevinBaconMovieHashNum++;
        kevinBaconMovieCounter++;
        if(kevinBaconMovieHashNum >= fileSizeOFPrincipalsValue){
            kevinBaconMovieHashNum = 0;
        }
        
        if(strcmp(kevinBaconMovieKey,"NOT FOUND") != 0){
            /*getting key of people in said movie*/
            peopleInMovieHashNum = hashfn(kevinBaconMovieKey,fileSizeOFPrincipalsKey);
            peopleInMovieCounter = 0;
            actorFound = 0;
            getNextMovie = 0;
            while( (peopleInMovieCounter < fileSizeOFPrincipalsKey) && getNextMovie == 0){
                key2ValMiniVersion(titlePrincipalsKey,titlePrincipalsKeyAndValues,kevinBaconMovieKey,peopleInMovieHashNum,actorKey);
                peopleInMovieHashNum++;
                peopleInMovieCounter++;
                if(peopleInMovieHashNum >= fileSizeOFPrincipalsKey){
                    peopleInMovieHashNum = 0;
                }
                
                if(strcmp(actorKey,"NOT FOUND") != 0){
                    actorFound = 1;
                    /*Getting key of movie if person exists in it*/
                    if(strcmp(actorKey,keyOfActorWhoStarsWithKevinBacon) == 0){
                        peopleInMovieHashNum = hashfn(kevinBaconMovieKey,fileSizeOfTitleBasicsKey);
                        key2ValMiniVersion(titleBasicsKey,titleBasicsKeyAndValues,kevinBaconMovieKey,peopleInMovieHashNum,movieTheyAreBothIn);
                        while(strcmp(movieTheyAreBothIn,"NOT FOUND") == 0){
                            key2ValMiniVersion(titleBasicsKey,titleBasicsKeyAndValues,kevinBaconMovieKey,peopleInMovieHashNum,movieTheyAreBothIn);    
                            hashNum++;
                            if(hashNum >= fileSizeOfNameBasicsValue){
                                hashNum = 0;
                            }
                        }
                        printf("%s\n",movieTheyAreBothIn);
                        fclose(titlePrincipalsKey);
                        fclose(titlePrincipalsValue);
                        fclose(titlePrincipalsKeyAndValues);
                        fclose(nameBasicsKeyAndValues);
                        fclose(nameBasicsValues);
                        fclose(titleBasicsKey);
                        fclose(titleBasicsKeyAndValues);
                        return(0);
                    }
                }
                else{
                    if(actorFound == 1){
                        getNextMovie = 1;
                    }
                }
            }
        }
    }
    
    fclose(titlePrincipalsKey);
    fclose(titlePrincipalsValue);
    fclose(titlePrincipalsKeyAndValues);
    fclose(nameBasicsKeyAndValues);
    fclose(nameBasicsValues);
    fclose(titleBasicsKey);
    fclose(titleBasicsKeyAndValues);
    return(0);
}
/*Gets the key from a kv file at the index given to by the value*/
void val2KeyMiniVersion(FILE * valFile, FILE * keyAndValFile, char * whatToLookFor,int hashNum,char * whereToPutIt){

    int index = 0;
    char valString[STRLEN];

    read_index(valFile,hashNum,&index);
    read_val(keyAndValFile,index,valString);
    if(strcmp(valString,whatToLookFor) == 0){
        read_key(keyAndValFile,index,whereToPutIt);
    }
    else{
        strcpy(whereToPutIt,"NOT FOUND");
    }    
}
/*Gets the value from a kv file at the index given to by the key*/
void key2ValMiniVersion(FILE * keyFile, FILE * keyAndValFile, char * whatToLookFor,int  hashNum, char * whereToPutIt){

    int index = 0;
    char keyString[STRLEN];

    read_index(keyFile,hashNum,&index);
    read_key(keyAndValFile,index,keyString);
    if(strcmp(keyString,whatToLookFor) == 0){
        read_val(keyAndValFile,index,whereToPutIt);
    }
    else{
        strcpy(whereToPutIt,"NOT FOUND");
    }
}

