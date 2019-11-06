#include <stdlib.h>
#include <stdio.h>
#include "ss_snn_lib.h"
/*___________________________
*| benchmark_lettore.c
*| Francesco Sisini (c) 2019
*/
/* Strato (layer) 1*/
#define L1_ND 784
#define L1_NP 100
/* Strato (layer) 2*/
#define L2_ND 100
#define L2_NP 10
#define N_TEST 10000
int main(int argc,char* argv[])
{
if(argc<5)
{
printf("uso: ss_lettore <digit.csv> <layer1.w> <layer2.w>");
exit(1);
}
/* Immagine da file CSV */
int img[L1_ND];
int label;
int score=0;
/*Strato 1*/
double v_x0[L1_ND+1];/* input dei percettroni del layer 1*/
double v_t[(L1_ND+1)*L1_NP];/* NP vettori di peso denditrico*/
double v_s1[L1_NP]; /*NP valori input*/
double v_y1[L1_NP];/* NP output uno per percettrone*/
/*Strato 2*/
double v_x1[L2_ND+1];/* input dei percettroni del layer 2*/
double v_u[(L2_ND+1)*L2_NP];/* NP vettori di peso denditrico*/
double v_s2[L2_NP]; /*NP valori input*/
double v_y2[L2_NP];/* NP output uno per percettrone*/
/* carica i pesi v_t e v_u dai file */
FILE* w=fopen(argv[2],"rb");
if(w==0)
{
printf("File %s non trovato\n",argv[2]);
exit (1);
}
layer_read(w,v_t, L1_ND, L1_NP);
fclose(w);
w=fopen(argv[3],"rb");
if(w==0)
{
printf("File %s non trovato\n",argv[3]);
exit (1);
}
layer_read(w,v_u, L2_ND, L2_NP);
fclose(w);
/* carica inout dai file */
w=fopen(argv[1],"r");
if(w==0)
{
printf("File %s non trovato\n",argv[1]);
exit (1);
}
for(int ii=0;ii<N_TEST;ii++)
{
get_image(img,&label,w);
/* conversione immagine da int a double */
v_x0[0]=1;
for(int i=0;i<L1_ND;i++)
{
if(img[i]>90)v_x0[i+1]=1;//((double)img[i]/255.);
else v_x0[i+1]=0;
}
/*** PROPAGAZIONE AVANTI ***/
/** Feed Forward: Input->L1->output to L2*/
layer_feed_forward(v_s1,v_y1,v_t,v_x0,L1_NP,L1_ND);
/** Mappa y1 in x1 aggiungendo l'elemento x1_0=1*/
layer_map_out_in(v_x1, v_y1,L2_ND);
/** Feed Forward: L1->L2->output*/
layer_feed_forward(v_s2,v_y2,v_u,v_x1,L2_NP,L2_ND);
/* Valutazione output */
int imax;
double fmax=0;
for(int i=0; i<L2_NP;i++)
{
if(v_y2[i]>fmax)
{
fmax=v_y2[i];
imax=i;
}
}
if(label==imax) score++;
print_object(v_x0+1,28, 28,10,30);
fflush(stdout);
}
printf("\nScore %d/%d\n",score,N_TEST);
fclose(w);
}
