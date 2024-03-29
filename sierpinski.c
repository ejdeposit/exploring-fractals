#include  "FPToolkit.c"
#include <math.h>

double mid(double a, double b);
double blend(double a, double b, double m);
void copy_triangle_points(double *, double *, double *, double *);
void sierpinski_triangle(double, double, double, double, double, double, int, int);

int main(){
    int maxDepth = 0;
    int    swidth, sheight ;
    //double p0X, p1X, p2X;
    //double p0Y, p1Y, p2Y;
    swidth = 600;
    sheight = 600;
    double xs[3];
    double ys[3];
    double oldXs[3];
    double oldYs[3];

    printf("\nplease maxDepth: ");
    scanf("%d", &maxDepth);

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
    G_rgb(196/255.0, 237/255.0, 248/255.0); // dark gray
    G_clear();

    // draw initial triangle unfilled
    G_rgb (25/255.0, 175/255.0, 221/255.0) ; // blue
    G_triangle (xs[0], ys[0],  xs[1],ys[1],  xs[2],ys[2]) ;
    
    // draw other triangles filled
    sierpinski_triangle(xs[0], ys[0], xs[1], ys[1], xs[2], ys[2], 0, maxDepth);

    int key ;   
    key =  G_wait_key() ; // pause so user can see results
    G_save_image_to_file("./img/sierpinski.xwd") ;
    G_save_to_bmp_file("./img/sierpinski.bmp") ;
}


double mid(double a, double b){
    return a + ((b - a)/2.0);
}

double blend(double a, double b, double m){
    return a + ((b - a)*m);
}

void copy_triangle_points(double * srcXs, double * srcYs, double * dstXs, double * dstYs){
    for(int i=0; i<3; i++){
        dstXs[i] = srcXs[i];
        dstYs[i] = srcYs[i];
    }
}

//void sierpinski_triangle(double *xs, double *ys, int depth, int maxDepth){
void sierpinski_triangle(double x0, double y0, double x1, double y1, double x2, double y2, int depth, int maxDepth){
    double newXs[3];
    double newYs[3];
    double startR = 7.0;
    double startG = 173.0;
    double startB = 229.0;
    double endR = 182.0;
    double endG = 210.0;
    double endB = 97.0;
    double m = ((depth + 1) * 1.0) / (maxDepth+1);
    
    // if max depth not reached generate children } 
    if(depth < maxDepth){
        //generate points for new triangle
        newXs[0] = mid(x0, x2);
        newYs[0] = mid(y0, y2);

        newXs[1] = mid(x1, x2);
        newYs[1] = mid(y1, y2);

        newXs[2] = mid(x0, x1);
        newYs[2] = y1;
         
        //printf("\ndepth: %d, maxDepth: %d, m: %lf", depth, maxDepth, m);
        //printf("\nred: %lf", blend(startR, endR, m));
        //printf("\ngreen: %lf", blend(startG, endG, m)); 
        //printf("\nblue: %lf", blend(startB, endB, m));

        //draw new triangle
        //G_rgb (25/255.0, 175/255.0, 221/255.0) ; // blue
        G_rgb (blend(startR, endR, m) / 255.0, 
               blend(startG, endG, m) / 255.0, 
               blend(startB, endB, m) / 255.0) ;
        G_fill_triangle (newXs[0], newYs[0],  newXs[1], newYs[1],  newXs[2], newYs[2]) ;
        

        // call function recursively on negative spaces
        //top
        sierpinski_triangle(newXs[0], newYs[0], newXs[1], newYs[1], x2, y2, depth+1, maxDepth);
        //left
        sierpinski_triangle(x0, y0, newXs[2], newYs[2], newXs[0], newYs[0], depth+1, maxDepth);
        //right
        sierpinski_triangle(newXs[2], newYs[2], x1, y1, newXs[1], newYs[1], depth+1, maxDepth);
    }

}

