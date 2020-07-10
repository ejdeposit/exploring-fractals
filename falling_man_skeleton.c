#include "FPToolkit.c"

// appropriate for a 600x600 window
double x[13] = {263,338,338,450,338,338,375,300,225,263,263,150,263} ;
double y[13] = {450,450,375,338,338,300,150,263,150,300,338,338,375} ;
int n = 13 ;

void rotate(double angle);

void translate (double dx, double dy)
{
  int i ;

  i = 0 ;
  while (i < n) {
    x[i] = x[i] + dx ;
    y[i] = y[i] + dy ;
    i = i + 1 ;
  }
}

void scale(double);

int main() 
{
  int q='a' ;

  //  G_choose_repl_display() ;
  G_init_graphics(600, 600) ;

  G_rgb(0,0,0) ;
  G_clear() ;

  G_rgb(0,0,1) ;
  G_fill_polygon(x,y,n) ;
  q = G_wait_key() ;
  while(q = 'q'){
      q = G_wait_key() ;
      scale(.2);
      //translate(150, 0) ;
      rotate(1.14);
      G_rgb(1,0,1) ;
      G_fill_polygon(x,y,n) ;

  }


}


void scale(double scaleF){
    double centerX = 0;
    double centerY = 0;
    for(int i=0; i<n; i++){
        centerX = centerX + x[i];
        centerY = centerY + y[i];
    }
    centerX = centerX / n;
    centerY = centerY / n;
     
    double midX;
    double midY;
    for(int i=0; i<n; i++){
        midX =  x[i]- centerX; 
        midY = y[i] -  centerY;

        midX =  midX * scaleF;
        midY =  midY * scaleF;
        
        x[i] = centerX + midX;
        y[i] = centerY + midY;
    }
}
void rotate(double angle){
    double centerX = 0;
    double centerY = 0;
    for(int i=0; i<n; i++){
        centerX = centerX + x[i];
        centerY = centerY + y[i];
    }
    centerX = centerX / n;
    centerY = centerY / n;
     
    double midX;
    double midY;
    double x1;
    double y1;
    double x2;
    double y2;
    for(int i=0; i<n; i++){
        x1 =  x[i];
        y1 =  y[i];
        x1 = x[i] - centerX;
        y1 = y[i] - centerY;
        x2 = cos(angle) * x1 - sin(angle) *  y1;
        y2 = cos(angle) * y1 + sin(angle) *  x1;
        x[i] = x2 + centerX;
        y[i] = y2 + centerY;
    }

}
