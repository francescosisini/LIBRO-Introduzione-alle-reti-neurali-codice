#include <stdio.h>
/*
* Variabili e indirizzi di memoria
*/
int main()
{
  int n_in=8;
  int* p;
  p=&n_in;
  *p=10;
  printf("Neuroni di input = %d\n",n_in);
}
