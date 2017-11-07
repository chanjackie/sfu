#include <stdint.h> // for uint8_t
#include <stdio.h>
#include "image.hpp"
#include <stdlib.h>

  Image::Image()
    : cols(0),
      rows(0),
      pixels(NULL)
  {}

  /* Frees all memory allocated for img */
  Image::~Image() {
    cols = 0;
    rows = 0;
    if(pixels!=NULL) {
      delete[]pixels;
    }
  }

  /* Changes the size of an image, allocating memory as necessary, and
     setting all pixels to fillcolor. Returns 0 on success, or a non-zero error code.*/
  int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolor ) {
    rows = height;
    cols = width;
    pixels = new uint8_t[cols*rows];
    if (pixels != NULL) {
      for (int i=0;i<cols*rows;i++) {
        pixels[i] = fillcolor;
      }
      return 0;
    }
    return 1;
  }

  /* Sets the color of the pixel at (x,y) to color. Returns 0 on success, else a non-zero
     error code. If (x,y) is not a valid pixel, the call fails and the image does not change.*/
  int Image::set_pixel( unsigned int x, unsigned int y, uint8_t color ) {
    if (x>=cols || y>=rows) {
      return 1;
    }
    pixels[y*cols+x] = color;
    return 0;
  }

  /* Gets the color of the pixel at (x,y) and stores at the address pointed to
     by colorp. Returns 0 on success, else a non-zero error code. */
  int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colorp ) {
    if (colorp != NULL) {
      if (x<cols && y<rows) {
        *colorp = pixels[y*cols+x];
        return 0;
      }
    }
    return 1;
  }

/*int main() {
  Image* test = new Image;
  if (test->resize(100,100,255) != 0) {
    exit(1);
  }
  test->set_pixel(4,0,90);
  for (int i=0;i<10;i++) {
    printf("%d\n", (int)test->pixels[i]);
  }
  return 0;
}
*/
