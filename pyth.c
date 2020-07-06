

#include  "FPToolkit.c"
#include <math.h>

double max_dub(double a, double b);
double min_dub(double a, double b);
double distance(double a, double b);
void find_third_point(double*, double*);
void b_square(double*, double*);


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
    b_square(triangleXs, triangleYs);
    double bDist = distance(p[1], q[1]);
     
    //a leg square
    G_rgb(148/255.0, 224/255.0, 254/255.0) ; //blue
    double aDist = distance(p[0], q[0]);
    G_fill_rectangle (min_dub(p[0], q[0]), min_dub(p[1], q[1]) - distance(p[0], q[0]), distance(p[0], q[0]), distance(p[0], q[0])) ;
    //G_rectangle (lowleftx, lowlefty, width, height) ;

    //c square  
    G_rgb (0.0, 0.0, 0.0) ; // black
    double cSquareXs[4];
    double cSquareYs[4];
    cSquareXs[0] = triangleXs[0];
    cSquareYs[0] = triangleYs[0];
    cSquareXs[1] = triangleXs[1];
    cSquareYs[1] = triangleYs[1];

    //case 1 positive slope
    if((triangleXs[1] - triangleXs[0] > 0 && triangleYs[1] - triangleYs[0] > 0) || 
       (triangleXs[1] - triangleXs[0] < 0 && triangleYs[1] - triangleYs[0] < 0)){
        cSquareXs[3] = min_dub(triangleXs[0], triangleXs[1]) - bDist;
        cSquareYs[3] = min_dub(triangleYs[0], triangleYs[1]) + aDist;
        cSquareXs[2] = max_dub(triangleXs[0], triangleXs[1]) - bDist;
        cSquareYs[2] = max_dub(triangleYs[0], triangleYs[1]) + aDist;
    }
    // case 2 negative slope
    else{
        cSquareXs[3] = min_dub(triangleXs[0], triangleXs[1]) + bDist;
        cSquareYs[3] = max_dub(triangleYs[0], triangleYs[1]) + aDist;
        cSquareXs[2] = max_dub(triangleXs[0], triangleXs[1]) + bDist;
        cSquareYs[2] = min_dub(triangleYs[0], triangleYs[1]) + aDist;
    }

    int numxy = 4 ;
    G_polygon (cSquareXs, cSquareYs, numxy) ;

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
    if((xs[1] - xs[0] > 0 && ys[1] - ys[0] > 0) || (xs[1] - xs[0] < 0 && ys[1] - ys[0] < 0)){
        xs[2] = max_dub(xs[1], xs[0]);
        ys[2] = min_dub(ys[1], ys[0]);
    }
    //case 2 slope is negative
    else{
        xs[2] = min_dub(xs[1], xs[0]);
        ys[2] = min_dub(ys[1], ys[0]);
    }
}

void b_square(double* xs, double* ys){
    double x;
    double y;
    double b = distance(ys[1], ys[0]);

    if((xs[1] - xs[0] > 0 && ys[1] - ys[0] > 0) || (xs[1] - xs[0] < 0 && ys[1] - ys[0] < 0)){
        x =  max_dub(xs[0], xs[1]);
        y = min_dub(ys[0], ys[1]);
    }
    else{
        x = min_dub(xs[0], xs[1]) - b;
        y = min_dub(ys[0], ys[1]);
    }

    G_rgb(158/255.0, 204/255.0, 111/255.0); // green
    G_fill_rectangle (x, y, b, b);
}

