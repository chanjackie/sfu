#include <stdio.h>
// declaration of function implemented in scrambled.c
int scrambled( unsigned int a[], unsigned int b[], unsigned int len );
 
int main( void )
{
  unsigned int a[9] = {10, 15, 15, 5, 4, 5, 2, 1, 8};
  unsigned int b[9] = {10, 15, 15, 4, 2, 1, 8, 5, 5};
 
  if( scrambled( a, b, 9 ) == 1 )
  {
     printf( "b is a scrambled version of a\n" );
  } else {
     printf( "b has different contents to a\n" );
  }
  
  return 0;
}
