#include <stdio.h>
#include "icoordstrans.h"

main()
{
    double phi, lambda, x, y, gamma;
    phi = 0.66322511575784523923100249202567;
    lambda = 0.40142572795869580269244887675238;
    wgs84_philambda_to_xy(phi, lambda, &x, &y, &gamma, PC_GR87);
    printf("X=%lf Y=%lf \n", x, y);
}
