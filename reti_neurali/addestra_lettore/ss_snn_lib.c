#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ss_snn_lib.h"
#define D_SIZE 784

void layer_writedown
(FILE * stream,double *v_w, int n_dend, int n_perc)
{
  fwrite(v_w, sizeof(double), n_dend*n_perc, stream);
}
void layer_read
(FILE * stream,double *v_w, int n_dend, int n_perc)
{
  fread(v_w, sizeof(double), n_dend*n_perc, stream);
}
void layer_feed_forward
(double v_s[],double v_y[],double v_w[],double v_x[],int n_perc, int n_dend)
{
  for(int i=0;i<n_perc;i++)
    {
      /*calcola l'output per ogni percettrone*/
      v_s[i]=perc_calc_output(v_w+i*(n_dend+1),v_x,n_dend);
      v_y[i]=activ_function(v_s[i]);
    }
}
void perc_correzione
(double v_w[],double v_x[],double z,double d,double rate,int n_dend)
{
  /* cicolo sui dendriti */
  for(int i=0;i<n_dend+1;i++)
    {
      v_w[i]=v_w[i]+rate*v_x[i]*(d)*Dactiv_function(z);
    }
}
void layer_map_out_in
(double v_x[],double v_y[], int n_dend)
{
  v_x[0]=1;
  for(int i=1;i<n_dend+1;i++)v_x[i]=v_y[i-1];
}
double perc_calc_output
(double v_w[],double v_x[],int n_dend)
{
  double a=0;
  /*somma pesata degli stimoli di ingresso*/
  for(int i=0;i<n_dend+1;i++) a=a+v_w[i]*v_x[i];
  /*Attivazione del percettrone*/
  return a;
}
double activ_function
(double summed_input)
{
  double r=1/(1+exp(-summed_input));
  return r;
}
double Dactiv_function(double summed_input)
{
  double r=activ_function(summed_input);
  return r*(1-r);//corretta, fare i conti!
}
int get_image
(int * o,int * out_label,FILE * in_stream)
{
  int r = fscanf(in_stream,"%d",out_label);
  for(int i=0; i<D_SIZE; i++)
    r += fscanf(in_stream,",%d",o+i);
  return r;
}
void print_object
(double x[],int r, int c,int R,int C)
{
  double min,max;
  min=10;
  max=-10;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
	if(x[i*c+j]>max) max=x[i*c+j];
	if(x[i*c+j]<min) min=x[i*c+j];
      }
  double i_range=max-min;
  double max_c=255;
  double min_c=0;
  double c_range=max_c-min_c;
  double conv=c_range/i_range;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
	double gl;
	gl=x[i*c+j];
	int col=max_c-(min_c+(double)(gl-min)*conv)+min_c;
	if(col<0)printf("%f",gl);
	//if(gl>0.9) col=0;
	printf("\x1b[%d;%dH\x1b[48;5;%dm  \x1b[0m",i+R,2*j+C,col);
      }
  fflush(stdout);
}
