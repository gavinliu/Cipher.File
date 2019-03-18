//
// Created by gavin on 19-3-15.
//

#ifndef CIPHER_FILE_AES_H
#define CIPHER_FILE_AES_H

#include "tiny-AES-c/aes.h"

void encrypt(const char *originFile, const char *cipherFile, uint8_t *key);

void decrypt(const char *originFile, const char *cipherFile, uint8_t *key);

uint32_t bytes2int(uint8_t *bytes);

void int2bytes(uint32_t i, uint8_t *bytes);

#endif // CIPHER_FILE_AES_H
