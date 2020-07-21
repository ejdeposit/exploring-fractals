#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "FPToolkit.c"

//char u[10000]= {'\0'};
char u[10000];
double toRadians = (2.0 * M_PI / 360.0);
double toDegrees = (360.0 / (2.0 * M_PI));



struct Node {
    char var;
    char rule[20];
    struct Node *next;
};

struct Node* find_rule(struct Node*, char key);
void string_builder(struct Node*, int);
struct Node* new_rule(char, char*);
void shift(int start, int length, int shiftSize);
void rotate_point(double * point, double detlaAngle);
void next_point(double * lastPoint, double * nextPoint, double startAngle, double deltaAngle, double forwardLen);
int string_interpreter(double *xs, double *ys, double forwardLen, double startAngle, double deltaAngle);
void string_doodler(double * xs, double * ys, int n);
double max_dub(double a, double b);
double min_dub(double a, double b);
double max_dub_array(double * A, int n);
double min_dub_array(double * A, int n);
double avg_dubs(double * A, int n);
void auto_placer(int swidth, int sheight, double startAngle, double deltaAngle, int depth, 
double * start, double * forwardLen){
    int n;
    double xMin;
    double xMax;
    double yMin;
    double yMax;
    double percentFillX;
    double percentFillY;
    double desiredPercentFill = 0.90;
    double recXs[4];
    double recYs[4];
    double recCenterX;
    double recCenterY;
    double shiftX;
    double shiftY;

    printf("swidth: %d\n", swidth);
    printf("sheight: %d\n", sheight);
    printf("startAngle: %lf\n", startAngle*toDegrees);
    printf("deltaAngle: %lf\n", deltaAngle*toDegrees);
    printf("depth: %d\n", depth);
    printf("start: %lf, %lf\n", start[0], start[1]);
    printf("forwardLen: %lf\n", *forwardLen);

    //string Doodler
    double xs[10000];
    double ys[10000];
    xs[0] = start[0];
    ys[0] = start[1];
    n = string_interpreter(xs, ys, *forwardLen, startAngle, deltaAngle);
    //string_doodler(xs, ys, n);

    //scale
    xMin = min_dub_array(xs, n);
    xMax = max_dub_array(xs, n);
    yMin = min_dub_array(ys, n);
    yMax = max_dub_array(ys, n);
    
    printf("xMin: %lf\n", xMin);
    printf("xMax: %lf\n", xMax);
    printf("yMin: %lf\n", yMin);
    printf("yMax: %lf\n", yMax);

    percentFillX =  (xMax - xMin) / swidth;
    percentFillY = (yMax - yMin) / sheight;
    //find limiting length
    if( percentFillX > percentFillY){
        printf("width is limiting\n");
        *forwardLen = *forwardLen * desiredPercentFill / percentFillX;
    }
    else{
        printf("height is limiting\n");
        *forwardLen = *forwardLen * desiredPercentFill / percentFillY;
    }
    //translate
    string_interpreter(xs, ys, *forwardLen, startAngle, deltaAngle);
    xMin = min_dub_array(xs, n);
    xMax = max_dub_array(xs, n);
    yMin = min_dub_array(ys, n);
    yMax = max_dub_array(ys, n);

    recXs[0] = xMin;
    recXs[1] = xMax;
    recXs[2] = xMax;
    recXs[3] = xMin;

    recYs[0] = yMin;
    recYs[1] = yMin;
    recYs[2] = yMax;
    recYs[3] = yMax;
    
    //G_rgb (1.0, 0.5, 0.0) ; // orange
    //G_polygon(recXs, recYs, 4);

    recCenterX = avg_dubs(recXs, 4);
    recCenterY = avg_dubs(recYs, 4);
    
    //draw circ at center of rec
    //G_rgb (1.0, 0.5, 0.0) ; // orange
    //G_fill_circle (recCenterX, recCenterY, 3) ;

    shiftX = swidth/2.0 - recCenterX;
    shiftY = sheight/2.0 - recCenterY;

    //run string intepreter again with new start
    start[0] = start[0] + shiftX;
    start[1] = start[1] + shiftY;
    xs[0] = start[0];
    ys[0] = start[1];
    string_interpreter(xs, ys, *forwardLen, startAngle, deltaAngle);
    //or just write new function to shift xs and ys

    //string_doodler(xs, ys, n);

    //test modfitying by reference
    //start[0] = 0.0;
    //start[1] = 1.0;
    //*forwardLen = 3;
}

