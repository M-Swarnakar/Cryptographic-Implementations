#include <stdio.h>
#include <stdint.h>
#include "sha1.h"

int main(int argc, unsigned char *argv[]){

	unsigned char *message = argv[1];
	uint32_t digest[5];
        printf("The given plaintext: %s\n", message);
        if(argc > 2){
                printf("Please give the input without any space in between\n");
        }else{
             sha1Main(message, digest, strlen(message));
	}
	printf("The Hash value:\n");
	for(int i = 0; i < 5; i++){
		printf("%08x ", digest[i]);
	}
	printf("\n");

}
