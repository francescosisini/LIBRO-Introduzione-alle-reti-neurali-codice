#include <stdio.h>
/*
* Stampa della tavola pitagorica
*/
int main()
{
  for(int i=1;i<=12;i++)
    {
      for(int j=1;j<=12;j++)
	{
	  printf("%d\t",i*j);
	}
      printf("\n");
    }
}
