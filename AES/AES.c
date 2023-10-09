#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned char sBox[256] = {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67,
0x2b, 0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa,
0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72,
0xc0, 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34,
0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 0x04, 0xc7, 0x23,
0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb,
0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a,
0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29,0xe3, 0x2f, 0x84, 0x53, 0xd1,
0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39,
0x4a, 0x4c, 0x58, 0xcf, 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d,
0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6,
0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d,
0x19, 0x73, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32,
0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62,
0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5,
0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd,
0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66,
0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1,
0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 0x8c, 0xa1,
0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
0xb0, 0x54, 0xbb, 0x16};

unsigned char iBox[256] =
{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3,
0x9e, 0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b,
0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9,
0xcb, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee,
0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 0x08, 0x2e, 0xa1,
0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d,
0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98,
0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c,
0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46,
0x57, 0xa7, 0x8d, 0x9d, 0x84, 0x90, 0xd8, 0xab, 0x00, 0x8c,
0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45,
0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1,
0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91, 0x11,
0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0,
0xb4, 0xe6, 0x73, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35,
0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 0x47,
0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62,
0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b, 0xc6,
0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a,
0xf4, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1,
0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f,
0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93,
0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5,
0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 0x17,
0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14,
0x63, 0x55, 0x21, 0x0c, 0x7d};

static const 
uint8_t Rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

void expandKey(unsigned char *secretKey, unsigned char *expandedKey);
void addRoundKey(unsigned char *state, unsigned char *roundKey);
void subBytes(unsigned char *state);
void shiftRow(unsigned char *state, char numOfRow);
void shiftRows(unsigned char *state);
unsigned char galoisMultiplication(unsigned char a, unsigned char b);
void mixColumn(unsigned char *column);
void mixColumns(unsigned char *state);
void aesRound(unsigned char *state, unsigned char *roundKey);

void invSubBytes(unsigned char *state);
void invShiftRows(unsigned char *state);
void invShiftRow(unsigned char *state, char numOfRow);
void invMixColumn(unsigned char *column);
void invMixColumns(unsigned char *state);
void aesInvRound(unsigned char *state, unsigned char *roundKey);

unsigned char Key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};
unsigned char plainText[16] = {'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
unsigned char State[16] = {'a', 'e', '3', '7', 'b', 'f', '4', '8', 'c', '1', '5', '9', 'd', '2', '6', '0'};

int main() {
    printf("\n\n ****Basic Implementation of AES****\n\n");

    int i;
    printf("\nCipher Key\n\n");

    for (i = 0; i < 16; i++){
        printf("%2.2x%c", Key[i], ((i+1)%16)? ' ' : '\n');
    }

    printf("\n\nPlaintext\n\n");

    for(i = 0; i < 16; i++){
        printf("%2.2x%c", plainText[i], ((i+1)%16)? ' ' : '\n');
    }

    //**KGEN**//

    uint8_t expandedKey[4 * 11 * 4];
    uint8_t roundKey[4 * 4];

    expandKey(Key, expandedKey);

        printf("\nRound Keys:\n");

    //**Encryption**//
    
    for( i = 0; i < 4; i++){
        roundKey[4*i] = expandedKey[4*i+3];
        roundKey[4*i+1] = expandedKey[4*i+2];
        roundKey[4*i+2] = expandedKey[4*i+1];
        roundKey[4*i+3] = expandedKey[4*i];
        
    }
    printf("\nround 0\n");
        for ( int k = 0; k<16; k++){
            printf("%2.2x ", roundKey[k]);
        }
    addRoundKey(State, roundKey);
    for (i = 1; i < 10; i++) {
        for(int j = 0; j < 4; j++){
            roundKey[4*j] = expandedKey[16 * i + 4*j+3];
            roundKey[4*j+1] = expandedKey[16 * i + 4*j+2];
            roundKey[4*j+2] = expandedKey[16 * i + 4*j+1];
            roundKey[4*j+3] = expandedKey[16 * i + 4*j];
        }

        printf("\nround %d\n", i);
        for ( int k = 0; k<16; k++){
            printf("%2.2x ", roundKey[k]);
        }
        aesRound(State, roundKey);
    }
    subBytes(State);
    shiftRows(State);

    for(int j = 0; j < 4; j++){
        roundKey[4*j] = expandedKey[16 * i + 4*j+3];
        roundKey[4*j+1] = expandedKey[16 * i + 4*j+2];
        roundKey[4*j+2] = expandedKey[16 * i + 4*j+1];
        roundKey[4*j+3] = expandedKey[16 * i + 4*j];
    }
    printf("\nround 10\n");
    for (i = 0; i<16; i++){
        printf("%2.2x ", roundKey[i]);
    }
    addRoundKey(State, roundKey);

    printf("\n\nCipher Text: \n\n");
    
    for (i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            printf("%2.2x ", State[j * 4 + i]);
        }
        
    }

    //**Decryption**//

    addRoundKey(State, roundKey);
    for(i = 9; i > 0; i--) {
        for(int j = 0; j < 4; j++){
            roundKey[4*j] = expandedKey[16 * i + 4*j+3];
            roundKey[4*j+1] = expandedKey[16 * i + 4*j+2];
            roundKey[4*j+2] = expandedKey[16 * i + 4*j+1];
            roundKey[4*j+3] = expandedKey[16 * i + 4*j];
            
        }
        aesInvRound(State, roundKey);
    }
    invShiftRows(State);
    invSubBytes(State);
    for(i = 0; i < 4; i++){
        roundKey[4*i] = expandedKey[4*i+3];
        roundKey[4*i+1] = expandedKey[4*i+2];
        roundKey[4*i+2] = expandedKey[4*i+1];
        roundKey[4*i+3] = expandedKey[4*i];
    }
    addRoundKey(State, roundKey);

    printf("\n\nDecrypted Plain Text: \n\n");
    
    for (i = 0; i < 16; i++) {
        printf("%2.2x ", State[i]);
    }

    return 0;
}

