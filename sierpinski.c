#include  "FPToolkit.c"
#include <math.h>

double mid(double a, double b);
void copy_triangle_points(double *, double *, double *, double *);
void sierpinski_triangle(double *, double *, int, int);

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
    G_rgb(0.0, 0.0, 0.0); // dark gray
    G_clear();

    // draw initial triangle unfilled
    G_rgb (253/255.0, 90/255.0, 0.0) ; // yellow
    G_triangle (xs[0], ys[0],  xs[1],ys[1],  xs[2],ys[2]) ;
    
    // draw other triangles filled
    sierpinski_triangle(xs, ys, 0, maxDepth);

    int key ;   
    key =  G_wait_key() ; // pause so user can see results
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

void sierpinski_triangle(double *xs, double *ys, int depth, int maxDepth){
//void sierpinski_triangle(double x0, double y0, double x1, double y1, double x2, double y2, int depth, int maxDepth){
    double newXs[3];
    double newYs[3];
    
    // if max depth not reached generate children } 
    if(depth < maxDepth){
        //generate points for new triangle
        newXs[0] = mid(x[0], xs[2]);
        newYs[0] = mid(ys[0], ys[2]);

        newXs[1] = mid(xs[1], xs[2]);
        newYs[1] = mid(ys[1], ys[2]);

        newXs[2] = mid(xs[0], xs[1]);
        newYs[2] = ys[1];
        
        //draw new triangle
        G_rgb (253/255.0, 90/255.0, 0.0); 
        G_fill_triangle (newXs[0], newYs[0],  newXs[1], newYs[1],  newXs[2], newYs[2]) ;
        
        //make more triangles


        // call function recursively on negative spaces

        sierpinski_triangle(xs, ys, depth+1, maxDepth);
    }

}

