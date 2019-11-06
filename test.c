#include <stdio.h>
int read_input_output(double inp[],double out[],FILE *fp){
  fscanf(fp,"%lf,%lf,%lf,%lf;%lf,%lf,%lf,%lf",inp,inp+1,inp+2,inp+3,out,out+1,out+2,out+3);
}
int main()
{
  double a[4],b[4];
  FILE * f=fopen("data.txt","rt");
  read_input_output(a,b,f);
  for(int i=0;i<4;i++)printf("%lf->%lf\n",*(a+i),*(b+i));
}
