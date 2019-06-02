#include "CGM.h"
#include <stdio.h>

Matrix CGM(Matrix x0, Matrix Q, Matrix b){

    Matrix s0(b - Q * x0);
    Matrix p0(s0);

    double err = 1;
    while(err > 1e-10)
    {
        double a = (s0.Trans() * s0 ).get(0,0) / ( p0.Trans() * Q * p0 ).get(0,0);
        x0 = (x0 +  p0 * a) ;
        err = (s0.Trans() * s0 ).get(0,0);
        s0 = (s0 - Q * p0 * a) ;
        double b = ( s0.Trans() * s0 ).get(0,0) / err;
        p0 = (s0 + p0 * b) ;
    }
    return x0;
}
