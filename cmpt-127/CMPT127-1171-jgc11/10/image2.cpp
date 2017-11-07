#include <stdint.h> // for uint8_t
#include <stdio.h>
#include "image2.hpp"
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

  /* Saves the image in the file filename. In a format that can be
     loaded by load().  Returns 0 on success, else a non-zero error
     code. */
  int Image::save( const char* filename ) {
    FILE* file = fopen(filename, "w");
    if (pixels!=NULL) {
      if (file == NULL) {
        puts("Failed to open file");
        return 1;
      }
      int colsrows[2];
      colsrows[0] = cols;
      colsrows[1] = rows;
      if (fwrite(colsrows, sizeof(int), 2, file) != 2) {
        puts("Failed to write image cols and rows");
        return 2;
      }
      const size_t imglen = cols*rows;
      if (fwrite(pixels, sizeof(int), imglen, file) != imglen) {
        puts("Failed to write array data");
        return 3;
      }
      fclose(file);
      return 0;
    }
    return 0;
  }

  /* Load the an image from the file filename, replacing the current
     image size and data. The file is in a format that was saved by
     save().  Returns 0 success, else a non-zero error code . */
  int Image::load( const char* filename ) {
    unsigned int colsrows[2];
    FILE* f = fopen(filename, "r");
    if (f==NULL) {
      puts("Failed to open image file for reading");
      return 1;
    }
    if (fread(colsrows, sizeof(unsigned int), 2, f) != 2) {
      puts("Empty image file detected");
      cols = 0;
      rows = 0;
      pixels = NULL;
      return 0;
    }
    cols = colsrows[0];
    rows = colsrows[1];
    pixels = new uint8_t[cols*rows];
    if (fread(pixels, sizeof(uint8_t), cols*rows, f) != cols*rows) {
      puts("Failed to read array data");
      return 3;
    }
    fclose(f);
    return 0;
  }

/*int main() {
  Image* test = new Image;
  /*if (test->resize(100,100,255) != 0) {
    exit(1);
  }
  test->set_pixel(4,0,90);
  for (int i=0;i<10;i++) {
    printf("%d\n", (int)test->pixels[i]);
  }*//*
  test->save("ayylamo");
  //test->resize(100,100,20);
  /*for (int i=0;i<10;i++) {
    printf("%d\n", (int)test->pixels[i]);
  }
  test->load("ayylamo");
  for (int i=0;i<10;i++) {
    printf("%d\n", (int)test->pixels[i]);
  }
  return 0;
}
*/
