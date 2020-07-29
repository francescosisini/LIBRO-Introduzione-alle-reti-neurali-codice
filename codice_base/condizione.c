#include <stdio.h>
/*
* ANN: Rete Neurale Artificiale
*/
int main()
{
  unsigned int n_in; //Numero di neuroni di input
  unsigned int n_out; //Numero di neuroni di output
  n_in=10;
  n_out=8;
  if(n_in!=n_out)
    {
      printf("N. di input diverso da N. di output\n");
    }
  unsigned int n_tot;//Numero totale di neuroni
  n_tot=n_in+n_out;
  printf("N. di input %u, N. di output %u, totale %u\n",n_in,n_out,n_tot);
  return 0;
}
