#include <stdint.h>
#include <math.h>
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include "imgops.h"
void draw_rectangle( uint8_t array[],
		          unsigned int cols,
		          unsigned int rows,
		          int x,
		          int y,
		          int rect_width,
		          int rect_height,
		          uint8_t color )
							{
								int sx=1,sy=1;

							  if(rect_width<0){sx=-1;}
								if(rect_height<0){sy=-1;}

								int nx=x+rect_width-1,ny=y+rect_height-1;

								if (rect_width<0) {nx=x+rect_width+1;}
								if (rect_height<0) {ny=y+rect_height+1;}

								if (rect_width!=0 && rect_height!=0)
								{

											for (int m = x; m < x+rect_width*sx ; m++)
											{
												if((x+sx*(m-x))>=0 && (x+sx*(m-x)) <cols && y>=0 && y<rows)
												{
													array[(x+sx*(m-x))+y*cols]=color;
												}
												if((x+sx*(m-x))>=0 && (x+sx*(m-x)) <cols && ny>=0 && ny<rows)
												{
													array[(x+sx*(m-x))+ny*cols]=color;
												}
											}
											for (int n = y; n< y+rect_height*sy ; n++ )
											{
												if((y+sy*(n-y))>=0 && (y+sy*(n-y)) < rows && x>=0 && x<cols)
												{
													array[x+(y+sy*(n-y))*cols]= color;
												}
												if((y+sy*(n-y))>=0 && (y+sy*(n-y)) < rows && nx>=0 && nx<cols)
												{
													array[nx+(y+sy*(n-y))*cols]= color;
												}
											}
								}
							}
