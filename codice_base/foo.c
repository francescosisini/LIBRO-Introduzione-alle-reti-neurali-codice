#include <stdio.h>
#include <stdlib.h>
float foo(float a, float b);
int main ()
{
float a,b,r;
 a=5.1;
 b=4.9;
 r=foo(a,b);
 printf("a=%f, b=%f, r=%f\n",a,b,r);
}
float foo(float a, float b)
{
  a=-b+1;
  return 2.1*a;
}
