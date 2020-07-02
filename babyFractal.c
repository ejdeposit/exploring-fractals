#include  "FPToolkit.c"
#include <math.h>

double mid(double a, double b);
void copy_triangle_points(double *, double *, double *, double *);

int main(){
    int depth = 2;
    int    swidth, sheight ;
    //double p0X, p1X, p2X;
    //double p0Y, p1Y, p2Y;
    swidth = 600;
    sheight = 600;
    double xs[3];
    double ys[3];
    double oldXs[3];
    double oldYs[3];

    printf("\nplease depth: ");
    scanf("%d", &depth);

   // make first triangle
   xs[0] = 50.0;
   ys[0] = 50.0;

   xs[1] = 550.0;
   ys[1] = 50.0;
   
   ys[2] = -999;
   xs[2] = xs[0] + ((xs[1] - xs[0]) / 2.0);
   
   ys[2] = tan(M_PI/3.0) * ((xs[1] - xs[0]) / 2);
   

   G_init_graphics (swidth,sheight) ;  // interactive graphics

   // clear the screen in a given color
   G_rgb(0.0, 0.0, 0.0); // dark gray
   G_clear();

   // triangles
   G_rgb (253/255.0, 90/255.0, 0.0) ; // yellow
   G_triangle (xs[0], ys[0],  xs[1],ys[1],  xs[2],ys[2]) ;

    for(int i=0; i< depth; i++){
        copy_triangle_points( xs, ys, oldXs, oldYs);

        xs[0] = mid(oldXs[0], oldXs[2]);
        ys[0] = mid(oldYs[0], oldYs[2]);

        xs[1] = mid(oldXs[1], oldXs[2]);
        ys[1] = mid(oldYs[1], oldYs[2]);
        /*
        xs[0] = 50.0;
        ys[0] = 200.0;
        xs[1] = 250.0;
        ys[1] = 200.0;
        */

        xs[2] = mid(oldXs[0], oldXs[1]);
        ys[2] = oldYs[0];

        
        G_rgb (253/255.0, 90/255.0, 0.0) ; // yellow
        G_triangle (xs[0], ys[0],  xs[1],ys[1],  xs[2],ys[2]) ;
         
    }

   
    int key ;   
    key =  G_wait_key() ; // pause so user can see results
    /*
   double lowleftx, lowlefty, width, height ;
   double x[10], y[10] ;
   double numxy ;
   double a[20], b[20] ;
   double numab ;

   
   // must do this before you do 'almost' any other graphical tasks 
   swidth = 400 ;  sheight = 600 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear () ;

   
   // draw a point
   G_rgb (1.0, 0.0, 0.0) ; // red
   G_point (200, 580) ; // hard to see

   
   // draw a line
   G_rgb (0.0, 1.0, 0.0) ; // green
   G_line (0,0, swidth-1, sheight-1) ;

   
   // aligned rectangles
   G_rgb (0.0, 0.0, 1.0) ; // blue
   lowleftx = 200 ; lowlefty = 50 ; width = 10 ; height = 30 ;
   G_rectangle (lowleftx, lowlefty, width, height) ;
   lowleftx = 250 ; 
   G_fill_rectangle (lowleftx, lowlefty, width, height) ;

   
   // triangles
   G_rgb (1.0, 1.0, 0.0) ; // yellow
   G_triangle (10, 300,  40,300,  60,250) ;
   G_fill_triangle (10,100,  40,100,  60,150) ;

   
   // circles   
   G_rgb (1.0, 0.5, 0.0) ; // orange
   G_circle (100, 300, 75) ;
   G_fill_circle (370, 200, 50) ;

   
   // polygons
   G_rgb (0.0, 0.0, 0.0) ; // black
   x[0] = 100 ;   y[0] = 100 ;
   x[1] = 100 ;   y[1] = 300 ;
   x[2] = 300 ;   y[2] = 300 ;
   x[3] = 300 ;   y[3] = 100 ;
   x[4] = 200 ;   y[4] = 175 ;
   numxy = 5 ;
   G_polygon (x,y,numxy) ;


   G_rgb (0.4, 0.2, 0.1) ; // brown
   a[0] = 300 ;   b[0] = 400 ;
   a[1] = 350 ;   b[1] = 450 ;
   a[2] = 275 ;   b[2] = 500 ;
   a[3] = 125 ;   b[3] = 400 ;
   numab = 4 ;
   G_fill_polygon (a,b,numab) ;



   //===============================================
   
   double p[2], q[2] ;

   G_rgb(1,0,0) ;
   
   G_wait_click(p) ;
   G_fill_circle(p[0],p[1],2) ;

   G_wait_click(q) ;
   G_fill_circle(q[0],q[1],2) ;   

   G_rgb(0,1,0.5) ;
   G_line(p[0],p[1], q[0],q[1]) ;
   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results

   //G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("demo.bmp") ;
   */
}


double mid(double a, double b){
    return a + ((b - a)/2.0);
}

void copy_triangle_points(double * srcXs, double * srcYs, double * dstXs, double * dstYs){
    for(int i=0; i<3; i++){
        dstXs[i] = srcXs[i];
        dstYs[i] = srcYs[i];
    }
}


