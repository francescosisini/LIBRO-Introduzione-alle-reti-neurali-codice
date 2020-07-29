#include <stdlib.h>
#include <stdio.h>
#include "ss_snn_lib.h"
/*___________________________
*| addestra_lettore.c
*| Francesco Sisini (c) 2019
*/
/* Strato (layer) 1*/
#define L1_ND 784
#define L1_NP 100
/* Strato (layer) 2*/
#define L2_ND 100
#define L2_NP 10
/* Velocità apprendimento*/
#define RATE 0.2
int main(int argc,char *argv[])
{
/* Epoche e campioni*/
int epoche=1;
int campioni=1;
if(argc<4)
{
printf
("uso: ss_addestra <file.csv>"
"<numero_epoche> <numero_immagini>"
"<lerning_rate> <max_sinapsi> <rnd_seed>");
exit(1);
}
if(sscanf(argv[2],"%i",&epoche)!=1)
{
printf("%s non e' un intero\n",argv[2]);
exit(1);
}
if(sscanf(argv[3],"%i",&campioni)!=1)
{
printf("%s non e' un intero\n",argv[3]);
exit(1);
}
/*Velocita' apprendimento*/
double rate=RATE;
if(argc>=5)
{
printf("ok|");
if(sscanf(argv[4],"%lf",&rate)!=1)
{
printf("%s non e' un float\n",argv[4]);
exit(1);
}
}
/*Estremo superiore del valore iniziale delle sinapsi (0 to ...)*/
double sinapsi=0.001;
if(argc>=6)
{
if(sscanf(argv[5],"%lf",&sinapsi)!=1)
{
printf("%s non e' un float\n",argv[5]);
exit(1);
}
}
/* Seme (seed) di inizializzazione dei numeri pseudocasuali */
int seed=1;
if(argc>=7)
{
if(sscanf(argv[6],"%i",&seed)!=1)
{
printf("%s non e' un int\n",argv[6]);
exit(1);
}
}
/* Immagine da file CSV */
int img[L1_ND];
/* Label da file CSV (desiderd output) */
int label;
/*Strato 1*/
double v_x0[L1_ND+1];/* input dei percettroni del layer 1*/
double v_t[(L1_ND+1)*L1_NP];/* NP vettori di peso dendritico*/
double v_Dt[(L1_ND+1)*L1_NP];/* Variazione v_t */
double v_s1[L1_NP]; /*NP valori input*/
double v_y1[L1_NP];/* NP output uno per percettrone*/
/*Strato 2*/
double v_x1[L2_ND+1];/* input dei percettroni del layer 2*/
double v_u[(L2_ND+1)*L2_NP];/* NP vettori di peso dendritico*/
double v_Du[(L2_ND+1)*L2_NP];/* Variazione v_u*/
double v_s2[L2_NP]; /*NP valori input*/
double v_y2[L2_NP];/* NP output uno per percettrone*/
/*Output desiderato*/
double v_d[L2_NP];/* NP output desiderato uno per percettrone*/
/*Carica dal file le configurazioni iniziali della rete*/
srand(seed);
/*2) bias+pesi strato 1*/
for(int i=0;i<(L1_ND+1)*L1_NP;i++)
v_t[i]=sinapsi*(double)rand()/(double)RAND_MAX;
printf
("\n Campioni: %d, epoche: %d, l-rate: %f\n",campioni, epoche, rate);
/*3) bias+pesi strato 2*/
for(int i=0;i<(L2_ND+1)*L2_NP;i++)
v_u[i]=sinapsi*(double)rand()/(double)RAND_MAX;
for(int ii=0;ii<epoche;ii++)
{
printf("\x1b[5;1HEpoca %d di %d\n",ii,epoche);
FILE* stream = fopen(argv[1], "r");
if(stream==0) exit(1);
/*Carica i dati di training ed esegue il training*/
for(int jj=0;jj<campioni;jj++)
{
if(jj%100==0)
printf("\x1b[6;1HCampione %d di %d\n",jj,campioni);
get_image(img,&label,stream);
/* conversione immagine da int a double */
v_x0[0]=1;
for(int i=0;i<L1_ND;i++)
{
if(img[i]>90)v_x0[i+1]=1;//((double)img[i]/255.);
else v_x0[i+1]=0;
//v_x0[i+1]=(double)img[i];
}
/*4 output desiderato*/
for(int i=0;i<L2_NP;i++)
{
if(i == label)
v_d[i]=1;
else
v_d[i]=0;
}
/*** PROPAGAZIONE AVANTI ***/
/** Feed Forward: Input->L1->output to L2*/
layer_feed_forward(v_s1,v_y1,v_t,v_x0,L1_NP,L1_ND);
/** Mappa y1 in x1 aggiungendo l'elemento x1_0=1*/
layer_map_out_in(v_x1, v_y1,L2_ND);
/** Feed Forward: L1->L2->output*/
layer_feed_forward(v_s2,v_y2,v_u,v_x1,L2_NP,L2_ND);
/*** CORREZIONE PER PROPAGAZIONE INVERSA ***/
/** Propagazione inversa dell'errore in L2
(v_u
<- v_y2) */
for(int i=0;i<L2_NP;i++)
{
/* correzione dei pesi (v_u) del percettrone i-esimo */
perc_correzione
( v_u+i*(L2_ND+1),v_x1,v_s2[i],v_d[i]-v_y2[i], rate,L2_ND);
}
/** Propagazione inversa dell'errore in L1*/
for(int i=0;i<L1_NP;i++)
{
double dd=0;
for(int j=0;j<L2_NP;j++)
{
/* w: peso del i-esimo dendrite del j-esimo
percettrone dello strato più esterno */
double w=v_u[j*(L2_ND+1)+i];
/* correzione
*/
dd=dd+w*(v_d[j]-v_y2[j])*Dactiv_function(v_s2[j]);
}
/* correzione del percettrone i-esimo*/
perc_correzione
(v_t+i*(L1_ND+1),v_x0,v_s1[i],dd, rate,L1_ND);
}
}
fclose(stream);
}
/*_____________________________________
*| Salva la rete
*/
FILE* sw = fopen("layer1.w", "w");
layer_writedown(sw,v_t, L1_ND, L1_NP);
fclose(sw);
sw = fopen("layer2.w", "w");
layer_writedown(sw,v_u, L2_ND, L2_NP);
fclose(sw);
}
