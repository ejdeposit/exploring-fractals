#include <stdlib.h>
#include  "FPToolkit.c"

int main(){
    int    swidth, sheight ;
    double startX;
    double startY;
    double endX;
    double endY;
    double diameterXOffset;
    double diameterYOffset;
    int numCircles;
    double centerX;
    double centerY;
    double xDist;
    double yDist;
    double diameter;

    //**user input**
    /*
    printf("\nplease starting coordinate x and y numbers: ");
    scanf("%lf %lf", &startX, &startY);
    printf("\nplease starting coordinate x and y numbers: ");
    scanf("%lf %lf", &endX, &endY);
    printf("\n %lf %lf", startX, startY);
    printf("\n %lf %lf", endX, endY);
    */
    //test values for start and end of line
    startX =  50;
    startY = 50;
    endX = 300;
    endY = 300;
    printf("please number of circles: ");
    scanf("%d", &numCircles);


    // **Math**
    //find diameter of circle 
    diameterXOffset =  endX - startX; 
    diameterYOffset = endY -  startY;

    diameterXOffset =  diameterXOffset / (numCircles-1);
    diameterYOffset =  diameterYOffset / (numCircles-1);

    centerX = startX;
    centerY =  startY;
    xDist = abs(startX - endX);
    yDist = abs(startY - endY);
    diameter = sqrt(xDist * xDist + yDist * yDist) / (numCircles-1) / 2;

   
    // **graphics stuff**
    // must do this before you do 'almost' any other graphical tasks 
    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics
   
    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    // draw a line
    G_rgb (0.0, 1.0, 0.0) ; // green
    G_line (startX ,startY, endX, endY) ;

    // draw draw circles

    for(int i=0; i<numCircles; i++){
       G_rgb (1.0, 0.5, 0.0) ; // orange
       G_circle (centerX, centerY, diameter) ;
        // calculate next circle location
        centerX = centerX + diameterXOffset;
        centerY = centerY + diameterYOffset;

    }
    //G_rgb (1.0, 0.0, 0.0) ; // red
    //G_point (midX, midY) ; // hard to see

    int key ;   
    key =  G_wait_key() ; // pause so user can see results

/*
   int    swidth, sheight ;
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



