#include <stdio.h>

void matrix_to_vector
(double w[][3],double v[]);
void vector_dot_Tvector
(double res[][3],double a[3],double Tb[3]);
void print_matrix
(double x[],int r, int c,int R,int C);
int main()
{
  double f1[3]={1,0,1};
  double g1[3]={1,1,0};
  double DA1[3][3];
  double f2[3]={1,0,-1};
  double g2[3]={1,0,1};
  double DA2[3][3];
  double f3[3]={0,1,0};
  double g3[3]={0,0,1};
  double DA3[3][3];
  double v[3*3];

  vector_dot_Tvector(DA1,g1,f1);
  matrix_to_vector(DA1,v);
  print_matrix(v,3,3,10, 1);
}
void vector_dot_Tvector
(double res[][3],double a[3],double Tb[3])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
       res[i][j]=a[i]*Tb[j];
    }
  }
}
void matrix_to_vector
(double w[][3],double v[])
{
 int r,c;
 int k;
 r=c=3;
 for(int i=0;i<r;i++)
  for(int j=0;j<c;j++)
  {
   k=i*3+j;
   v[k]=w[i][j];
  }
}
void print_matrix
(double x[],int r, int c,int R,int C)
{
for(int i=0;i<r;i++)
  for(int j=0;j<c;j++)
 {
  double gl;
  gl=x[i*c+j];
  if(gl>=0)
    printf("\x1b[%d;%dH%0.1lf \x1b[0m ",i*2+R,6*j+C,gl);
  else
   printf("\x1b[%d;%dH%0.1lf \x1b[0m ",i*2+R,6*j+C-1,gl);
 }
fflush(stdout);
} 
