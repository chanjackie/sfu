/*
 * imageops.c - Simple operations on images
 *
 * C laboratory exercises.
 * Richard Vaughan, 2014.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* PAIR SECTION BEGINS - WORK WITH YOUR PARTNER ON THESE TASKS */

/*-------------------------------------------------
  PART 0: DEMONSTRATION
*/


// get the value in the array at coordinate (x,y)
uint8_t get_pixel( const uint8_t array[],
           unsigned int cols,
           unsigned int rows,
           unsigned int x,
           unsigned int y )
{
    assert(x<cols);
    assert(y<rows);
    return array[ y*cols + x ];
}

// set the pixel at coordinate {x,y} to the specified color
void set_pixel( uint8_t array[],
        unsigned int cols,
        unsigned int rows,
        unsigned int x,
        unsigned int y,
        uint8_t color )
{
    assert( x < cols );
    assert( y < rows );
    array[ y * cols + x ] = color;
}

// Set every pixel to 0 (black)
void zero( uint8_t array[],
	   unsigned int cols,
	   unsigned int rows )
{
  // your code here.
	memset( array, 0, cols*rows*sizeof(array[0]));
}

// Returns a pointer to a freshly allocated array that contains the
// same values as the original array, or a null pointer if the
// allocation fails. The caller is responsible for freeing the array
// later.
uint8_t* copy( const uint8_t array[],
           unsigned int cols,
           unsigned int rows )
{
  // your code here
	uint8_t * arraycopy = malloc(cols*rows*sizeof(uint8_t));
	if (arraycopy == 0) {
		return NULL;
	}
	for (int i=0;i<cols*rows;i++) {
		arraycopy[i] = array[i];
	}
	return arraycopy;
}



/*-------------------------------------------------
  PART 1: OPERATIONS ON THE WHOLE IMAGE
*/

/* TASK 1 - three easy functions to get started */

// Return the darkest color that appears in the array; i.e. the
// smallest value
uint8_t min( const uint8_t array[],
	     unsigned int cols,
	     unsigned int rows )
{
  // your code here
  uint8_t smallest = 255;
  for (int i=0;i<cols*rows;i++) {
	if (smallest > array[i]) {
		smallest = array[i];
	}
  }
  return smallest;
}

// Return the lightest color that appears in the array; i.e. the
// largest value
uint8_t max( const uint8_t array[],
		 unsigned int cols,
		 unsigned int rows )
{
  // your code here
  uint8_t largest = 0;
  for (int i=0;i<cols*rows;i++) {
	if (largest < array[i]) {
		largest = array[i];
	}
  }
  return largest;
}

// TASK 2

//  Replace every instance of pre_color with post_color.
void replace_color(  uint8_t array[],
		     unsigned int cols,
		     unsigned int rows,
		     uint8_t pre_color,
		     uint8_t post_color )
{
  // your code here
  for (int i=0;i<cols*rows;i++) {
	if (array[i] == pre_color) {
		array[i] = post_color;
	}
  }
}

/* TASK 3  - two functions */


// flip the image, left-to-right, like in a mirror.
void flip_horizontal( uint8_t array[],
              unsigned int cols,
              unsigned int rows )
{
  // your code here
  unsigned int i;
  unsigned int n = cols-1;
  for(int r=0;r<rows;r++) {
	for (i=0;i<n;i++) {
                int temp = array[cols*r + i];
                array[cols*r+i] = array[cols*r+n];
                array[cols*r+n] = temp;
                n--;
        }
        n = cols-1;
  }
}

// flip the image top-to-bottom.
void flip_vertical( uint8_t array[],
            unsigned int cols,
            unsigned int rows )
{
	unsigned int i = 0;
	unsigned int n = rows - 1;
	for(int r=0;r<cols;r++) {
		for (i=0;i<n;i++) {
			int temp = array[r + i*cols];
			array[r + i*cols] = array[r + n*cols];
			array[r + n*cols] = temp;
			n--;
		}
		n = rows - 1;
	}
}

/* TASK 4 */

// Find the first coordinate of the first pixel with a value that
// equals color. Search from left-to-right, top-to-bottom. If it is
// found, store the coordinates in *x and *y and return 1. If it is
// not found, return 0.
int locate_color(  const uint8_t array[],
		   unsigned int cols,
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y )
{
    // your code here
    for (int i=0;i<rows;i++) {
       for(int n=0;n<cols;n++) {
         if (array[n+i*cols] == color) {
           *x = n;
           *y = i;
           return 1;
         }
       }
    }
    return 0;
}


/* TASK 5 */

// Invert the image, so that black becomes white and vice versa, and
// light shades of grey become the corresponding dark shade.
void invert( uint8_t array[],
         unsigned int cols,
         unsigned int rows )
{
    // your code here
    for (int i=0;i<cols*rows;i++) {
      array[i] = 255 - array[i];
    }
}

/* TASK 6 */

