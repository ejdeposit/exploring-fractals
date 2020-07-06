

#include  "FPToolkit.c"
#include <math.h>

double max_dub(double a, double b);
double min_dub(double a, double b);
double distance(double a, double b);
void find_third_point(double*, double*);

void tree(double, double, double, double);
void complete_rectangle(double*, double*);
int positive_slope(double x0, double y0, double x1, double y1);

int main()
{
    int    swidth, sheight ;
    double p[2], q[2];

    // must do this before you do 'almost' any other graphical tasks 
    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics
    
    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    //double triangleXs[3];
    //double triangleYs[3];

    G_rgb(1,0,0) ;
    
    // get user input
    G_wait_click(p) ;
    G_fill_circle(p[0],p[1],2) ;

    G_wait_click(q) ;
    G_fill_circle(q[0],q[1],2) ;   

    G_rgb(0,1,0.5) ;
    G_line(p[0],p[1], q[0],q[1]);

    tree(p[0], p[1], q[0], q[1]);

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


void tree(double x0, double y0, double x1, double y1){
    double recXs[4];
    double recYs[4];

    recXs[0] = x0;
    recXs[1] = x1;
    recYs[0] = y0;
    recYs[1] = y1;

    complete_rectangle(recXs, recYs);
    G_rgb(148/255.0, 224/255.0, 254/255.0) ; //blue
    G_polygon (recXs, recYs, 4) ;

     
}

void complete_rectangle(double * xs, double * ys){
    double tempX, tempY;
    double a, b;
    double scaleFactor = 1.0;

    // sort by x coord 
    if(xs[1] < xs[0]){
        printf("true");
        tempX = xs[0];
        tempY = ys[0];
        xs[0] = xs[1];
        ys[0] = ys[1];
        xs[1] = tempX;
        ys[1] = tempY;
    }
    if(ys[0] == ys[1]){ //if flat line
        a  = distance(xs[0], xs[1]);
        xs[2] = xs[1];
        ys[2] = ys[1] + a * scaleFactor;
        xs[3] = xs[0];
        ys[3] = ys[2];
    }
    else{  //sloped line
        // get third point on trinagle to get x and y offset for legs a and b
        find_third_point(xs, ys);

        if( positive_slope(xs[0], ys[0], xs[1], ys[1])){ //positive sloped line
            b = distance(ys[1], ys[2]);
            a = distance(xs[2], xs[0]);
            xs[2] = xs[1] - b * scaleFactor; 
            ys[2] = ys[1] + a * scaleFactor;
            xs[3] = xs[0] - b * scaleFactor;
            ys[3] = ys[0] + a * scaleFactor;
            
        }
        else{  //negative sloped line
            b = distance(ys[0], ys[2]);
            a = distance(xs[1], xs[2]);
            xs[2] = xs[1] + b * scaleFactor;
            ys[2] = ys[1] + a * scaleFactor;
            xs[3] = xs[0] + b * scaleFactor;
            ys[3] = ys[0] + a * scaleFactor;
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

