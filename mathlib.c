#include "mathlib.h"
#include <stddef.h>

// Base functions defined in mathlib.h -> 
// clamp, lerp, is_close, factorial, fibonacci, my_fabs (double), my_abs (int), my_fmod

/* 
2D SHAPES ---

circle_area, circle_perim, 
square_area, square_perim, 
rect_area, rect_perim, 

tri_perim, 
tri_area, 
right_tri_area, 
equil_tri_area

rhombus_area
rhombus_perim
trap_area
trap_perim
para_area
para_perim

polygon_perim

3D SHAPES ---

cube_volume
cube_surface

prism_volume

sphere_volume
sphere_surface

cyl_volume
cyl_surface

cone_volume
pyramid_volume

DEG2RAD
RAD2DEG
*/
// Math and Equation Parser
double my_sqrt(double x)
{
    /* reject NaNs / negatives */
    if (x < 0.0)      return -1.0;     /* error flag – adjust to taste */
    if (x == 0.0)     return 0.0;      /* √0 = 0 */

    /* initial guess: half of x (or 1.0 for very small numbers) */
    double guess = (x < 1.0) ? 1.0 : x * 0.5;

    /* Newton iteration:  gₙ₊₁ = ½ (gₙ + x / gₙ) */
    for (int i = 0; i < 8; ++i)        /* 6–8 steps are plenty for 1e-15 accuracy */
    {
        double next = 0.5 * (guess + x / guess);
        if (next == guess) break;      /* converged */
        guess = next;
    }
    return guess;
}


// Trigonometry
double my_sin(double x) 
{
    x = my_fmod(x, 2 * MY_PI); // Reduce angle to within -2π to 2π range
    double result = 0.0;
    double term = x;
    for (int i = 1; i <= 10; i++) 
    { // Adjust the number of terms for desired accuracy
        result += term;
        term *= -(x * x) / ((2.0 * i) * (2.0 * i + 1.0));
    }
    return result;
}

double my_cos(double x) 
{
    x = my_fmod(x, 2 * MY_PI); // Reduce angle to within -2π to 2π range
    double result = 1.0;
    double term = 1.0;
    for (int i = 1; i <= 10; i++) { // Adjust the number of terms for desired accuracy
        term *= -(x * x) / ((2.0 * i - 1.0) * (2.0 * i));
        result += term;
    }
    return result;
}

double my_tan(double x)
{
	double tan;
	tan = my_sin(x) / my_cos(x);
}