int main()
{
    //needed by auto placer
    int swidth = 600;
    int sheight = 600 ;
    double startAngle = 0;
    double deltaAngle = 60 * toRadians;
    int depth = 3;
    struct Node* rules;

    //modifed by auto placer
    double start[2];
    start[0] = 200; 
    start[1] = 200;
    double forwardLen=1;

    // not needed by auto placer
    int key ;   
    struct Node* node;
    char axiom[10] = "F";
    int pointsLen;

    //make list of rules 
    node = new_rule('F', "F+F--F+F");
    rules = node;

    //string builder
    u[0] ='\0';
    strcpy(u, "F");
    string_builder(rules, depth);
    //OR draw square
    //deltaAngle = 45 * toRadians;
    //strcpy(u, "++F++F++F++F");


    //init graphics 
    G_init_graphics (swidth,sheight) ;  // interactive graphics
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;
    
    //auto placer
    //void auto_placer(int swidth, int sheight, double startAngle, double detlaAngle, 
    //int depth, double * start, double * forwardLen){
    auto_placer(swidth, sheight, startAngle, deltaAngle, depth, start, &forwardLen); 
    printf("start: %lf, %lf\n", start[0], start[1]);
    printf("forwardLen: %lf\n", forwardLen);
    
    //string Doodler
    double xs[10000];
    double ys[10000];
    xs[0] = start[0];
    ys[0] = start[1];
    pointsLen = string_interpreter(xs, ys, forwardLen, startAngle, deltaAngle);
    string_doodler(xs, ys, pointsLen);

    key ;   
    key =  G_wait_key() ; // pause so user can see results
}

struct Node* find_rule(struct Node* node, char key){
    //struct Node* newNode;
    //newNode = (struct Node*) malloc(sizeof(struct Node));
    //newNode->var = 'c';
     

    if(node->var == key){
        return node;    
    }
    else if(node->next != NULL){
        return find_rule(node->next, key);
    }
    else{
        return NULL;
    }
}

struct Node* new_rule(char var, char* ruleStr){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->var = 'F';
    strcpy(newNode->rule, ruleStr);
    newNode->next = NULL;
    return newNode;
}

void shift(int start, int length, int shiftSize){
    for(int i=length; i>start; i--){
        u[i+shiftSize] = u[i];
    }
   

}

void string_builder(struct Node* rules, int maxDepth){
    int length = strlen(u);
    struct Node* node; 
    int shiftSize;
    char temp;
    int start;
    int i;
    int j;
    
    //one pass
    for(int depth=0; depth< maxDepth; depth++){
        i = 0;
        j = strlen(u);
        //printf("\ndepth: %d", depth);
        while(i < j){
            node = find_rule(rules, u[i]);
            //printf("\nstart %s i=%d j=%d ", u, i, j);
            if(node != NULL){
                //index is last letter
                //assuming you update j at the end of while loop
                shiftSize = strlen(node->rule); // using smaller shift prevents have to shift back
                if(i == j - 1){
                    u[i]='\0';
                    strcat(u, node->rule);
                    //printf("case 1");
                }
                else{
                    //printf("case 2");
                    //to accomodate null char of rule
                    //shiftSize = strlen(node->rule) + 1;

                    //save first character that will get over written by nul of subs
                    temp = u[i+1];
                    u[i] = '\0';

                    //probably doesn't work 
                    shift(i+1, j, shiftSize-1);
                    
                    strcat(u, node->rule);
                    
                    u[strlen(u)] = temp;
                }
                //should be equivalent
                //j = j + shiftSize
                j = strlen(u);
                //printf("\nend   %s i=%d j=%d ", u, i, j);
                //for(int k=j; k<20; k++){
                    //printf("*%c", u[k]);
                //}
            }
            else{ // no rule found for subst string stays same size
                shiftSize = 0;
            }
            i = i + 1 + shiftSize;
        }
    }
}


