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
    int depth = 3;
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


    // ---- String builder ----


//   // old rule strinb builder test test 
//     struct Node* nodeTest = new_rule('F', "-F+F-");
//     struct Node* rulesTest = nodeTest;
//     printf("old test\n");
//     printf("rule: %s\n", rulesTest->rule);
//     //test 1
//     u[0]='\0';
//     strcpy(u, "++F");
//     printf("axiom: %s\n", u);
//     string_builder(rulesTest, 1);
//     printf("\nresult 1: %s\n", u);
//
//     //test 2
//     u[0]='\0';
//     strcpy(u, "++F");
//     printf("axiom: %s\n", u);
//     string_builder(rulesTest, 2);
//     printf("\nresult 2:%s\n", u);

///    //new rule string builder tests
///    printf("\n\n new rule test\n");
///    //stringBuilder test 1
//       u[0] = '\0';
//       strcpy(u, "F");
///    printf("test 1\n");
///    printf("axiom: %s\n", u);
///    printf("rule: %s\n", rules->rule);
///    string_builder(rules, 1);
///    char str1[10] = "F+F--F+F";
///    printf("result:  %s\n", u);
///    printf("expected:%s\n", str1);
    //stringBuilder test 1
    //char str2[50] = "F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F";
    //stringBuilder test 2
    //char str3[200] = "F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F+F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F+F+F--F+F+F+F--F+F--F+F--F+F+F+F--F+F";
   
    //draw snow flake
    u[0] ='\0';
    strcpy(u, "F");
    string_builder(rules, depth);
    //OR draw square
    //deltaAngle = 45 * toRadians;
    //strcpy(u, "++F++F++F++F");

    //draw something from string
    //string_interpreter(*xs, *ys, *start, forwardLen, startAngle, deltaAngle);
    xs[0] = startX;
    ys[0] = startY;
    pointsLen = string_interpreter(xs, ys, forwardLen, startAngle, deltaAngle);

    //test print all points
    printf("\n\npoints print out\n");
    for(int i=0; i<pointsLen; i++){
        printf("%lf %lf\n", xs[i], ys[i]);
    }

    //graphics 
    G_init_graphics (swidth,sheight) ;  // interactive graphics
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;
    

    string_drawer(xs, ys, pointsLen);

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
        printf("next_Point(lastPoint=(%lf, %lf), nextPoint=(%lf, %lf), startAngle=%lf, turn=%lf, f*len=%d*%lf\n", 
                lastPoint[0], lastPoint[1], nextPoint[0], nextPoint[1], startAngle, turn, f, forwardLen);
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
        printf("next_Point(lastPoint=(%lf, %lf), nextPoint=(%lf, %lf), startAngle=%lf, turn=%lf, f*len=%d*%lf\n", 
                lastPoint[0], lastPoint[1], nextPoint[0], nextPoint[1], startAngle*toDegrees, turn*toDegrees, f, forwardLen);

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