#include  "FPToolkit.c"
#include <complex.h>

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

    for(int j = 0; j < swidth; j++){
        for(int i = 0; i < sheight; i++){
            //scale to imaginary plane
            imagX = (j - swidth/2.0) * 4.0/swidth;
            imagY = (i - sheight/ 2.0) * 4.0/sheight;
            c = imagX + imagY * I;
            z = 0 + 0 * I;
            //feed into loop
            int k;
            for(k = 0; k < 100; k++){
                z =  z * z + c;

                if(cabs(z) > 100){
                    break;
                }
            }
            //plot
            x = creal(z); 
            y = cimag(z);
            a = (int) x;
            b = (int) y;

            if(cabs(z) > 100){//background
                G_rgb (0.8, 0.0, cabs(z)/255.0); // blue
            }
            else{//fractal part
                //G_rgb (0.0, (y/x), (y/x)) ; // y and y are pretty small
                //G_rgb (0.5, (x/y)*(x/y), (x/y)) ; // pretty good
                //G_rgb (1.0, abs(1.0-(x/y)), abs(1.0-(x/y))) ; 
                G_rgb (k/100.0, (x/y)*(x/y)*.5, .4) ; // blue
            }
            G_point (j, i) ; // hard to see
        }
    }

    int key ;   
    key =  G_wait_key() ; // pause so user can see results

    G_save_image_to_file("./img/tiedyeMandelbrot.xwd") ;
    G_save_to_bmp_file("./img/tiedyeMandelbrot.bmp") ;
}



