
#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <complex.h>

double scale_imag(int num, int sdimension){
    return num * 2.0 / sdimension;
}

int main()
{
    complex u,v,w,z,c ;
    double  a,x,y ;
    int sheight=600; 
    int swidth = 600;
    double imagX;
    double imagY;

   G_init_graphics (swidth,sheight) ;  // interactive graphics
   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear () ;

    //u =  2 +  5*I ;
    //v =  1 -  3*I ;
    //w = 12 + 11*I ;
    //z = u*v - w ;
    //     
    //a = cabs(z) ;
    //x = creal(z) ;
    //y = cimag(z) ;

    //printf("The absolute value of %lf + %lf I is %lf\n",x,y,a) ;

    for(int j = 0; j < swidth; j++){
        for(int i = 0; i < sheight; i++){
            //scale to imaginary plane
            imagX = (j - swidth/2.0) * 4.0/swidth;
            imagY = (i - sheight/ 2.0) * 4.0/sheight;
            c = imagX + imagY * I;
            z = 0 + 0 * I;
            //feed into loop
            for(int k = 0; k < 100; k++){
                z =  z * z + c;
            }
            //plot
            double p = cabs(z);
            if(cabs(z) > 100){
                G_rgb (0.0, 0.0, p/255.0) ; // dark gray
            }
            else{
                G_rgb (0.0, p/255.0, 0.0) ; // dark gray
            }
            G_point (j, i) ; // hard to see
            

        }
    }

   int key ;   
   key =  G_wait_key() ; // pause so user can see results
}



