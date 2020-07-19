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
void string_drawer(double * xs, double * ys, int n);

int main()
{
    //seg faults at depth 12
    int depth = 8;
    double startAngle = 0;
    double deltaAngle = 60 * toRadians;
    double forwardLen=8;
    double startX = 200;
    double startY = 200;
    int swidth = 600;
    int sheight = 600 ;
    int key ;   
    struct Node* node;
    struct Node* rules;
    char axiom[10] = "F";
    double xs[10000];
    double ys[10000];
    int pointsLen;

    
    //make list of rules 
    node = new_rule('F', "F+F--F+F");
    rules = node;


    //graphics 
    G_init_graphics (swidth,sheight) ;  // interactive graphics
    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;
    
    //draw square
    //deltaAngle = 45 * toRadians;
    //strcpy(u, "++F++F++F++F");

    // ---- String builder ----
    //string_builder(rules, depth);

    // old test 
    //u[0]='\0';
    //strcpy(u, "++F");
    ////string_builder(struct Node*, int);
    //string_builder(rules, depth);
    //printf("%s\n", u);


    //stringBuilder test 1
    u[0] = '\0';
    strcpy(u, "F");
    printf("u with axiom: %s\n", u);
    string_builder(rules, 1);
    printf("u after strinbuilder\n%s\n", u);
    char str1[10] = "F+F--F+F";

    //stringBuilder test 1
    char str2[50] = "F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F";

    //stringBuilder test 2
    char str3[200] = "F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F+F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F+F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F";


    //build up points from string
    //string_interpreter(*xs, *ys, *start, forwardLen, startAngle, deltaAngle);
    xs[0] = startX;
    ys[0] = startY;
    pointsLen = string_interpreter(xs, ys, forwardLen, startAngle, deltaAngle);

    //printf("\n\npoints print out\n");
    //for(int i=0; i<pointsLen; i++){
    //    printf("%lf %lf\n", xs[i], ys[i]);
    //}
    
    string_drawer(xs, ys, pointsLen);
    
    key ;   
    key =  G_wait_key() ; // pause so user can see results
}

struct Node* find_rule(struct Node* node, char key){
    struct Node* newNode;
    newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->var = 'c';

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

struct Node* new_rule(char var, char* rule){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->var = 'F';
    strcpy(newNode->rule, "-F+F-");
    newNode->next = NULL;
    return newNode;
}

void shift(int start, int length, int shiftSize){
    for(int i=length; i>=start; i--){
        u[i+shiftSize] = u[i];
    }
   

}

void string_builder(struct Node* rules, int maxDepth){
    int index;
    int length = strlen(u);
    struct Node* node; 
    int shiftSize;
    char temp;
    int start;
    

    //one pass
    for(int i=0; i< maxDepth; i++){
        index= 0;
        while(index < length){
            node = find_rule(rules, u[index]);
            if(node != NULL){
                shiftSize = strlen(node->rule) - 1;

                //index is last letter
                if(index == length - 1){
                    u[index]='\0';
                    strcat(u, node->rule);
                }
                else{
                    temp = u[index+1];
                    length = strlen(u);
                    u[index] = '\0';
                    //why -1
                    shift(index+1, length, shiftSize);
                    
                    strcat(u, node->rule);
                    length = strlen(u);
                    u[length]= temp;
                }
                index = index + shiftSize;
            }
            // noe rule for char
            else{
                index++;
            }
            length = strlen(u);
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
        lastPoint[1] = ys[1];
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
    printf("\n\n");
    
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
                //lastPoint[0], lastPoint[1], nextPoint[0], nextPoint[1], startAngle*toDegrees, turn*toDegrees, f, forwardLen);

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

void string_drawer(double * xs, double * ys, int n){
    G_rgb (0.0, 1.0, 0.0) ; // green
    for(int i = 0; i < n-1; i++){
       G_line (xs[i],ys[i], xs[i+1], ys[i+1]);
    }
    
}