// Multiply every pixel by scale_factor, in order to brighten or
// darken the image. Any resulting value over 255 is
// thresholded to 255.
void scale_brightness( uint8_t array[],
            unsigned int cols,
            unsigned int rows,
            double scale_factor )
{
  // your code here
  for (int i=0;i<cols*rows;i++) {
    double color = round(scale_factor*(double)array[i]);
    if (color >= 255) {
      array[i] = 255;
    } else {
      array[i] = (uint8_t)color;
    }
  }
}


/* TASK 7 */

// Normalize the dynamic range of the image, i.e. Shift and scale the
// pixel colors so that that darkest pixel is 0 and the lightest pixel
// is 255. Hint: you already wrote min() and max().
void normalize( uint8_t array[],
        unsigned int cols,
        unsigned int rows )
{
    // your code here
    uint8_t darkest = min(array,cols,rows);
    uint8_t lightest = max(array,cols,rows);
    for (int i=0;i<cols*rows;i++) {
      array[i] = (array[i]-darkest)*(255/(lightest-darkest));
    }
}

/* TASK 8 */

// Return a new image of size rows/2 by cols/2 If the original image
// has an odd number of columns, ignore its rightmost column. If the
// original image has an odd number of rows, ignore its bottom row.
// The value of a pixel at (p,q) in the new image is the average of
// the four pixels at (2p,2q), (2p+1,2q), (2p+1,2q+1), (2p,2q+1) in
// the original image.
uint8_t* half( const uint8_t array[],
	       unsigned int cols,
	       unsigned int rows )
{
  // your code here
  if (cols % 2 != 0) {
    cols--;
  }
  if (rows % 2 != 0) {
    rows--;
  }
  uint8_t *half = malloc(floor(cols/2)*floor(rows/2)*sizeof(uint8_t));
  memset(half,0,floor(cols/2)*floor(rows/2));
  int newIndex = 0;
  for (int i=0;i<rows;i+=2) {
    for (int n=0;n<cols;n+=2) {
      uint8_t one = array[n+i*cols];
      uint8_t two = array[n+i*cols+1];
      uint8_t three = array[n+(i+1)*cols];
      uint8_t four = array[n+(i+1)*cols+1];
      uint8_t average = (one+two+three+four)/4;
      half[newIndex] = average;
      newIndex++;
    }
  }
  return half;
}




/*-------------------------------------------------
  PART 2: OPERATIONS ON IMAGE SUB-REGIONS

  These functions operate only on a rectangular region of the array
  defined by a (left,top) corner (i.e. closer to the image origin) and
  (right,bottom) corner (i.e. further from the image origin).

  The region includes all the columns from [left, right-1] inclusive,
  and allthe rows from [top, bottom-1] inclusive.

  In every case, you may assume that left <= right and top <= bottom:
  do not need to test for this.

  The area of the region is right-left * bottom-top pixels, which
  implies that if left == right or top == bottom, the region has no
  area and is defined as "empty". Each function notes how to handle
  empty regions.

  In every function, use assert() to test bounds on the region
  corners.
*/

/* TASK 9 */

// Set every pixel in the region to color. If the region is empty, the
// image must be unchanged.
void region_set( uint8_t array[],
         unsigned int cols,
         unsigned int rows,
         unsigned int left,
         unsigned int top,
         unsigned int right,
         unsigned int bottom,
         uint8_t color )
{
    // your code here
    //int width = right-left;
    //int height = bottom-top;
    for (int i=top;i<bottom;i++) {
      for (int n=left;n<right;n++) {
        array[n+i*cols] = color;
      }
    }
}

/* TASK 10 */

// Return the sum of all the pixels in the region. Notice the large
// return type to handle potentially large numbers. Empty regions
// return the sum 0.
unsigned long int region_integrate( const uint8_t array[],
                    unsigned int cols,
                    unsigned int rows,
                    unsigned int left,
                    unsigned int top,
                    unsigned int right,
                    unsigned int bottom )
{
    // your code here
    unsigned long int sum = 0;
    for (int i=top;i<bottom;i++) {
      for (int n=left;n<right;n++) {
        sum+=array[n+i*cols];
      }
    }
    return sum;
}

/* TASK 11 */

// Get a new image which is a copy of the region. Empty regions return
// a null pointer. If memory allocation fails, return a null
// pointer. The caller is responsible for freeing the returned array
// later.
uint8_t* region_copy( const uint8_t array[],
              unsigned int cols,
              unsigned int rows,
              unsigned int left,
              unsigned int top,
              unsigned int right,
              unsigned int bottom )
{
    // your code here
    uint8_t* copy = malloc((right*bottom)*sizeof(uint8_t));
    int x = 0;
    for (int i=top;i<bottom;i++) {
      for (int n=left;n<right;n++) {
        copy[x] = array[n+i*cols];
        x++;
      }
    }
    if (left == right || top == bottom) {
      return NULL;
    }
    return copy;
}
