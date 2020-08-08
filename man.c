
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
    double  x,y ;
    int sheight=600; 
    int swidth = 600;
    double imagX;
    double imagY;
    int a, b;

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

                if(cabs(z) > 100){
                    break;
                }
            }
            //plot
            //double  = cabs(z);
            //int q = (int) p;
            //int modNum = 2;
            x = creal(z); 
            y = cimag(z);
            a = (int) x;
            b = (int) y;

            if(cabs(z) > 100){//background
                //G_rgb (0.0, 0.0, (q % modNum)/255.0) ; // dark gray
                G_rgb (0.8, 0.0, cabs(z)/255.0); // blue
            }
            else{//fractal part
                //G_rgb (0.0, (q % modNum)/255.0, 0.0) ; // dark gray
                //G_rgb (0.0, 1.0, 0.0) ; // green
                //G_rgb (0.0, (y/x), (x/y)) ; // blue
                //G_rgb (0.0, (x/y), (x/y)) ; // blue
                //G_rgb (0.0, (y/x), (y/x)) ; // y very small or x very large
                G_rgb (0.3, (y/x), (x/y)) ; // y very small or x very large
            }
            G_point (j, i) ; // hard to see
            

        }
    }

   int key ;   
   key =  G_wait_key() ; // pause so user can see results
}



