#include <stdio.h>

void matrix_dot_vector
(double res[3],double matrix[][3],double vector[3]); void
matrix_plus_matrix
(double res[][3],double m1[][3],double m2[][3]);
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
  double A[3][3];
  double r[3];
  vector_dot_Tvector(DA1,g1,f1);
  matrix_to_vector(DA1,v);
  print_matrix(v,3,3,10,1);
  vector_dot_Tvector(DA2,g2,f2);
  matrix_to_vector(DA2,v);
  print_matrix(v,3,3,10,30);
  vector_dot_Tvector(DA3,g3,f3);
  matrix_to_vector(DA3,v);
  print_matrix(v,3,3,10,50);
  //Calcolo A=DA1+DA2+DA3
  matrix_plus_matrix(A,DA1,DA2);
  matrix_plus_matrix(A,A,DA3);
  matrix_to_vector(A,v);
  print_matrix(v,3,3,20, 1);
  //Calcolo A*f1
  matrix_dot_vector(r,A,f1);
  print_matrix(f1,3, 1,20, 22);
  print_matrix(r,3, 1,20, 28);
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
void matrix_plus_matrix
(double res[][3],double m1[][3],double m2[][3])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      res[i][j]=m1[i][j]+m2[i][j];
    }
  }
}
void matrix_dot_vector
(double res[3],double matrix[][3],double vector[3])
{
for(int i=0;i<3;i++){
  res[i]=0;
  for(int j=0;j<3;j++){
    res[i]+=matrix[i][j]*vector[j];
  }
 }
}
