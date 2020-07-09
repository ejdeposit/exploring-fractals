

#include  "FPToolkit.c"
#include <math.h>

double max_dub(double a, double b);
double min_dub(double a, double b);
double distance(double a, double b);
void find_third_point(double*, double*);

void tree(double, double, double, double, int, int, double, double);
void complete_rectangle(double*, double*, double, double);
int positive_slope(double x0, double y0, double x1, double y1);
//double euclidean_distance(double, double, double, double);
int grows_up(double, double, double, double);
int mid_point(double, double);
double avg_dubs(double*, int);

int main()
{
    int    swidth, sheight ;
    double p[2], q[2];
    int n;
    //malloc this later
    double xs[100];
    double ys[100];

    printf("\nenter n: ");
    scanf("%d", &n);

    // must do this before you do 'almost' any other graphical tasks 
    swidth = 600 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics
    
    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;


    G_rgb(1,0,0) ;
    
    // get user input
    G_wait_click(p) ;
    G_fill_circle(p[0],p[1],2) ;

    G_wait_click(q) ;
    G_fill_circle(q[0],q[1],2) ;   

    double a = q[0] - p[0];
    double b = q[1] - p[1];
    double r = sqrt(a * a + b * b );

    //G_rgb(0,1,0.5) ;
    //G_line(p[0],p[1], q[0],q[1]);
    double slice = 2 * M_PI/n;
    
    for(int i=0; i<n; i++){
        xs[i] = p[0] + r * cos(i*slice);
        ys[i] = p[1] + r * sin(i*slice);
        //xs[i] = r * cos(i*slice);
        //ys[i] = r * sin(i*slice);
    }

    G_rgb(148/255.0, 224/255.0, 254/255.0) ; //blue
    G_fill_polygon (xs, ys, n) ;


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


void tree(double x0, double y0, double x1, double y1, int depth, int maxDepth, double anchorX, double anchorY){
    if(depth == maxDepth){
        return;
    }
    double recXs[4];
    double recYs[4];
    double splitTriangleXs[4];
    double splitTriangleYs[4];
    double xAccum = 0;
    double yAccum = 0;

    // make rectangle
    recXs[0] = x0;
    recXs[1] = x1;
    recYs[0] = y0;
    recYs[1] = y1;

    complete_rectangle(recXs, recYs, anchorX, anchorY);
    G_rgb(148/255.0, 224/255.0, 254/255.0) ; //blue
    G_fill_polygon (recXs, recYs, 4) ;

    // make split tringle
    splitTriangleYs[0] = recYs[2];
    splitTriangleYs[1] = recYs[3];
    splitTriangleXs[0] = recXs[2];
    splitTriangleXs[1] = recXs[3];

    // make square from first to points and average 4 points to find third 
    // on triangle
    //anchor doesn't work, use avg of 4 points from previous square
    complete_rectangle(splitTriangleXs, splitTriangleYs, avg_dubs(recXs, 4), avg_dubs(recYs, 4));

    //G_rgb(158/255.0, 204/255.0, 111/255.0); // green
    //G_polygon (splitTriangleXs, splitTriangleYs, 4) ;

    for(int i=0; i<4; i++){
        xAccum =  xAccum + splitTriangleXs[i];
        yAccum =  yAccum + splitTriangleYs[i];
    }
    xAccum =  xAccum/4.0;
    yAccum =  yAccum/4.0;
    splitTriangleXs[2] = xAccum;
    splitTriangleYs[2] = yAccum;

    G_rgb(158/255.0, 204/255.0, 111/255.0); // green
    G_fill_triangle(splitTriangleXs[0], splitTriangleYs[0],  splitTriangleXs[1], splitTriangleYs[1], 
               splitTriangleXs[2], splitTriangleYs[2]);

    //recusrive calls
    tree(splitTriangleXs[2], splitTriangleYs[2], splitTriangleXs[0], splitTriangleYs[0], depth+1, maxDepth, 
    splitTriangleXs[1], splitTriangleYs[1]);
    tree(splitTriangleXs[2], splitTriangleYs[2], splitTriangleXs[1], splitTriangleYs[1], depth+1, maxDepth, 
    splitTriangleXs[0], splitTriangleYs[0]);
    
}

void complete_rectangle(double * xs, double * ys, double anchorX, double anchorY){
    double tempX, tempY;
    double a, b;
    double scaleFactor = 1.0;
    int direction = 1;
    double anchorXDir;
    double anchorYDir;
    double midX;
    double midY;
    double m;
    // y value of line, for same x value as anchor point
    double y2;

    // sort by x coord 
    if(xs[1] < xs[0]){
        tempX = xs[0];
        tempY = ys[0];
        xs[0] = xs[1];
        ys[0] = ys[1];
        xs[1] = tempX;
        ys[1] = tempY;
    }
    if(ys[0] == ys[1]){ //if horizontal line
        a  = distance(xs[0], xs[1]);
        if(anchorY < ys[0]){
            xs[2] = xs[1];
            ys[2] = ys[1] + a * scaleFactor;
            xs[3] = xs[0];
            ys[3] = ys[2];
        }
        else{
            xs[2] = xs[1];
            ys[2] = ys[1] - a * scaleFactor;
            xs[3] = xs[0];
            ys[3] = ys[2];
        }
    }
    else if(xs[0] == xs[1]){ // if vertical line
        //sort points so y[0] is lowest
        if(ys[1] < ys[0]){
            tempX = xs[0];
            tempY = ys[0];
            xs[0] = xs[1];
            ys[0] = ys[1];
            xs[1] = tempX;
            ys[1] = tempY;
        }
        a  = distance(ys[0], ys[1]);
        if(anchorX > xs[0]){ // anchor on right
            xs[2] = xs[1] - a * scaleFactor;
            ys[2] = ys[1];
            xs[3] = xs[0] - a * scaleFactor;
            ys[3] = ys[0];
        }
        else{
            xs[2] = xs[1] + a * scaleFactor;
            ys[2] = ys[1];
            xs[3] = xs[0] + a * scaleFactor;
            ys[3] = ys[0];
        }
    }
    else{  //sloped line
        // get third point on trinagle to get x and y offset for legs a and b
        find_third_point(xs, ys);

        // DOES NOT WORK
        anchorXDir = anchorX - mid_point(xs[0], xs[1]);
        anchorYDir = anchorY - mid_point(ys[0], ys[1]);

        // figure out if point is above or below line
        m = (ys[1] - ys[0]) / (xs[1] - xs[0]);
        y2 = m * (anchorX - xs[0]) + ys[0];
        

        if( positive_slope(xs[0], ys[0], xs[1], ys[1])){ //positive sloped line
            b = distance(ys[1], ys[2]);
            a = distance(xs[2], xs[0]);
            
            // if y2 is greater than anchor y, anchor is below line, go up
            if(y2 > anchorY){
                xs[2] = xs[1] - b * scaleFactor; 
                ys[2] = ys[1] + a * scaleFactor;
                xs[3] = xs[0] - b * scaleFactor;
                ys[3] = ys[0] + a * scaleFactor;
            }
            else{
                xs[2] = xs[1] + b * scaleFactor; 
                ys[2] = ys[1] - a * scaleFactor;
                xs[3] = xs[0] + b * scaleFactor;
                ys[3] = ys[0] - a * scaleFactor;
            }
        }
        else{  //negative sloped line
            b = distance(ys[0], ys[2]);
            a = distance(xs[1], xs[2]);

            // if y2 greater than anchor y, anchor is below line, go  up
            if(y2 > anchorY){
                xs[2] = xs[1] + b * scaleFactor;
                ys[2] = ys[1] + a * scaleFactor;
                xs[3] = xs[0] + b * scaleFactor;
                ys[3] = ys[0] + a * scaleFactor;
            }
            else{
                xs[2] = xs[1] - b * scaleFactor;
                ys[2] = ys[1] - a * scaleFactor;
                xs[3] = xs[0] - b * scaleFactor;
                ys[3] = ys[0] - a * scaleFactor;
            }
        }
    }
}

int positive_slope(double x0, double y0, double x1, double y1){
    if((x1 - x0 > 0 && y1 - y0 > 0) ||
        (x1 - x0 < 0 && y1 - y0 < 0)){
        return 1;
    }
    return 0;
}

int grows_up(double y0, double y1, double y2, double y3){
    if(y2 > y0 || y2> y1){
        return 0;
    }
    return 1;
}
int mid_point(double a, double b){
    double offset =  b - a; 
    offset =  offset / 2.0;
    return a + offset;
}

double avg_dubs(double * A, int n){
    double accum = 0.0;
    for(int i=0; i<n; i++){
        accum = accum + A[i];
    }
    return accum / n;
}

//double euclidean_distance(double, double, double, double){}

