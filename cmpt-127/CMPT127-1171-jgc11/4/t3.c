#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include "imgops.h"

void life(uint8_t array[], unsigned int cols, unsigned int rows) {
  uint8_t* newarr = malloc(sizeof(uint8_t)*cols*rows);
  int livenear = 0;
  for (int y=0;y<rows;y++) {
    for (int x=0;x<cols;x++) {
      if (x==0 && y==0) {
        if (get_pixel(array,cols,rows,cols-1,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,cols-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,cols-1,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y+1) != 0) {
          livenear++;
        }
      } else if (x==cols-1 && y==0) {
        if (get_pixel(array,cols,rows,x-1,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y+1) != 0) {
          livenear++;
        }
      } else if (x==0 && y==rows-1) {
        if (get_pixel(array,cols,rows,cols-1,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,cols-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,cols-1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y-1) != 0) {
          livenear++;
        }
      } else if (x==cols-1 && y==rows-1) {
        if (get_pixel(array,cols,rows,x-1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,0) != 0) {
          livenear++;
        }
      } else if (x==0) {
        if (get_pixel(array,cols,rows,cols-1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,cols-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,cols-1,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y+1) != 0) {
          livenear++;
        }
      } else if (y==0) {
        if (get_pixel(array,cols,rows,x-1,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,rows-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y+1) != 0) {
          livenear++;
        }
      } else if (x==cols-1) {
        if (get_pixel(array,cols,rows,x-1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,0,y+1) != 0) {
          livenear++;
        }
      } else if (y==rows-1) {
        if (get_pixel(array,cols,rows,x-1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,0) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,0) != 0) {
          livenear++;
        }
      } else {
        if (get_pixel(array,cols,rows,x-1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y-1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x-1,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x,y+1) != 0) {
          livenear++;
        }
        if (get_pixel(array,cols,rows,x+1,y+1) != 0) {
          livenear++;
        }
      }
      if (livenear < 2) {
        newarr[x+y*cols] = 0;
      }
      if (livenear == 2) {
        newarr[x+y*cols] = get_pixel(array,cols,rows,x,y);
      }
      if (livenear == 3) {
        newarr[x+y*cols] = 255;
      }
      if (livenear>3) {
        newarr[x+y*cols] = 0;
      }
      livenear=0;
    }
  }
  for (int i=0;i<cols*rows;i++) {
    array[i] = newarr[i];
  }
  free(newarr);
}
