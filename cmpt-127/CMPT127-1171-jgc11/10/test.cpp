#include <stdio.h>
#include <stdint.h>
#include "image.hpp"

class Image;

int main() {
  Image test;
  if (test.resize(100,100,255) != 0) {
    exit(1);
  }
  for (int i=0;i<10;i++) {
    printf("%d\n", test.pixels[i]);
  }
  return 0;
}
