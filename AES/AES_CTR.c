#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "aes.c"

unsigned char State[16];

int main() {
    unsigned char plaintext[] = {0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96, 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                                0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C, 0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                                0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11, 0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
                                0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17, 0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10};
    unsigned char key[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
    unsigned ctr[16] = {0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};

    uint8_t expandedKey[4 * 11 * 4];
    uint8_t roundKey[4 * 4];
    unsigned char cipher[16*4];
    unsigned char decryptedText[16 * 4];
    unsigned char roundCtr[16];
    unsigned char state[16];


    int plaintextSize = strlen(plaintext);

    expandKey(key, expandedKey);

    //***Encryption***//

    for(int i = 0; i < 16; i++){
        roundCtr[i] =  ctr[i];
    }

    for(int r = 0; r < plaintextSize/16; r++){
        for(int k = 0; k < 16; k++){
            state[k] = roundCtr[k];
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                State[4 * j + i] = state[ 4 * i + j];
            }
        }

        Encyption(roundKey, expandedKey);

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                state[4 * j + i] = State[ 4 * i + j];
            }
        }

        if(roundCtr[15] != 255){
            roundCtr[15] += 1;
        }else{
            roundCtr[15] = 0;
            roundCtr[14] += 1;
        } 

        for (int k = 0; k < 16; k++){
            state[k] = state[k] ^ plaintext[16 * r + k];
        }
        for (int k = 0; k < 4; k++){
            for(int j = 0; j < 4; j++){
                cipher[16 * r + (4 * k + j)] = state[j * 4 + k];
            }

        }
    }

    //***Decryption***//

    for(int i = 0; i < 16; i++){
        roundCtr[i] =  ctr[i];
    }

    for(int r = 0; r < plaintextSize/16; r++){

        for(int k = 0; k < 16; k++){
            state[k] = roundCtr[k];
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                State[4 * j + i] = state[ 4 * i + j];
            }
        }
        Encyption(roundKey, expandedKey);

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                state[4 * j + i] = State[ 4 * i + j];
            }
        }
        if(roundCtr[15] != 255){
            roundCtr[15] += 1;
        }else{
            roundCtr[15] = 0;
            roundCtr[14] += 1;
        }     

        for (int k = 0; k < 16; k++){
            state[k] = state[k] ^ cipher[16 * r + k];
        }
        for (int k = 0; k < 4; k++){
            for(int j = 0; j < 4; j++){
                decryptedText[16 * r + (4 * k + j)] = state[j * 4 + k];
            }

        }
    }

    printf("\n\nPlain text: \n");
    for (int i = 0; i < 16 * 4; i++) {
        printf("%2.2x%c", plaintext[i], ((i+1)%16)? ' ' : '\n');
    }

    printf("\nCipher Text: \n");
    
    for (int i = 0; i < 16 * 4; i++) {
        printf("%2.2x%c", cipher[i], ((i+1)%16)? ' ' : '\n');
    }

    printf("\nDecrypted text: \n");
    for (int i = 0; i < 16 * 4; i++) {
        printf("%2.2x%c", decryptedText[i], ((i+1)%16)? ' ' : '\n');
    }


}