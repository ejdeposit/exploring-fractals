

#include  "FPToolkit.c"
#include <math.h>

double max_dub(double a, double b);
double min_dub(double a, double b);
double distance(double a, double b);
void find_third_point(double*, double*);
void b_square(double*, double*, double*, double*);


int main()
{
    int    swidth, sheight ;

    // must do this before you do 'almost' any other graphical tasks 
    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics
    
    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    double p[2], q[2], r[2];
    double triangleXs[3];
    double triangleYs[3];

    G_rgb(1,0,0) ;
    
    // get user input
    G_wait_click(p) ;
    G_fill_circle(p[0],p[1],2) ;

    G_wait_click(q) ;
    G_fill_circle(q[0],q[1],2) ;   

    G_rgb(0,1,0.5) ;
    G_line(p[0],p[1], q[0],q[1]) ;

    // calculate third third point 
    triangleXs[0] = p[0];
    triangleYs[0] = p[1];
    triangleXs[1] = q[0];
    triangleYs[1] = q[1];
    find_third_point(triangleXs, triangleYs);
    
    r[0] =  triangleXs[2];
    r[1] =  triangleYs[2];

    // draw trinagle
    G_rgb(254/255.0, 246/255.0, 119/255.0); //yellow
    G_triangle (triangleXs[0], triangleYs[0],  triangleXs[1], triangleYs[1], triangleXs[2], triangleYs[2]);

    //b leg square
    //b_square(triangleXs, triangleYs,  
    G_rgb(158/255.0, 204/255.0, 111/255.0); // green
    double bDist = distance(p[1], q[1]);
    G_fill_rectangle (max_dub(p[0], q[0]), min_dub(p[1], q[1]), distance(p[0], q[0]), distance(p[1], q[1])) ;
     
    //a leg square
    G_rgb(148/255.0, 224/255.0, 254/255.0) ; //blue
    double aDist = distance(p[0], q[0]);
    G_fill_rectangle (min_dub(p[0], q[0]), min_dub(p[1], q[1]) - distance(p[0], q[0]), distance(p[0], q[0]), distance(p[0], q[0])) ;
    //G_rectangle (lowleftx, lowlefty, width, height) ;

    
    G_rgb (0.0, 0.0, 0.0) ; // black
    double x[4];
    double y[4];
    x[0] = p[0] ;   y[0] = p[1] ;
    x[1] = q[0] ;   y[1] = q[1] ;
    x[2] =  max_dub(p[0], q[0]) - bDist ;   y[2] = max_dub(p[1], q[1]) + aDist;
    x[3] = min_dub(p[0], q[0]) - bDist ;   y[3] = min_dub(p[1], p[1]) + aDist;
    int numxy = 4 ;
    G_polygon (x,y,numxy) ;


  /*
   double lowleftx, lowlefty, width, height ;
   double x[10], y[10] ;
   double numxy ;
   double a[20], b[20] ;
   double numab ;
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
   */
   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results

   //G_save_image_to_file("demo.xwd") ;
   //G_save_to_bmp_file("demo.bmp") ;
}



double max_dub(double a, double b){
   double c = b - a;
   if(c>0){
       return b;
   }
   return a;
}

double min_dub(double a, double b){
   double c = b - a;
   if(c>0){
       return a;
   }
   return b;

}

double distance(double a, double b){
    return sqrt((a - b) * (a - b));
}

void find_third_point(double * xs, double * ys){
    //case 1 slope is positve
    if(xs[1] - xs[0] > 0 && ys[1] - ys[0] > 0){
        xs[2] = max_dub(xs[1], xs[0]);
        ys[2] = min_dub(ys[1], ys[0]);
    }
    //case 2 slope is negative
    else{
        xs[2] = min_dub(xs[1], xs[0]);
        ys[2] = min_dub(ys[1], ys[0]);
    }
}

void b_square(double* triXs, double* triYs, double* recXs, double* recYs){

}

