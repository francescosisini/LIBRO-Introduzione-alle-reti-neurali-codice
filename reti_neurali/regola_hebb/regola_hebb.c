#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VROWS 4
#define MROWS 4
#define COLS 4

void matrix_dot_vector(double res[MROWS],double matrix[][VROWS],double vector[VROWS]);
void matrix_init(double res[][VROWS],double val);
void matrix_plus_matrix(double res[][VROWS],double m1[][VROWS],double m2[][VROWS]);
void matrix_to_vector(double w[][VROWS],double v[]);
void print_matrix(double x[],int r, int c,int R,int C);
int read_input_output(FILE *fp,double inp[],double out[]);
int read_test(FILE *fp,double test[]);
void scalar_dot_vector(double res[],double l,double vector[],int rows);
void vector_dot_Tvector(double res[][VROWS],double a[VROWS],double Tb[MROWS]);

int main()
{
  //Carica i dati di addestramento
  FILE * f=fopen("data.txt","rt");
  if(f==0) exit(1);

  double lambda;
  double in[VROWS];
  double out[VROWS];
  double M[VROWS][COLS];
  double DM[VROWS][COLS];
  double v[VROWS*VROWS];

  //Legge il valore di lambda
  fscanf(f,"%lf",&lambda);

  //Inizzializza a 0 la la matrice M
  matrix_init(M,0);
  
  //Addestra la rete
  while(read_input_output(f,in,out)!=EOF)
    {
      for(int i=0;i<4;i++)printf("%lf->%lf\n",*(in+i),*(out+i));
      vector_dot_Tvector(DM,out,in);
      matrix_plus_matrix(M,M,DM);
      
    }
  
  fclose(f);
  matrix_to_vector(M,v);
  //Mostra M
  print_matrix(v,4, 4,10,50);

  //Apre il file con i dati di test
  int tn=0;
  f=fopen("test.txt","rt");
  if(f==0) exit(1);
  //Testa la rete
  while(read_test(f,in)!=EOF)
    {
      matrix_dot_vector(out,M,in);
      print_matrix(in,4, 1,10+tn*10,100);
      print_matrix(out,4, 1,10+tn*10,105);
      tn++;
    }
}

int read_input_output(FILE *fp,double inp[],double out[]){
  int r;
  r=fscanf(fp,"%lf,%lf,%lf,%lf;%lf,%lf,%lf,%lf",inp,inp+1,inp+2,inp+3,out,out+1,out+2,out+3);
  return r;
}

int read_test(FILE *fp,double test[]){
  int r;
  r=fscanf(fp,"%lf,%lf,%lf,%lf",test,test+1,test+2,test+3);
  return r;
}


void matrix_init(double res[][VROWS],double val)
{
 int r,c;
  r=c=VROWS;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
	res[i][j]=val;
      }
}

void matrix_to_vector(double w[][VROWS],double v[])
{
  int r,c;
  int k;
  r=c=VROWS;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
        k=i*VROWS+j;
        v[k]=w[i][j];
      }

}


void matrix_rand_init(double res[][VROWS],double max_val,int fr)
{
  int r,c;
  r=c=VROWS;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
	if(rand()%fr==0)
	  {
	    res[i][j]=max_val;
	  }else
	  res[i][j]=0;
	//printf("%f\t",res[i][j]
      }
}
void vector_rand_init(double res[MROWS],double max_val)
{
int c;
  c=VROWS;
  
    for(int j=0;j<c;j++)
      {
	res[j]=(double)rand()/RAND_MAX*max_val;
      }
}


void vector_init(double res[MROWS],double val){
  int c;
  c=VROWS;
  
    for(int j=0;j<c;j++)
      {
	res[j]=val;
      }
  
}

void print_matrix(double x[],int r, int c,int R,int C)
{
    
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
	double gl;
	gl=x[i*c+j];
        if(gl>=0)
          printf("\x1b[%d;%dH%0.1lf  \x1b[0m  ",i*2+R,6*j+C,gl);
        else
          printf("\x1b[%d;%dH%0.1lf  \x1b[0m  ",i*2+R,6*j+C-1,gl);
      }
  fflush(stdout);
}



void sigma(double res[],double arg[],int rows)
{
  for(int i=0;i<rows;i++)
    {
      res[i]=(arg[i]<0)?0:arg[i];
    }
}
void dsigma(double res[],double arg[],int rows)
{
  for(int i=0;i<rows;i++)
    {
      res[i]=(arg[i]<0)?0:1;
    }

}

void copy_vector(double res[],double v[],int rows)
{
  for(int i=0;i<rows;i++)
    {
      res[i]=v[i];
    }
}

void vector_hadamard_vector(double res[],double a[],double b[],int rows)
{
  for(int i=0;i<rows;i++)
    {
      res[i]=a[i]*b[i];
    }
}

void vector_plus_vector(double res[],double a[],double b[],int rows)
{
  for(int i=0;i<rows;i++)
    {
      res[i]=a[i]+b[i];
    }
}

void vector_dot_Tvector(double res[][VROWS],double a[VROWS],double Tb[MROWS])
{
   for(int i=0;i<MROWS;i++){
     for(int j=0;j<VROWS;j++){
       res[i][j]=a[i]*Tb[j];
     }
   }
}

void scalar_dot_vector(double res[],double l,double v[],int rows)
{
   for(int i=0;i<rows;i++)
    {
      res[i]=l*v[i];
    }

}

void matrix_dot_vector(double res[MROWS],double matrix[][VROWS],double vector[VROWS])
{ 
  for(int i=0;i<MROWS;i++){
    res[i]=0;
    for(int j=0;j<VROWS;j++){
      res[i]+=matrix[i][j]*vector[j];
    }
  }
}
  
  void matrix_plus_matrix(double res[][VROWS],double m1[][VROWS],double m2[][VROWS])
  { 
    for(int i=0;i<MROWS;i++){
      for(int j=0;j<VROWS;j++){
	res[i][j]=m1[i][j]+m2[i][j];
      }
    }
    
  }
void scalar_dot_matrix(double res[][VROWS],double l,double m1[][VROWS])
{
     for(int i=0;i<MROWS;i++){
      for(int j=0;j<VROWS;j++){
	res[i][j]=l*m1[i][j];
      }
    }
  
}
