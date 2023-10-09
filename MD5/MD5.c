#include "MD5.h"

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

uint32_t AA = A;
uint32_t BB = B;
uint32_t CC = C;
uint32_t DD = D;

unsigned char plainText[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                                'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z','0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', '\0'};


static uint32_t S[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                       5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                       4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                       6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};



static uint32_t T[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                       0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                       0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                       0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                       0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                       0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                       0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                       0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                       0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                       0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                       0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                       0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                       0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                       0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                       0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                       0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static uint8_t PADDING[] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static uint8_t K[] = {0, 1, 2, 3 ,4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                      1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
                      5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
                      0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};


uint64_t length;
uint64_t bitLength;
uint32_t W[16];

#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

int main() {

    length = strlen(plainText);
    bitLength = strlen(plainText) * 8;

    uint8_t paddedMsg[64 * 4];
    MD5Padding (plainText, length, paddedMsg);

    uint32_t words[strlen(paddedMsg)];
    int j = 0;
    for(int i = 0; i < 56; i+= 4 ){
        words[j++] = (uint32_t) (paddedMsg[i+3] << 24 | paddedMsg[i+2] << 16 | paddedMsg[i+1] << 8 | paddedMsg[i]);
    }

    words[14] =  (uint32_t) (bitLength & 0xffffffff);
    words[15] = (uint32_t) (bitLength >> 32);

    int i;
    uint32_t E;
    //Round functions:

    for(i = 0; i < 64; i++){
        switch(i / 16){
            case 0:
                E = F(BB, CC, DD);
                j = i;
                break;
            case 1:
                E = G(BB, CC, DD);
                j = K[i];
                break;
            case 2:
                E = H(BB, CC, DD);
                j = K[i];
                break;
            default:
                E = I(BB, CC, DD);
                j = K[i];
                break;

        }

        uint32_t temp = DD;
        DD = CC;
        CC = BB;
        BB = BB + rotateLeft(AA + E + words[j] + T[i], S[i]);
        AA = temp;
    }

    AA += A;
    BB += B;
    CC += C;
    DD += D;

    uint32_t output[4] = {AA, BB, CC, DD};

    uint8_t digest[16];

    for(i = 0; i < 4; i++) {
        digest[(i * 4) + 0] = (uint8_t) (output[i] & 0x000000FF);
        digest[(i * 4) + 1] = (uint8_t) ((output[i] & 0x0000FF00) >> 8);
        digest[(i * 4) + 2] = (uint8_t) ((output[i] & 0x00FF0000) >> 16);
        digest[(i * 4) + 3] = (uint8_t) ((output[i] & 0xFF000000) >> 24);
    }

    printf("The plaintext:\n");
    for(i = 0; i <strlen(plainText) ; i++){
        printf("%2.2x", plainText[i]);
    }

    printf("\nThe Hash value:\n");
    for(i = 0; i <16 ; i++){
        printf("%2.2x", digest[i]);
    }

    return 0;
}


// padding function

void MD5Padding(uint8_t *input, uint64_t size, uint8_t *output) {
    int i = 0;
    while (size  % 64 != (64-8)) {
        input[size++] = PADDING[i];
        i++;
    }

    for (i = 0; i < size; i++){
        output[i] = input[i];
    }
}

//a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). So we need a shift function

uint32_t rotateLeft(uint32_t x, uint32_t n) {
    return ((x << n) | (x >> (32 - n)));
}