
#include <stdio.h>
#include <math.h>
#include <complex.h>

int main()
{
  complex u,v,w,z ;
  double  a,x,y ;

  u =  2 +  5*I ;
  v =  1 -  3*I ;
  w = 12 + 11*I ;
  z = u*v - w ;
       
  a = cabs(z) ;
  x = creal(z) ;
  y = cimag(z) ;

  printf("The absolute value of %lf + %lf I is %lf\n",x,y,a) ;
}


