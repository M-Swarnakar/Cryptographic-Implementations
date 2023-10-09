#include <stdio.h>
#include <stdint.h>
#include "sha1.h"

int main(int argc, unsigned char *argv[]){

	unsigned char *message = argv[1];
        printf("The given plaintext: %s\n", message);
        if(argc > 2){
                printf("Please give the input without any space in between\n");
        }else{
             sha1Main(message);
	}

}
