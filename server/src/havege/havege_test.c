/*
 * This is a test programme for the Havege Algorithm library, have fun!
 */

#include <stdio.h>

#include "havege.h"

int main(int argc, char **argv) {
  havege_state st;
  unsigned char buf[8] = {0};

  // init havege_state
  havege_init(&st);
  // get the result
  havege_random((void*)&st, buf, sizeof(buf));
  // show the result
  printf("Random:\n");
  for(int i = 0; i < sizeof(buf); i++) {
    printf("0x%02X ", buf[i]);
  }
  printf("\n");
  return 0;
}
