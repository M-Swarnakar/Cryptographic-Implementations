
#include "AES.h"
#include "aes.c"

int main() {
    printf("\n\n ****Basic Implementation of AES****\n\n");


    int i;
    printf("\nCipher Key\n");

    for (i = 0; i < 16; i++){
        printf("%2.2x%c", Key[i], ((i+1)%16)? ' ' : '\n');
    }

    printf("\nPlaintext: \n");
    for (i = 0; i < 16; i++){
        printf("%2.2x%c", plainText[i], ((i+1)%16)? ' ' : '\n');
    }

    //**KGEN**//

    uint8_t expandedKey[4 * 11 * 4];
    uint8_t roundKey[4 * 4];

    expandKey(Key, expandedKey);

    //**Encryption**//

    Encyption(roundKey, expandedKey);

    printf("\n\nCipher Text: \n");

    for (i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            printf("%2.2x ", State[j * 4 + i]);
        } 
    }

    //**Decryption**//

    Decryption(roundKey, expandedKey);

    printf("\n\nDecrypted Plain Text: \n");
    
    for (i = 0; i < 16; i++) {
        printf("%2.2x%c", State[i], ((i+1)%16)? ' ' : '\n');
    }
return 0;
    
}