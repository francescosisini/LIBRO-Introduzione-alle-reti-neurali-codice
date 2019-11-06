#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 *MLP Multy Layer Perceptron
 */

/*Strato (layer) 1*/
#define L1_ND 7
#define L1_NP 2

/*Strato (layer) 2*/
#define L2_ND 2
#define L2_NP 1

/*** Sezione API ***/

/* Calcola la risposta del  percettrone*/
double perc_calc_output(double v_w[],double v_x[],int n_dend);
/* Calcola l'output di uno strato  percettroni*/
void layer_feed_forward(double v_s[],double v_y[],double v_w[],double v_x[],int n_perc, int n_dend);
/* Mappa l'output v_y in v_x aggiungendo prima l'elemento v_x[0]=1*/
void layer_map_out_in(double v_x[],double v_y[], int n_dend);
/* Calcola la variazione delle connessioni dendritiche del out layer e le aggiorna */
void perc_outlayer_update(double v_w[],double y,double v_x[],double z,double d,double rate,int n_dend);
/* Calcola la variazione delle connessioni dendritiche del deep layer e le aggiorna */
void perc_deeplayer_update(double v_w_t[],double v_w_u[],double v_y_2[],double v_x[],double z,double v_s_2[],double d[],double rate,int n_dend,int n_perc_2);
  

/*** Sezione Libreria ***/

/* Calcola il valore della risposta del percettrone*/
double activ_function(double summed_input);
/* Calcola il valore della derivata della risposta del percettrone*/
double Dactiv_function(double summed_input);

int main()
{

  /*Velocita' apprendimento*/
  double rate=0.1;
  
  /*Strato 1*/
  double v_x0[L1_ND+1];/* input dei percettroni del layer 1*/
  double v_t[(L1_ND+1)*L1_NP];/* NP vettori di peso denditrico*/
  double v_Dt[(L1_ND+1)*L1_NP];/* Variazione v_t */
  double v_s1[L2_NP]; /*NP valori input*/
  double v_y1[L1_NP];/* NP output uno per percettrone*/

  /*Strato 1*/
  double v_x1[L2_ND+1];/* input dei percettroni del layer 2*/
  double v_u[(L2_ND+1)*L2_NP];/* NP vettori di peso denditrico*/
  double v_Du[(L2_ND+1)*L2_NP];/* Variazione v_u*/
  double v_s2[L2_NP]; /*NP valori input*/
  double v_y2[L2_NP];/* NP output uno per percettrone*/

  /*Output desiderato*/
  double v_d[L2_NP];/* NP output desiderato uno per percettrone*/
  
  /*Inizializza la rete dal file di input*/
  FILE * f=fopen("data_MLP_7segmenti.txt","rt");
  if(f==0) exit(1);
  char comment[200];
  /*1) 1+input*/
  fscanf(f,"%s",comment);
  for(int i=0;i<L1_ND+1;i++) fscanf(f,"%lf",v_x0+i);
  /*2) bias+pesi strato 1*/
  fscanf(f,"%s",comment);
  for(int i=0;i<L1_NP;i++)
    for(int j=0;j<L1_ND+1;j++) fscanf(f,"%lf",v_t+i*(L1_ND+1)+j);
  /*3 bias+pesi strato 2*/
  fscanf(f,"%s",comment);
  for(int i=0;i<L2_NP;i++)
    for(int j=0;j<L2_ND+1;j++) fscanf(f,"%lf",v_u+i*(L2_ND+1)+j);
  /*4 output desiderato*/
  fscanf(f,"%s",comment);
  for(int i=0;i<L2_NP;i++) fscanf(f,"%lf",v_d+i);
  
  /*Stampa input*/
   printf("x0: ");
  for(int i=0;i<L1_ND+1;i++)
    {
      printf("%lf\t",v_x0[i]);
    }
  printf("\n");

  for(int k=0;k<50;k++)
    {
      printf("\n\n\n******Cicolo %d*******",k);
  
      /*Feed Forward: Input->L1->output to L2*/
      layer_feed_forward(v_s1,v_y1,v_t,v_x0,L1_NP,L1_ND);
      
      /*Mappa y1 in x1 aggiungendo l'elemento x1_0=1*/
      layer_map_out_in(v_x1, v_y1,L2_ND);
      
      /*Stampa y1 e x1*/
      printf("y1: ");
      for(int i=0;i<L1_NP;i++)
        {
          printf("%lf\t",v_y1[i]);
        }
      printf("\n");
      
      printf("x1: ");
      for(int i=0;i<L1_NP+1;i++)
        {
          printf("%lf\t",v_x1[i]);
        }
      printf("\n");
      
      
      /*Feed Forward: L1->L2->output*/
      printf("Strato 2\n");
      layer_feed_forward(v_s2,v_y2,v_u,v_x1,L2_NP,L2_ND);
      
      /*Stampa risultato*/
      printf("\nOutput 2\n");
      for(int i=0;i<L2_NP;i++)
        {
          printf("%lf\t",v_y2[i]);
        }
      printf("\n");
      
      /*** Propagazione inversa dell'errore*/
      /* Strato 1*/
      /* cicolo sui percettroni */
      for(int i=0;i<L2_NP;i++)
        {
          perc_outlayer_update( v_u+i*(L2_ND+1),v_y2[i],v_x1,v_s2[i],v_d[i], rate,L2_ND);
        }
      printf("\n\n");
      /* Strato 2*/
      /* cicolo sui percettroni */
      for(int i=0;i<L1_NP;i++)
        {
          perc_deeplayer_update(v_t+i*(L2_ND+1),v_u+i*(L1_ND+1),v_y2,v_x0,v_s1[i],v_s2, v_d, rate,L1_ND,L2_NP);
        }
      
    }
       


  
}

