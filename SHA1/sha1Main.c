
#include "sha1.h"

uint32_t a, b, c, d,e;

uint32_t K[] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};

void sha1Main(unsigned char *message, uint32_t *digest, uint64_t msg_len){
//printf("\nmlen = %ld\n",msg_len);

//uint64_t msg_len;
//	msg_len = strlen(message); // bytewise lenthof the msg and we need 64 bytes per block
uint64_t offset = msg_len / 64;
uint64_t offset2 = msg_len % 64;
uint64_t padding_len = offset2 < 56 ? 56 - offset2 : (64 + 56) - offset2;
uint64_t total_len = msg_len + padding_len; // bytewise
uint8_t paddedMsg[total_len];

	// Padding
	sha1Padding(message, msg_len, padding_len, paddedMsg);

	// Processing words and th message blocks of 512 bit
uint32_t msg_words[total_len/4 + 2];
uint32_t X[16];
int i, j = 0;
	for(i = 0; i < total_len; i += 4){
		msg_words[j++] = (uint32_t) (paddedMsg[i] << 24 | paddedMsg[i+1] << 16 | paddedMsg[i+2] << 8 | paddedMsg[i+3]);//change

	}
	msg_words[j++] = (uint32_t) ((msg_len * 8) >> 32);
	msg_words[j++] = (uint32_t) ((msg_len * 8) & 0xFFFFFFFF);
	//msg_words[j++] = (uint32_t) ((msg_len * 8) >> 32); change
	int msg_Block_count;
	msg_Block_count = (msg_len + padding_len + 8) / 64;
	/*
	printf("\nWords :\n");
	for(i=0; i < (total_len / 4)+2; i++)
	    printf("%08x%c", msg_words[i],(i%16 == 15)?'\n':' ');
	printf("\n");
	*/
	a =A; b=B; c=C; d=D; e=E;
	for(i = 0; i < msg_Block_count; i++){
		for(int k = 0; k < 16; k++){
			X[k] = msg_words[i * 16 + k];
		}
		/*
		printf("Block %d\n", i);
		for(int p=0; p < 16; p++){
			printf("%08x ", X[p]);
		}
		printf("\n");
		*/
		sha1_update(X);
	}
        //printf("\nThe Hash value:\n");
        //printf("%08x %08x %08x %08x %08x\n", a, b, c, d, e);
	digest[0] = a;
	digest[1] = b;
	digest[2] = c;
	digest[3] = d;
	digest[4] = e;

}


uint32_t rotateLeft(uint32_t x, uint32_t n) {
    return ((x << n) | (x >> (32 - n)));
}

uint32_t rotateRight(uint32_t x, uint32_t n) {
    return ((x >> n) | (x << (32 - n)));
}

void sha1_update(uint32_t *X){

uint32_t W[80];

	for( int i = 0; i < 80; i++){
		if(i < 16)
			W[i] = X[i];
		else
			W[i] = rotateLeft((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]), 1);
		//printf("%08x%c",W[i],(i % 16 == 15)? '\n':' ');
	}


uint32_t AA = a, BB = b, CC = c, DD = d, EE = e;
int r;
	for(r = 0; r < 80; r++){
		
		switch(r / 20){
			case 0:
				R1f(W, &AA, &BB, &CC, &DD, &EE, r);
				break;
			case 1:
				R2f(W, &AA, &BB, &CC, &DD, &EE, r);
				break;
			case 2:
				R3f(W, &AA, &BB, &CC, &DD, &EE, r);
				break;
			case 3:
				R4f(W, &AA, &BB, &CC, &DD, &EE, r);
				break;
			default :
				printf("\nERROR\n");
		}
		
		//printf("r = %d\t",r);
		//printf("%08x %08x %08x %08x %08x\n", AA, BB, CC, DD, EE);
			
        }
	//change
	a += AA;
	b += BB;
	c += CC;
	d += DD;
	e += EE;
}

void R1f(uint32_t *W, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i){
	uint64_t T;
	T = (uint64_t)rotateLeft(*AA, 5) +(uint64_t) F(*BB, *CC, *DD) + (uint64_t)*EE + (uint64_t)K[0] + (uint64_t)W[i];//change
	*EE = *DD;
	*DD = *CC;
	*CC = rotateLeft(*BB, 30);
	*BB = *AA;
	*AA = (uint32_t)(T & 0xffffffff);//change
}

void R2f(uint32_t *W, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i){
        uint64_t T;
	T = (uint64_t)rotateLeft(*AA, 5) +(uint64_t) G(*BB, *CC, *DD) + (uint64_t)*EE + (uint64_t)K[1] + (uint64_t)W[i];
        *EE = *DD;
        *DD = *CC;
        *CC = rotateLeft(*BB, 30);
        *BB = *AA;
        //*AA = T;//change
	*AA = (uint32_t)(T & 0xffffffff);
}

void R3f(uint32_t *W, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i){
        uint64_t T;
        //T = rotateLeft(*AA, 5) + H(*BB, *CC, *DD) + *EE + K[2] + X[i];
        T = (uint64_t)rotateLeft(*AA, 5) +(uint64_t) H(*BB, *CC, *DD) + (uint64_t)*EE + (uint64_t)K[2] + (uint64_t)W[i];//change
        *EE = *DD;
        *DD = *CC;
        *CC = rotateLeft(*BB, 30);
        *BB = *AA;
        //*AA = T;
	*AA = (uint32_t)(T & 0xffffffff);
}

void R4f(uint32_t *W, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i){
        uint64_t T;
        
	T = (uint64_t)rotateLeft(*AA, 5) +(uint64_t) G(*BB, *CC, *DD) + (uint64_t)*EE + (uint64_t)K[3] + (uint64_t)W[i];
        *EE = *DD;
        *DD = *CC;
        *CC = rotateLeft(*BB, 30);
        *BB = *AA;
        
	*AA = (uint32_t)(T & 0xffffffff);
}

