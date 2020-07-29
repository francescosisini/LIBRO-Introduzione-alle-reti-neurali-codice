#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main ()
{
  int i;
  time_t t;
  srand((unsigned) time(&t));
  while((i=rand())>RAND_MAX/4)
    {
      printf("%d è maggiore di %d\n",i,RAND_MAX/4);
    }
  return 0;
}
