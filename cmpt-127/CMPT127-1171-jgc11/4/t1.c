#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imgops.h"

void draw_circle(uint8_t img[], unsigned int cols, unsigned int rows,
                 int x, int y, int r, uint8_t color){
    int i;
    int n;
    double xdist;
    double ydist;
    double dist;
    if (r>0) {
      for(i = 0; i< cols; i++) {
          for(n = 0; n< rows;n++) {
              xdist = i-x+0.5;
              ydist = n-y-0.5;
              dist = sqrt(pow(xdist,2) + pow(ydist,2));
              if(dist<r) {
                  set_pixel(img, cols, rows, i,n,color);
              }
              xdist = i-x-0.5;
              ydist = n-y+0.5;
              dist = sqrt(pow(xdist,2) + pow(ydist,2));
              if(dist<r) {
                  set_pixel(img, cols, rows, i,n,color);
              }
              xdist = i-x-0.5;
              ydist = n-y-0.5;
              dist = sqrt(pow(xdist,2) + pow(ydist,2));
              if(dist<r) {
                  set_pixel(img, cols, rows, i,n,color);
              }
              xdist = i-x+0.5;
              ydist = n-y+0.5;
              dist = sqrt(pow(xdist,2) + pow(ydist,2));
              if(dist<r) {
                  set_pixel(img, cols, rows, i,n,color);
              }
          }
      }
    }
}
