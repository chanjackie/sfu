#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imgops.h"

void draw_rectangle(uint8_t array[], unsigned int cols, unsigned int rows,
                    int x, int y, int rect_width, int rect_height, uint8_t color) {
  if (rect_width == 0 || rect_height == 0 || x>=cols || y>=rows || x<0 || y<0) {
    return;
  }
  int signx = (rect_width<0)? -1:1;
  int signy = (rect_height<0)? -1:1;
  int cx = x+rect_width - 1;
  int cy = y+rect_height - 1;
  if (rect_width<0) {cx = x+rect_width+1;}
  if (rect_height<1) {cy = y+rect_height+1;}
  for (int i=y;i<y+rect_height*signy;i++) {
    if ((y+signy*(i-y)) >= 0 && (y+signy*(i-y)) < rows && x>= 0 && x<cols) {
      array[(y+signy*(i-y))*cols+x] = color;
    }
    if ((y+signy*(i-x))>=0 && (y+signy*(i-x)) < rows && cx>=0 && cx<cols) {
      array[(y+signy*(i-y))*cols+cx] = color;
    }
  }
  for (int i=x;i<x+rect_width*signx;i++) {
    if ((x+signx*(i-x)) >= 0 && (x+signx*(i-x)) < cols && y>= 0 && y<rows) {
      array[(x+signx*(i-x))+y*cols] = color;
    }
    if ((x+signx*(i-x))>=0 && (x+signx*(i-x)) < cols && cy>=0 && cy<rows) {
      array[(x+signx*(i-x))+cy*cols] = color;
    }
  }
}
