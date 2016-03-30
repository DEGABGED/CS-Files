#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Algorithm source: http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

int main(){
    /*Finding segment intersection using vector cross products
    - express as segments from p (x,y) to p+r (x,y)+(plusx+plusy)
    */
    printf("\nProgram 2: Intersecting Segments\n");
    int ndx;
    float x[2], y[2], plusx[2], plusy[2];
    //p = x[0],y[0] ; q = x[1],y[1]
    //r = plusx[0],plusy[0] ; s = plusx[1],plusy[1]
    char input[100], *token;
    printf("Enter the 4 coordinates: ");
    fgets(input, 100, stdin);

    token = strtok(input, ", ");
    for(ndx=0; ndx<2; ndx++){
        x[ndx] = atof(token);
        token = strtok(NULL, ", ");
        y[ndx] = atof(token);
        token = strtok(NULL, ", ");
        plusx[ndx] = atof(token) - x[ndx];
        token = strtok(NULL, ", ");
        plusy[ndx] = atof(token) - y[ndx];
        token = strtok(NULL, ", ");
        printf("(%.2f, %.2f) to (%.2f, %.2f)\n", x[ndx], y[ndx],
            x[ndx]+plusx[ndx], y[ndx]+plusy[ndx]);
    }

    float t, u, den, qmpx, qmpy;
    qmpx = x[1]-x[0];
    qmpy = y[1]-y[0];
    den = plusx[0]*plusy[1] - plusx[1]*plusy[0]; //scalar = r x s
    if(den){
        t = (qmpx*plusy[1] - qmpy*plusx[1]) / den; //scalar t = (q - p) x s / r x s
        u = (qmpx*plusy[0] - qmpy*plusx[0]) / den; //scalar u = (q - p) x r / r x s
        if(t>=0 && t<=1 && u>=0 && u<=1){
            //intersect, meet at point
            printf("Segments intersect at (%.2f, %.2f)\n", x[0]+(plusx[0]*t), y[0]+(plusy[0]*t));
        } else {
            //do not intersect
            printf("NO INTERSECTION\n");
        }
    } else {
        if(qmpx*plusy[0] - qmpy*plusx[0]){
            //parallel, nonintersecting
            printf("NO INTERSECTION\n");
        } else {
            //collinear, may overlap
            float rdotr = plusx[0]*plusx[0] + plusy[0]*plusy[0];
            float t0 = (qmpx*plusx[0] + qmpy*plusy[0]) / rdotr;
            float sdotr = plusx[1]*plusx[0] + plusy[1]*plusy[0];
            float t1 = t0 + (sdotr / rdotr);
            if(sdotr < 0){ //swap t0 and t1. Source: http://www.geeksforgeeks.org/swap-two-numbers-without-using-temporary-variable/
                t0 += t1;
                t1 = t0 - t1;
                t0 = t0 - t1;
            }
            printf("[%.2f, %.2f]\n", t0, t1);
            if((t0<=0 && t1>0) || (t0<1 && t1>=1) || (t0>=0 && t1<=1)){ //i have no idea what form of witchcraft makes this work but oh well
                printf("Segments overlap\n");
            } else if(t0==1){
                printf("Segments intersect at (%.2f, %.2f)\n", x[0]+plusx[0], y[0]+plusy[0]);
            } else if(t1==0){
                printf("Segments intersect at (%.2f, %.2f)\n", x[0], y[0]);
            } else {
                printf("NO INTERSECTION\n");
            }
        }
    }
}
