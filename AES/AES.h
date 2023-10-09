#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void expandKey(unsigned char *secretKey, unsigned char *expandedKey);
//void getRoundKey(unsigned char *expandedKey, unsigned int roundNumber);
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
void Encyption(uint8_t* roundKey, uint8_t* expandedKey);
void Decryption(uint8_t* roundKey, uint8_t* expandedKey);