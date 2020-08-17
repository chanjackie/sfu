#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main( int argc, char* argv[] )
{
  char k;
	int numcensor = argc;
	int recentword=0, i=0;
  char currentWord[128]={0};
  while ((k = getchar())!= EOF) {
    if (isalpha(k) || k == '\'') {
      currentWord[i]=k;
      i++;
    } else {
      for (i=1;i<numcensor;i++) {
        if (strcmp(argv[i],currentWord)==0) {
          printf("CENSORED");
          recentword=1;
        }
      }
      if(recentword==0) {
        printf("%s",currentWord);
      }
      printf("%c",k);
      memset(currentWord,0,128);
      i=0;
			recentword=0;
    }
  }
  return 0;
}