uint32_t rotateLeft(uint32_t x) {
    return ((x << 8) | (x >> (32 - 8)));
}

uint32_t subWord(uint32_t W){
    for (int i = 0; i < 4; i++) {
        uint8_t byte = (uint8_t)(W >> (i * 8));
        byte = sBox[byte];
        W &= ~(0xFF << (i * 8));
        W |= ((uint32_t)byte) << (i * 8);
    }

    return W;
}

void expandKey(unsigned char *Key, unsigned char *expandedKey) {
    uint32_t *W = (uint32_t *)expandedKey;
    uint32_t temp;

    for(int i = 0; i < (16/4); i++){
        W[i] = (Key[4 * i] << 24) | (Key[4 * i + 1] << 16) | (Key[4 * i + 2] << 8) | (Key[4 * i + 3]);
    }

    for( int i = (16/4); i < 4 * 11; i++ ){
        temp = W[i - 1];
        if(i % 4 == 0){
            temp = rotateLeft(temp);
            temp = subWord(temp);
            temp ^= (Rcon[(i / 4) - 1] << 24);
        }
        W[i] = W[i - 4] ^ temp;
    }
}

void addRoundKey(unsigned char *state, unsigned char *roundKey) {
    for (int i = 0; i < 4; i++){
        for(int j=0; j<4;j++)
            state[4 * i + j] ^= roundKey[4* j +i];
    }
}

//*****ENCRYPTION FUNCTIONS*****//

void subBytes(unsigned char *state) {
    for (int i = 0; i < 16; i++){
        state[i] = sBox[state[i]];
    }
}

void shiftRows(unsigned char *state) {
    
    for (int r = 0; r < 4; r++){
        shiftRow(state+r*4, r);
    }
}

void shiftRow(unsigned char *state, char numOfRow){
    unsigned char temp;
    for (int i = 0; i< numOfRow; i++){
        temp = state[0];
        for (int j = 0; j < 3; j++){
            state[j] = state[j+1];
        }
        state[3] = temp;
    }
}

unsigned char galoisMultiplication(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hiBitSet;
    for(counter = 0; counter < 8; counter++) {
        if ((b&1) == 1)
            p = p^a;
        hiBitSet = (a & 0x80);
        a <<= 1;
        if(hiBitSet == 0x80)
            a ^= 0x1b;
        b >>= 1; 
    }
    return p;
}

void mixColumns(unsigned char *state) {
    unsigned char column[4];

    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            column[j] = state[(j*4)+i];
        }

        mixColumn(column);

        for (int j = 0; j < 4; j++) {
            state[(j*4)+i] = column[j];
        }
    }
}

void mixColumn(unsigned char *column) {
    unsigned char copy[4];
    for (int i = 0; i < 4; i++) {
        copy[i] = column[i];
        column[i] = 0;   
    }

    unsigned char givenMatrix[16] = {2, 3, 1, 1, 1, 2, 3, 1, 1, 1, 2, 3, 3, 1, 1, 2 };

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            column[i] ^= galoisMultiplication(givenMatrix[(i*4+j)], copy[j]);
        }
    }
}

void aesRound(unsigned char *state, unsigned char *roundKey) {
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, roundKey);
}

//*****DECRYPTION FUNCTIONS*****//

void invSubBytes(unsigned char *state) {
    for (int i = 0; i < 16; i++){
        state[i] = iBox[state[i]];
    }
}

void invShiftRows(unsigned char *state) {
    
    for (int r = 0; r < 4; r++){
        invShiftRow(state+r*4, r);
    }
}

void invShiftRow(unsigned char *state, char numOfRow){
    unsigned char temp;
    for (int i = 0; i< numOfRow; i++){
        temp = state[3];
        for (int j = 3; j > 0 ; j--){
            state[j] = state[j-1];
        }
        state[0] = temp;
    }
}

void invMixColumns(unsigned char *state) {
    unsigned char column[4];

    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            column[j] = state[(j*4)+i];
        }

        invMixColumn(column);

        for (int j = 0; j < 4; j++) {
            state[(j*4)+i] = column[j];
        }
    }
}

void invMixColumn(unsigned char *column) {
    unsigned char copy[4];
    for (int i = 0; i < 4; i++) {
        copy[i] = column[i];
        column[i] = 0;   
    }

    unsigned char givenMatrix[16] = {14, 11, 13, 9, 9, 14, 11, 13, 13, 9, 14, 11, 11, 13, 9, 14 };

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            column[i] ^= galoisMultiplication(givenMatrix[(i*4+j)], copy[j]);
        }
    }
}

void aesInvRound(unsigned char *state, unsigned char *roundKey) {
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKey);
    invMixColumns(state);
}








