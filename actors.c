#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfn.h"
#include "util.h"

int main(int argc, char * argv[]){
    if(argc != 2){
        fprintf( stderr, "Usage: %s 'search term'\n", argv[0]);
        exit(-1);
    }

    FILE * titlePrincipalsKey = fopen("title.principals.khs","rb");
    FILE * titlePrincipalsKeyAndValues = fopen("title.principals.kv","rb");
    FILE * nameBasicsValue = fopen("name.basics.vhs","rb");
    FILE * nameBasicsKeyAndValues = fopen("name.basics.kv","rb");

    
}