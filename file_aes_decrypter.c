//
// Created by gavin on 19-3-15.
//
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "file_aes.h"

static void phex(uint8_t *str);

int main(int argc, char **argv) {
  char *input;
  char *output;
  char *key;

  int opt;
  while ((opt = getopt(argc, argv, "o:i:k:")) != EOF)
    switch (opt) {
    case 'i':
      input = optarg;
      break;
    case 'o':
      output = optarg;
      break;
    case 'k':
      key = optarg;
      break;
    }

  if (input == NULL) {
    printf("Miss input file. eg: -i <file>\n");
    return -1;
  }

  if (output == NULL) {
    printf("Miss output file. eg: -o <file>\n");
    return -1;
  }

  if (key == NULL) {
    printf("Miss key. eg: -k <keycode>\n");
  }

  int keylen = strlen(key);

  if (keylen != 16) {
    printf("KeyCode length is %d, but it must be 16\n", keylen);
  }

  printf("KEY: ");
  phex(key);

  decrypt(output, input, key);

  return 0;
}

static void phex(uint8_t *str) {
  unsigned char i;
  for (i = 0; i < 16; ++i)
    printf("%.2x", str[i]);
  printf("\n");
}