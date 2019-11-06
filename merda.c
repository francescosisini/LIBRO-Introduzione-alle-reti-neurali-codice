#include <stdio.h>

float calcola_attivazione(float att_neur[]);

/*
* ANN: Calcolo dell'attivazione
*/
int main()
{
  unsigned int n_in; //Numero di neuroni di input
  unsigned int n_out; //Numero di neuroni di output
  n_in=10;
  n_out=8;
  float att=0;
  float in[10];
  in[0]=0.1;
  in[1]=0.5;
  in[2]=0.6;
  in[3]=0.11;
  in[4]=0.15;
  in[5]=0.25;
  in[6]=0.98;
  in[7]=0.5;
  in[8]=0.22;
  in[9]=0.3;
  
  att=calcola_attivazione(in);
  
  printf("Attivazione di output %f\n",att);
  return 0;
}


float calcola_attivazione(float att_neur[]) {
  float att=0;
  for(int i=0;i<10;i++)
    {
      att=att+att_neur[i];
    }
  return att;
}
