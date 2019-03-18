//
// Created by gavin on 19-3-15.
//
#include <stdio.h>

#include "file_aes.h"

void encrypt(const char *originFile, const char *cipherFile, uint8_t *key) {
  struct AES_ctx ctx;
  AES_init_ctx(&ctx, key);

  // Open File
  FILE *fd = fopen(originFile, "re");
  FILE *fd2 = fopen(cipherFile, "we");

  uint8_t buffer[16];
  size_t size = 0;

  uint8_t header[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  uint32_t line = 0;
  uint32_t offset = 0;
  uint8_t tempBytes[4];

  // Save Header
  fwrite(header, sizeof(uint8_t), 16, fd2);

  // Save Body
  while ((size = fread(buffer, sizeof(uint8_t), 16, fd)) > 0) {
    line++;
    if (size < 16) {
      offset = (uint32_t)(16 - size);
      for (size_t index = 16 - offset; index < 16; index++) {
        buffer[index] = '\0';
      }
    }
    AES_ECB_encrypt(&ctx, buffer);
    fwrite(buffer, sizeof(uint8_t), 16, fd2);
  }

  // Update Header
  int2bytes(line, tempBytes);
  for (size_t i = 0; i < 4; i++) {
    header[i] = tempBytes[i];
  }
  int2bytes(offset, tempBytes);
  for (size_t i = 0; i < 4; i++) {
    header[4 + i] = tempBytes[i];
  }
  AES_ECB_encrypt(&ctx, header);
  fseek(fd2, 0, SEEK_SET);
  fwrite(header, sizeof(uint8_t), 16, fd2);

  // Close File
  fclose(fd);
  fclose(fd2);
}

void decrypt(const char *originFile, const char *cipherFile, uint8_t *key) {
  struct AES_ctx ctx;
  AES_init_ctx(&ctx, key);

  // Open File
  FILE *fd = fopen(cipherFile, "re");
  FILE *fd2 = fopen(originFile, "we");

  uint8_t buffer[16];
  uint32_t lines = 0;

  uint32_t line = 0;
  uint32_t offset = 0;
  uint8_t tempBytes[4];

  // Parse Header
  if (fread(buffer, sizeof(uint8_t), 16, fd)) {
    AES_ECB_decrypt(&ctx, buffer);
  }
  for (size_t i = 0; i < 4; i++) {
    tempBytes[i] = buffer[i];
  }
  line = bytes2int(tempBytes);
  for (size_t i = 0; i < 4; i++) {
    tempBytes[i] = buffer[4 + i];
  }
  offset = bytes2int(tempBytes);

  // Parse Body
  while (fread(buffer, sizeof(uint8_t), 16, fd)) {
    lines++;
    AES_ECB_decrypt(&ctx, buffer);
    if (line == lines) {
      fwrite(buffer, sizeof(uint8_t), 16 - offset, fd2);
    } else {
      fwrite(buffer, sizeof(uint8_t), 16, fd2);
    }
  }

  // Close File
  fclose(fd);
  fclose(fd2);
}

void int2bytes(uint32_t i, uint8_t *bytes) {
  bytes[0] = (uint8_t)(0xFF & i);
  bytes[1] = (uint8_t)((0xFF00 & i) >> 8);
  bytes[2] = (uint8_t)((0xFF0000 & i) >> 16);
  bytes[3] = (uint8_t)((0xFF000000 & i) >> 24);
}

uint32_t bytes2int(uint8_t *bytes) {
  uint32_t iRetVal = bytes[0] & 0xFF;
  iRetVal |= ((bytes[1] << 8) & 0xFF00);
  iRetVal |= ((bytes[2] << 16) & 0xFF0000);
  iRetVal |= ((bytes[3] << 24) & 0xFF000000);
  return iRetVal;
}