void perc_outlayer_update(double v_w[],double y,double v_x[],double z,double d,double rate,int n_dend)
{
  /* cicolo sui dendriti */
  v_w[0]=v_w[0]+rate*(1*(d-y)*Dactiv_function(z));
  for(int i=1;i<n_dend+1;i++)
    {
      v_w[i]=v_w[i]+rate*v_x[i]*(d-y)*Dactiv_function(z);
      printf("d=%d, Dw=%lf\t",i,v_w[i]);
    }
  

}

/* v_w_t vettore pesi layer 1, v_w_u vettore pesi layer 2 
   n_perc_2 percettroni di output
 */
void perc_deeplayer_update(double v_w_t[],double v_w_u[],double v_y_2[],double v_x[],double z,double v_s_2[],double v_d[],double rate,int n_dend,int n_perc_2)
{
  /* cicolo sui dendriti */
  for(int i=0;i<n_dend+1;i++)
    {
      double dd=0;
      for(int j=0;j<n_perc_2;j++)
        {
          dd=dd+v_w_u[j]*(v_d[j]-v_y_2[j])*Dactiv_function(v_s_2[j]);
        }
      v_w_t[i]=v_w_t[i]+rate*v_x[i]*dd*Dactiv_function(z);
      printf("d=%d, Dw=%lf\t",i,v_w_t[i]);
    }
  

}

void layer_map_out_in(double v_x[],double v_y[], int n_dend)
{
  v_x[0]=1;
  for(int i=1;i<n_dend+1;i++)v_x[i]=v_y[i-1];
}

/*  v_s: vettore delle somme dei canali dendritici per gli n_perc percettroni
 *  v_y: vettore degli output per gli n_perc percetroni
 *  v_w: vettore dei pesi dendritici per gli n_perc percetroni
 *  v_x: vettore degli input al percettrone (uguale per tutti  gli n_perc percetroni)
 *  n_perc: numero di percettroni nello strato
 *  n_dend: numero di dendriti per percettrone */
void layer_feed_forward(double v_s[],double v_y[],double v_w[],double v_x[],int n_perc, int n_dend)
{
  for(int i=0;i<n_perc;i++)
    {
      /*calcola l'output per ogni percettrone*/
      v_s[i]=perc_calc_output(v_w+i*(n_dend+1),v_x,n_dend);
      v_y[i]=activ_function(v_s[i]);
    }
}

/*  v_w: vettore di dimensione  n_dend+1 di pesi dendritici
 *  v_x: vettore delgi n_dend+1 (c'è il bias) input al percettrone
 *  n_dend numero di dendriti  */
double perc_calc_output(double v_w[],double v_x[],int n_dend)
{
  double a=0;
  /*somma pesata degli stimoli di ingresso*/
  for(int i=0;i<n_dend+1;i++) a=a+v_w[i]*v_x[i];
 
  /*Attivazione del percettrone*/
  printf("\nInput %lf\n",a);
  for(int i=0;i<n_dend+1;i++) printf("%d) %lf*%lf=",i,v_w[i],v_x[i]);
  return a;
}
double activ_function(double summed_input)
{
  double r=tanh(summed_input);
  return r;
}
double Dactiv_function(double summed_input)
{
  double r=tanh(summed_input);
  return 1-r*r;
}





