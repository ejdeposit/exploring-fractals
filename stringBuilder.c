#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "FPToolkit.c"

//char u[10000]= {'\0'};
char u[10000];


struct Node {
    char var;
    char rule[20];
    struct Node *next;
};

struct Node* find_rule(struct Node*, char key);
void string_builder(struct Node*, int);
struct Node* new_rule(char, char*);
void shift(int start, int length, int shiftSize);
void string_interpreter(double *xs, double *ys, double *start, double forwardLen, double startAngle, double deltaAngle);
void rotate_point(double * point, double detlaAngle);
void next_point(double * lastPoint, double * nextPoint, double startAngle, double deltaAngle, double forwardLen);

void scale(double scaleF);
void string_drawer();

int main()
{
    struct Node* node;
    struct Node* rules;
    char axiom[100] = "++F";
    int length;
    double startAngle = 0;
    double deltaAngle = 90 * (2 * M_PI / 360);
    double forwardLen=10;
    
    //make list of rules 
    node = new_rule('F', "-F+F-");
    rules = node;
    //printf("rule test\n");
    //printf("Var: %c\n", rules->var);
    //printf("Rule: %s\n", rules->rule);

    ////make second rule and test fine rule
    //node = new_rule('A', "F");
    //node->next = rules;
    //rules = node;
    //node = find_rule(rules, 'F');
    //if(node != NULL){
    //    printf("find_rule() test\n");
    //    printf("Var: %c\n", node->var);
    //    printf("Rule: %s\n", node->rule);
    //}
    //else{
    //    printf("no rule found");
    //}

    
    //test string builder
    u[0]='\0';
    strcpy(u, "++F");
    printf("\n\ntest string_builder()\n");
    printf("%s\n", u);
    string_builder(rules, 2);
    printf("%s\n", u);

    //graphics 
    int    swidth, sheight ;
    int key ;   
    double p[2] = {0,0};
    double q[2];
    // must do this before you do 'almost' any other graphical tasks 
    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;


    startAngle = 0;
    deltaAngle = 5 * (2 * M_PI / 360.0);
    double toRadians = (2.0 * M_PI / 360.0);
    //right point
    q[0] = 30*cos(0);
    q[1] = 30*sin(0);
    //top point
    p[0] = 30*cos(90*toRadians);
    p[1] = 30*sin(90*toRadians);

    // rotate arround center
    G_rgb(1,0,0) ;
    G_fill_circle(0,0,2) ;
    G_fill_circle(q[0], q[1], 2) ;
    G_fill_circle(p[0], p[1], 2) ;
    rotate_point(q, 45*toRadians);
    G_fill_circle(q[0],q[0],2) ;

    //rotate arroudn point
    //next_point(lastPoint, nextPoint, startAngle, deltaAngle, forwardLen){
    q[0] = 30*cos(0);
    q[1] = 30*sin(0);
    p[0] = 30*cos(90*toRadians);
    p[1] = 30*sin(90*toRadians);
    next_point(q, p, 0, 90*toRadians, 30);
    G_fill_circle(p[0], p[1], 2) ;

    // get user input
    //G_wait_click(p) ;
    //G_fill_circle(p[0],p[1],2) ;
     
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

void string_interpreter(double *xs, double *ys, double *start, 
                        double forwardLen, double startAngle, double deltaAngle){
}


void scale(double scaleF){
    //double centerX = 0;
    //double centerY = 0;
    //for(int i=0; i<n; i++){
    //    centerX = centerX + x[i];
    //    centerY = centerY + y[i];
    //}
    //centerX = centerX / n;
    //centerY = centerY / n;
    // 
    //double midX;
    //double midY;
    //for(int i=0; i<n; i++){
    //    midX =  x[i]- centerX; 
    //    midY = y[i] -  centerY;

    //    midX =  midX * scaleF;
    //    midY =  midY * scaleF;
    //    
    //    x[i] = centerX + midX;
    //    y[i] = centerY + midY;
    //}
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
    printf(" cos(theta), sin(theta): %lf %lf\n", x1, y1); 

    //rotate
    tempPoint[0] = x1;
    tempPoint[1] = y1;
    rotate_point(tempPoint, deltaAngle);
    x1 = tempPoint[0];
    y1 = tempPoint[1];
    printf(" rotate 0: %lf %lf\n", x1, y1); 

    //scale by forward Len and translate
    x1 = x1 * forwardLen + x0; 
    y1 = y1 * forwardLen + y0; 
    nextPoint[0] = x1; 
    nextPoint[1] = y1;
}

/*

void rotate(double * lastPoint, double * nextPoint, double startAngle, double detlaAngle, double forwardLen);
    double x1;
    double y1;
    double x2;
    double y2;
    

    //x0 y0 is last point shift it to center
    //dont' really need to assign it and shift

    //x1 is is just next point plus last angle 
    x1 =  cos(startAngle);
    y1 =  cos(startAngle);

    //rotate
    x2 = cos(detlaAngle) * x1 - sin(detlaAngle) *  y1;
    y2 = cos(detlaAngle) * y1 + sin(detlaAngle) *  x1;

    //mult it by len
    x2 = x2 * forwardLen;
    y2 = y2 * forwardLen;
    
    //shift back to old spot
    x2 = x2 + lastPoint[0];
    y2 = y2 + lastPoint[1];
    
    nextPoint[0] = x2;
    nextPoint[1] = y2;
*/
void string_drawer(){}
