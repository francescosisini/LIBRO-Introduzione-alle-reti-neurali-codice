#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VROWS 3
#define MROWS 3
#define COLS 3

void matrix_dot_vector(double res[MROWS],double matrix[][VROWS],double vector[VROWS]);
void vector_dot_Tvector(double res[][VROWS],double a[VROWS],double Tb[MROWS]);
void scalar_dot_vector(double res[],double l,double vector[],int rows);
void matrix_plus_matrix(double res[][VROWS],double m1[][VROWS],double m2[][VROWS]);
void matrix_to_vector(double w[][VROWS],double v[]);
void print_object(double x[],int r, int c,int R,int C);
void matrix_init(double res[][VROWS],double val);
void print_matrix(double x[],int r, int c,int R,int C);
int main()
{
  double f1[VROWS]={1,0,1};
  double g1[VROWS]={1,1,0};
  double DA1[VROWS][COLS];
  double f2[VROWS]={1,0,-1};
  double g2[VROWS]={1,0,1};
  double DA2[VROWS][COLS];
  double f3[VROWS]={0,1,0};
  double g3[VROWS]={0,0,1};
  double DA3[VROWS][COLS];
  double r[VROWS]={1,0,1};
  double A[VROWS][COLS];
  double v[VROWS*VROWS];

  //calcolo DA1
   vector_dot_Tvector(DA1,g1,f1);
   matrix_to_vector(DA1,v);
   print_matrix(v,VROWS, COLS,10, 1);

   //calcolo DA2
   vector_dot_Tvector(DA2,g2,f2);
   matrix_to_vector(DA2,v);
   print_matrix(v,VROWS, COLS,20, 1);

   //calcolo DA3
   vector_dot_Tvector(DA3,g3,f3);
   matrix_to_vector(DA3,v);
   print_matrix(v,VROWS, COLS,30, 1);

   //Calcolo A=DA1+DA2+DA3
   matrix_init(A,0);
   matrix_plus_matrix(A,DA1,DA2);
   matrix_plus_matrix(A,A,DA3);
   matrix_to_vector(A,v);
   print_matrix(v,VROWS, COLS,40, 1);
   
   //Calcolo A*f1
   matrix_dot_vector(r,A,f1);
   print_matrix(f1,VROWS, 1,40, 22);
   print_matrix(r,VROWS, 1,40, 28);
   
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

void print_object(double x[],int r, int c,int R,int C)
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
  if(i_range==0)
    {
      printf("X MERDA!");
      printf("%f - %f \n",max,min);
      exit(1);
    }
  double max_c=255;
  double min_c=232;
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
	printf("\x1b[%d;%dH\x1b[48;5;%dm  \x1b[0m  ",i+R,2*j+C,col);

      }
  fflush(stdout);
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
