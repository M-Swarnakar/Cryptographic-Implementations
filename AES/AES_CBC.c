
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "aes.c"

static uint8_t PADDING[] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

unsigned char State[16];

int main() {
    unsigned char plaintext[] = {0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96, 0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A,
                                0xAE, 0x2D, 0x8A, 0x57, 0x1E, 0x03, 0xAC, 0x9C, 0x9E, 0xB7, 0x6F, 0xAC, 0x45, 0xAF, 0x8E, 0x51,
                                0x30, 0xC8, 0x1C, 0x46, 0xA3, 0x5C, 0xE4, 0x11, 0xE5, 0xFB, 0xC1, 0x19, 0x1A, 0x0A, 0x52, 0xEF,
                                0xF6, 0x9F, 0x24, 0x45, 0xDF, 0x4F, 0x9B, 0x17, 0xAD, 0x2B, 0x41, 0x7B, 0xE6, 0x6C, 0x37, 0x10};
    unsigned char key[16] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
    unsigned IV[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    unsigned roundIv[16];
    uint8_t expandedKey[4 * 11 * 4];
    uint8_t roundKey[4 * 4];
    unsigned char cipher[16*4];
    unsigned char decryptedText[16 * 4];
    unsigned char state[16];


    int plaintextSize = strlen(plaintext);


    printf("\n\nPlain Text: \n");
    
    for (int i = 0; i < 16 * 4; i++) {
        printf("%2.2x ", plaintext[i]);
    }

    for(int i = 0; i < 16; i++){
        roundIv[i] =  IV[i];
    }

    expandKey(key, expandedKey);

    for(int r = 0; r < plaintextSize/16; r++){
        for(int j = 0; j < 16; j++){
            state[j] = plaintext[16 * r +j];
            state[j] ^= roundIv[j];
        }
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                State[4 * j + i] = state[ 4 * i + j];
            }
        }
        Encyption(roundKey, expandedKey);
        for (int k = 0; k < 4; k++){
            for(int j = 0; j < 4; j++){
                roundIv[4 * k+j] = State[j * 4 + k];
                //cipher[16 * r + (4 * k + j)] = State[j * 4 + k];
            }

        }

        for(int i = 0; i < 16; i++){
            cipher[16 * r + i] = roundIv[i];
        }
    }


    //Decryption

    for(int i = 0; i < 16; i++){
        roundIv[i] =  IV[i];
    }
    for (int r = 0; r < plaintextSize/16; r++){

        for(int j = 0; j < 16; j++){
            state[j] = cipher[16 * r + j];
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                State[4 * j + i] = state[ 4 * i + j];
            }
        }

        Decryption(roundKey, expandedKey);

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                state[4 * j + i] = State[ 4 * i + j];
            }
        }

        for(int k = 0; k < 16; k++){
            state[k] ^= roundIv[k];
            plaintext[16 * r + k] = state[k];
            roundIv[k] = cipher[16 * r  + k]; // **** 
        }

    }

    printf("\n\nCipher Text: \n");
    
    for (int i = 0; i < 16 * 4; i++) {
        printf("%2.2x ", cipher[i]);
    }


    printf("\n\nDecrypted text: \n");
    for (int i = 0; i < 16 * 4; i++) {
        printf("%2.2x ", plaintext[i]);
    }

}