#include "FPToolkit.c"

// appropriate for a 600x600 window
//double x[13] = {263,338,338,450,338,338,375,300,225,263,263,150,263} ;
//double y[13] = {450,450,375,338,338,300,150,263,150,300,338,338,375} ;
//int n = 13 ;
double x[1] = {0} ;
double y[1] = {0} ;
int n = 1 ;

void translate (double dx, double dy)
{
  int i ;

  i = 0 ;
  while (i < n) {
    x[i] = x[i] + dx ;
    y[i] = y[i] + dy ;
    i = i + 1 ;
  }
}


void scale (double sx, double sy)
{
  int i ;

  i = 0 ;
  while (i < n) {
    x[i] = sx * x[i] ;
    y[i] = sy * y[i] ;
    i = i + 1 ;
  }
}


void rotate (double degrees)
{
  double radians,c,s,t ;
  int i ;

  radians = degrees*M_PI/180.0 ;
  c = cos(radians) ;
  s = sin(radians) ;

  i = 0 ;
  while (i < n) {
     t    = c*x[i] - s*y[i] ;
     y[i] = s*x[i] + c*y[i] ;
     x[i] = t ;
     i = i + 1 ;
  }
}



int main() 
{
 int j,q ;
 double r ;
 double toRadians = M_PI/180.0;
 
 // G_choose_repl_display() ;
 G_init_graphics(800, 800) ;

 srand48(162) ;
 
 j = 0 ;
 //j is the number of points
 while (j < 1000000) {

   r = drand48() ;  // gives a random double such that 0 <= r < 1
   
    //baby looks   quarter size to me
   if(r < 0.25) { //doing rule 0
     scale(1.0/3.0, 1.0/3.0) ;
   }
   else if(r < 0.5) { //doing rule 1
     scale(1.0/3.0, 1.0/3.0) ;
     rotate(60.0);
     translate(1.0/3.0, 0) ;
   }
   else if(r < 0.75) { //doing rule 1
     scale(1.0/3.0, 1.0/3.0) ;
     rotate(-60.0);
     translate(.5, (1.0/3.0) *sin(60 * toRadians)) ;
     //translate(.5, sqrt(3.0)/6.0);
   }
   else { //doing rule 2
     scale(1.0/3.0, 1.0/3.0) ;
     translate(2.0/3.0, 0) ;
   }

   //single point in x and y and starts at 0, 0
   G_point(800*x[0] , 800*y[0]) ;
   //G_fill_circle(800*x[0] , 800*y[0] , 3) ;
   
   /*   
   translate(-300, -300) ;
   scale(0.98, 0.98) ;
   rotate(3.0) ;
   translate(300, 300) ;
   */
   j=j+1 ;
 }

 q = G_wait_key() ;

}


