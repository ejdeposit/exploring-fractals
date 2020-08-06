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



int main(){
    int j,q ;
    double r ;
    double toRadians = M_PI/180.0;
    double p = 1.0 / 13.0;
    int letter = 0;
    double s = 14.0;
 
    // G_choose_repl_display() ;
    G_init_graphics(800, 800) ;
    G_rgb (50.0/255, 40.0/255, 50.0/255); // dark gray
    G_clear () ;

    srand48(162) ;
 
    j = 0 ;
//j is the number of points
while (j < 1000000) {
    r = drand48() ;  // gives a random double such that 0 <= r < 1
    //E 
    if(r < 1 * p) { //rule 1
        scale(4.0/s, 1.0/s);
        letter = 1;
       
    }
    else if(r < 2 * p) { // rule 2
        scale(4.0/s, 1.0/s);
        translate(0.0, 6.5/s);
        letter = 1;
    }
    else if(r < 3 * p) { //rule 3
        scale(4.0/s, 1.0/s);
        translate(0.0, 13.0/s);
        letter = 1;
    }
    else if(r < 4 * p) { //rule 4
        scale(5.5/s, 1.0/s);
        rotate(90.0);
        //translate(0.0, 1.0/s);
        translate(1.0/s, 1.0/s);
        letter = 1;
    }
    else if(r < 5 * p) { // rule 5
        scale(5.5/s, 1.0/s);
        rotate(90.0);
        //translate(0.0, 8.0/s);
        translate(1.0/s, 7.5/s);
        letter = 1;
    }
    //J
    else if(r < 6 * p) { //rule 6
         scale(4.0/s, 1.0/s);
         translate(4.5/s, 0);
         letter = 2;
    }
    else if(r < 7 * p) { //rule 7
        scale(6.0/s, 1.0/s);
        rotate(90.0);
        translate(5.5/s, 1.0/s);
        letter = 2;
    }
    else if(r < 8 * p) { // rule 8
        scale(13.0/s, 1.0/s);
        rotate(90.0);
        translate(8.5/s, 1.0/s);
        letter = 2;
    }
    //D
    else if(r <  9 * p) { //rule 9
        scale(4.0/s, 1.0/s);
        translate(9.0/s, 0);
        letter = 3;

    }
    else if(r < 10 * p) { //rule 10
        scale(4.0/s, 1.0/s);
        translate(9.0/s, 13.0/s);
        letter = 3;
    }
    else if(r < 11 * p) { //rule 11
        scale(12.0/s, 1.0/s);
        rotate(90.0);
        translate(10.0/s, 1.0/s);
        letter = 3;
    }
    else { //doing rule 12
        scale(12.0/s, 1.0/s);
        rotate(90.0);
        translate(14.0/s, 1.0/s);
        letter = 3;
    }

   //single point in x and y and starts at 0, 0
   if(letter == 1){
        G_rgb (231.0/255, 136.0/255, 114.0/255); // dark gray
   }else if(letter == 2){
        G_rgb (167.0/255, 214.0/255, 122.0/255); // dark gray
   }
   else{
        G_rgb (152.0/255, 197.0/255, 222.0/255); // dark gray
   }
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


