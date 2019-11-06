#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VROWS 25
#define MROWS 25
#define COLS 25


void delay(int milliseconds);
void print_NN(double x[VROWS],double y[MROWS],double a[MROWS],double b[MROWS],double w[][VROWS],double dw[][VROWS]);
void matrix_dot_vector(double res[MROWS],double matrix[][VROWS],double vector[VROWS]);
void vector_plus_vector(double res[],double a[],double b[],int rows);
void vector_dot_Tvector(double res[][VROWS],double a[VROWS],double Tb[MROWS],int rows);
void vector_hadamard_vector(double res[],double a[],double b[],int rows);
void copy_vector(double res[],double v[],int rows);
void sigma(double res[],double arg[],int rows);
void dsigma(double res[],double arg[],int rows);
void scalar_dot_vector(double res[],double l,double vector[],int rows);
void scalar_dot_matrix(double res[][VROWS],double l,double m1[][VROWS]);
void matrix_to_vector(double w[][VROWS],double v[]);
void matrix_plus_matrix(double res[][VROWS],double m1[][VROWS],double m2[][VROWS]);
void matrix_init(double res[][VROWS],double val);
void matrix_rand_init(double res[][VROWS],double max_val,int fr);
void vector_rand_init(double res[MROWS],double max_val);
void vector_init(double res[MROWS],double val);
void print_object(double x[],int r, int c,int R,int C);




void matrix_to_vector(double w[][VROWS],double v[])
{
  int r,c;
  r=c=VROWS;
  for(int i=0;i<r;i++)
    for(int j=0;j<c;j++)
      {
	v[i*VROWS+j]=w[i][j];
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

void print_NN(double x[VROWS],double y[MROWS],double a[MROWS],double b[MROWS],double w[][VROWS],double dw[][VROWS])
{
    printf("\033[8;9H Weight Matrix           x-input  b-bias   a-output ground-truth");
      //Display the w-matrix
      for(int i=0;i<MROWS;i++){
	for(int j=0;j<VROWS;j++){
	  int color;
	  if(dw[i][j]<-0.05||dw[i][j]>0.05) color =91;
	  else color=34;
	  printf("\033[0;%dm\033[%d;%dH%0.1lf\033[0m",color,10+i*2,10+j*5, w[i][j]);
	  delay(0);
	}
      }
      printf("\033[%d;%dHx",12,10+VROWS*5+1);

      //Display x-vector
      for(int i=0;i<VROWS;i++){
	printf("\x1b[0;33m\033[%d;%dH%+1.1lf\x1b[0m",10+i*2,10+VROWS*5+4, x[i]);
      }
      printf("\033[%d;%dH +",12,10+VROWS*5+9);
      
      //Display b-vector
      for(int i=0;i<VROWS;i++){
	printf("\x1b[0;34m\033[%d;%dH%+.1lf\x1b[0m",10+i*2,10+VROWS*5+13, b[i]);
      }
      printf("\033[%d;%dH =",12,10+VROWS*5+18);
      
      //Display a-vector
      for(int i=0;i<MROWS;i++){
	int color;
	if(a[i]-y[i]>0.2) color=91;
	else color=92;
	printf("\x1b[0;%dm\033[%d;%dH%+1.2lf\x1b[0m",color,10+i*2,10+VROWS*5+22, a[i]);
	
      }
      
      //Display y-vector
      for(int i=0;i<MROWS;i++){
	printf("\x1b[0;32m\033[%d;%dH%+1.1lf\x1b[0m",10+i*2,10+VROWS*5+31, y[i]);
	delay(1000);
      }
      printf("\033[50;1H");    
  

}

void delay(int milliseconds){
  long pause;
  clock_t now,then;
  
  pause = milliseconds*(1000/1000);
  now = then = clock();
  while( (now-then) < pause )
    now = clock();
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

void vector_dot_Tvector(double res[][VROWS],double a[VROWS],double Tb[MROWS],int rows)
{
   for(int i=0;i<MROWS;i++){
     for(int j=0;j<VROWS;j++){
       res[i][j]=a[j]*Tb[i];
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
