#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void MD5Padding(uint8_t *input, uint64_t size, uint8_t *output);
uint32_t rotateLeft(uint32_t x, uint32_t n);