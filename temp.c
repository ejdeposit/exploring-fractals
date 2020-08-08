
//double euclidean_distance(double, double, double, double){}
void make_leaves(double x, double y){
    double p;
    double delta = 5.0; 
    int red;
    int green;
    int blue;
    double randomNum;

    srand48(162) ;
    //pick random location
    for(int i = 0; i < 8; i++){
        randomNum = drand48() ;  // gives a random double such that 0 <= r < 1
        p = 1.0/9.0;
        if(randomNum < 1 * p) { 
           x = x;     
           y = y;
        }
        else if(randomNum < 2 * p) { 
            y =  y + delta;
        }
        else if(randomNum < 3 * p) { 
            y = y - delta;
        }
        else if(randomNum < 4 * p) { 
            x = x + delta;
        }
        else if(randomNum < 5 * p) { 
            x = x + delta;
            y = y + delta;
        }
        else if(randomNum < 6 * p) { 
            x = x + delta;
            y = y - delta;
        }
        else if(randomNum < 7 * p) { 
            x = x - delta;
        }
        else if(randomNum < 8 * p) { 
            x = x - delta;
            y = y - delta;
        }
        else{
            x = x - delta;
            y = y + delta;
        }

        //pick random color
        p = 1.0/8.0;
        if(randomNum < 1 * p) { 
            red = 125;   
            green = 187;
            blue = 110;
            //light green
        }
        else if(randomNum < 2 * p) { 
            red = 75;   
            green = 135;
            blue = 61;
            //darker green
        }
        else if(randomNum < 3 * p) { 
            red = 202;   
            green = 133;
            blue = 72;
            //coral
        }
        else if(randomNum < 4 * p) { 
            red = 250;   
            green = 214;
            blue = 119;
            //mellow yellow

        }
        else if(randomNum < 5 * p) { 
            red = 235;   
            green = 110;
            blue = 78;
            //orange
        }
        else if(randomNum < 6 * p) { 
            red = 253;   
            green = 219;
            blue = 114;
            //gold

        }
        else if(randomNum < 7 * p) { 
            red = 235;   
            green = 97;
            blue = 85;
            //mellow coral
        }
        else{
            red = 221;   
            green = 320;
            blue = 149;
        }
        
        G_rgb(r/255.0, g/255.0, b/255.0); 
        G_fill_circle (x, y, 3) ;
    }
}

    
