#include<stdio.h>
#include<stdint.h>
#include<string.h>

//#define N 512
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476
#define E 0xC3D2E1F0 

#define F(x, y, z) ((x & y) ^ (~x & z))
#define G(x, y, z) (x ^ y ^ z)
#define H(x, y, z) ((x & y) ^ (x & z) ^ (y & z)) 

uint32_t rotateLeft(uint32_t x, uint32_t n);
uint32_t rotateRight(uint32_t x, uint32_t n);
void sha1Main(unsigned char *message, uint32_t *digest, uint64_t msg_len);
void sha1Padding( uint8_t *message, uint64_t offset2, uint64_t padding_len, uint8_t *paddedMsg);
void sha1_update(uint32_t *X);
void R1f(uint32_t *X, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i);
void R2f(uint32_t *X, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i);
void R3f(uint32_t *X, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i);
void R4f(uint32_t *X, uint32_t *AA, uint32_t *BB, uint32_t *CC, uint32_t *DD, uint32_t *EE, int i);