void rotate_point(double * point, double detlaAngle){
    double x1;
    double y1;
    double x2;
    double y2;
    double d;

    //x1 is is just next point plus last angle 
    x1 =  point[0];
    y1 =  point[1];

    d = sqrt((x1 * x1) + (y1 * y1));
    x1 = x1 / d;
    y1 = y1 / d;

    //rotate
    x2 = cos(detlaAngle) * x1 - sin(detlaAngle) *  y1;
    y2 = cos(detlaAngle) * y1 + sin(detlaAngle) *  x1;

    //mult it by len
    x2 = x2 * d;
    y2 = y2 * d;
    
    //shift back to old spot
    point[0] = x2;
    point[1] = y2;
}

void next_point(double * lastPoint,double * nextPoint, double startAngle, double deltaAngle, double forwardLen){
    double x0 = lastPoint[0];
    double y0 = lastPoint[1];
    double x1;
    double y1;
    double tempPoint[2]; 
    
    //point pre-rotation
    x1 = cos(startAngle);
    y1 = sin(startAngle);

    //rotate
    tempPoint[0] = x1;
    tempPoint[1] = y1;
    rotate_point(tempPoint, deltaAngle);
    x1 = tempPoint[0];
    y1 = tempPoint[1];

    //scale by forward Len and translate
    x1 = x1 * forwardLen + x0; 
    y1 = y1 * forwardLen + y0; 
    nextPoint[0] = x1; 
    nextPoint[1] = y1;
}

int string_interpreter(double *xs, double *ys, double forwardLen, double startAngle, double deltaAngle){
    char c;
    int i = 0; //u index
    int j = 1; //first coord should already be in place 
    int f = 0; //count of moves forward
    double lastPoint[2];
    double nextPoint[2];
    double turn = 0;

    c = u[i];
    lastPoint[0] = xs[0]; 
    lastPoint[1] = ys[0];

    while(c == 'F'){
        f++;
        c=u[++i];
    }
    //starting with out a turn
    if(f > 0){ //make first move
        //next_point(double * lastPoint,double * nextPoint, double startAngle, double deltaAngle, double forwardLen){
        lastPoint[0] = xs[0];
        lastPoint[1] = ys[0];
        next_point(lastPoint, nextPoint, startAngle, 0, f*forwardLen);
        //printf("next_Point(lastPoint=(%lf, %lf), nextPoint=(%lf, %lf), startAngle=%lf, turn=%lf, f*len=%d*%lf\n", 
        //        lastPoint[0], lastPoint[1], nextPoint[0], nextPoint[1], startAngle, turn, f, forwardLen);
        xs[j] = nextPoint[0];
        ys[j] = nextPoint[1];
        lastPoint[0] = nextPoint[0];
        lastPoint[1] = nextPoint[1];
        j++;
        startAngle = startAngle + turn;
        turn = 0;

    }
    
    while(c != '\0'){
        // turn
        f=0;
        while(c == '+' || c == '-'){
            if(c == '+'){
                turn = turn + deltaAngle;
            }
            else{
                turn = turn - deltaAngle;
            }
            c = u[++i];
        }
        //go forward
        while(c == 'F'){
            f++;
            c = u[++i];
        }
        //move
        next_point(lastPoint, nextPoint, startAngle, turn, f*forwardLen);
        //printf("next_Point(lastPoint=(%lf, %lf), nextPoint=(%lf, %lf), startAngle=%lf, turn=%lf, f*len=%d*%lf\n", 
        //        lastPoint[0], lastPoint[1], nextPoint[0], nextPoint[1], startAngle*toDegrees, turn*toDegrees, f, forwardLen);

        xs[j] = nextPoint[0];
        ys[j] = nextPoint[1];
        lastPoint[0] = nextPoint[0];
        lastPoint[1] = nextPoint[1];
        j++;
        startAngle = startAngle + turn;
        turn = 0;
    }
    return j;
}

void string_doodler(double * xs, double * ys, int n){
    G_rgb (0.0, 1.0, 0.0) ; // green
    for(int i = 0; i < n-1; i++){
       G_line (xs[i],ys[i], xs[i+1], ys[i+1]);
    }
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

double max_dub_array(double * A, int n){
    int max = A[0];
    for(int i=1; i<n; i++){
        max = max_dub(max, A[i]);
    }
    return max;
}

double min_dub_array(double * A, int n){
    int min = A[0];
    for(int i=1; i<n; i++){
        min = min_dub(min, A[i]);
    }
    return min;
}

double avg_dubs(double * A, int n){
    double accum = 0.0;
    for(int i=0; i<n; i++){
        accum = accum + A[i];
    }
    return accum / n;
}
