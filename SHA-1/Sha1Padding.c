#include "sha1.h"

uint8_t j;

void sha1Padding(unsigned char *message,  uint64_t msg_len, uint64_t padding_len, unsigned char *paddedMsg){

int i;
	for(i = 0; i < msg_len + padding_len; i++){
		if(i < msg_len){
			paddedMsg[i] = message[i];
		}else if((msg_len == i) && padding_len > 0){
			paddedMsg[i] = 0x80;
		}else{
			paddedMsg[i] = 0x00;
		}
	}

}

