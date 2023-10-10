#include "hmac.h"

#define ipad 0x36;
#define opad 0x5C;

void hmacMain(unsigned char *message, unsigned char *key, uint32_t *digest){

	unsigned char K0[64];
	unsigned char K1[64];
	int i;
	//printf("K0:\n");
	for(i = 0; i < 64; i++){
		K0[i] = key[i] ^ ipad;
		//printf("%02x%c", K0[i], (i%16 == 15)?'\n':' ');
	}
	//printf("\nK1:\n");
	for(i = 0; i < 64; i++){
		K1[i] = key[i] ^ opad;
		//printf("%02x%c", K1[i], (i%16 == 15)?'\n':' ');

	}
	uint64_t msg_len = strlen(message);
	unsigned char state1[msg_len + 64];
		for(i = 0; i < (msg_len +64); i++){
			if(i < 64)
				state1[i] = K0[i];
			else
				state1[i] = message[i - 64];
		}

	sha1Main(state1, digest, msg_len+64);
	/*
	for(i=0;i<5;i++)
		printf("%08x ",digest[i]);
	printf("\n");
	*/
	uint8_t Digest[20];
	    for(i = 0; i < 5; i++) {
        	Digest[(i * 4) + 0] = (uint8_t) ((digest[i] >> 24) & 0xFF);
        	Digest[(i * 4) + 1] = (uint8_t) ((digest[i] >> 16) & 0xFF);
        	Digest[(i * 4) + 2] = (uint8_t) ((digest[i] >> 8) & 0xFF);
        	Digest[(i * 4) + 3] = (uint8_t) (digest[i] & 0xFF);
    	 }
	 
	unsigned char state2[84];
		for(i = 0; i < 84; i++){
			if(i < 64)
				state2[i] = K1[i];
			else
				state2[i] = Digest[i - 64];
		}

		sha1Main(state2, digest, 84);

}
