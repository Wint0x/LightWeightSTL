#ifndef H_MYMATHLIB
#define H_MYMATHLIB

// VARS
#include <stddef.h>
#include "my_math_constants.h"

// 2D Shapes
typedef struct Circle {
    double radius;
} Circle;

typedef struct Rectangle {
    double width;
    double height;
} Rectangle;

typedef struct Square {
    double side;
} Square;

typedef struct Triangle {
    double a, b, c; // Lengths of the three sides
} Triangle;

typedef struct RightTriangle {
    double base;
    double height;
} RightTriangle;

typedef struct EquilateralTriangle {
    double side;
} EquilateralTriangle;

typedef struct Rhombus {
    double side;
    double height;  // or diagonal1, diagonal2 for alternative
} Rhombus;

typedef struct Trapezoid {
    double base1;
    double base2;
    double height;
} Trapezoid;

typedef struct Parallelogram {
    double base;
    double height;
} Parallelogram;

typedef struct Polygon {
    int sides;         // number of sides
    double *lengths;   // dynamic array of side lengths
    double *angles;    // internal angles (optional)
} Polygon;

// 3D SHAPES
typedef struct Cube {
    double side;
} Cube;

typedef struct RectangularPrism {
    double width;
    double height;
    double depth;
} RectangularPrism;

typedef struct Sphere {
    double radius;
} Sphere;

typedef struct Cylinder {
    double radius;
    double height;
} Cylinder;

typedef struct Cone {
    double radius;
    double height;
} Cone;

typedef struct Pyramid {
    double base_length;
    double base_width;
    double height;
} Pyramid;

double my_sqrt(double x);

/*────────── 2-D AREA & PERIMETER ───────────────────────────*/

static inline double circle_area   (const Circle *c)            { return MY_PI * c->radius * c->radius; }
static inline double circle_perim  (const Circle *c)            { return 2.0 * MY_PI * c->radius; }

static inline double square_area   (const Square *s)            { return s->side * s->side; }
static inline double square_perim  (const Square *s)            { return 4.0 * s->side; }

static inline double rect_area     (const Rectangle *r)         { return r->width * r->height; }
static inline double rect_perim    (const Rectangle *r)         { return 2.0 * (r->width + r->height); }

static inline double tri_perim     (const Triangle *t)          { return t->a + t->b + t->c; }
static inline double tri_area      (const Triangle *t)          /* Heron’s formula */
{
    double s = tri_perim(t) * 0.5;
    return (s<=0)?0 : my_sqrt( s * (s - t->a) * (s - t->b) * (s - t->c) );
}

static inline double right_tri_area(const RightTriangle *t)     { return 0.5 * t->base * t->height; }
static inline double equil_tri_area(const EquilateralTriangle *t){ return 0.4330127018922193 * t->side * t->side; } /* √3/4 */

static inline double rhombus_area  (const Rhombus *r)           { return r->side * r->height; }
static inline double rhombus_perim (const Rhombus *r)           { return 4.0 * r->side; }

static inline double trap_area     (const Trapezoid *t)         { return 0.5 * (t->base1 + t->base2) * t->height; }
static inline double trap_perim    (const Trapezoid *t)         { /* need left/right for exact */ return 0.0; }

static inline double para_area     (const Parallelogram *p)     { return p->base * p->height; }
static inline double para_perim    (const Parallelogram *p)     { return 2.0 * (p->base + p->height); }

static inline double polygon_perim (const Polygon *p)
{
    double sum = 0.0;
    for (int i = 0; i < p->sides; ++i) sum += p->lengths[i];
    return sum;
}
/* polygon_area left out—requires coordinates or Gauss “shoelace” algorithm */

/*────────── 3-D VOLUME & SURFACE ───────────────────────────*/

static inline double cube_volume   (const Cube *c)              { return c->side * c->side * c->side; }
static inline double cube_surface  (const Cube *c)              { return 6.0 * c->side * c->side; }

static inline double prism_volume  (const RectangularPrism *p)  { return p->width * p->height * p->depth; }

static inline double sphere_volume (const Sphere *s)            { return (4.0/3.0) * MY_PI * s->radius*s->radius*s->radius; }
static inline double sphere_surface(const Sphere *s)            { return 4.0 * MY_PI * s->radius * s->radius; }

static inline double cyl_volume    (const Cylinder *c)          { return MY_PI * c->radius*c->radius * c->height; }
static inline double cyl_surface   (const Cylinder *c)          { return 2.0*MY_PI*c->radius*(c->radius + c->height); }

static inline double cone_volume   (const Cone *c)              { return (1.0/3.0)*MY_PI*c->radius*c->radius * c->height; }
/* cone surface requires slant height (sqrt(r²+h²)) */

static inline double pyramid_volume(const Pyramid *p)           { return (1.0/3.0)*p->base_length*p->base_width*p->height; }

/*────────── Helper macros (optional) ───────────────────────*/
#define DEG2RAD(x) ((x) * (MY_PI / 180.0))
#define RAD2DEG(x) ((x) * (180.0 / MY_PI))


// Base Functions

inline static double clamp(double value, double min, double max) 
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

inline static double lerp(double a, double b, double t) 
{
    return a + t * (b - a);
}

inline static int my_abs(int x) { return x < 0 ? -x : x;}
inline static double my_fabs(double x) { return x < 0 ? -x : x; }

inline static int is_close(double a, double b, double tolerance) 
{
    return my_fabs(a - b) < tolerance;
}

inline static long factorial(long n) 
{
    if (n < 0) return 0;
    long result = 1;
    for (long i = 2; i <= n; ++i)
        result *= i;
    return result;
}

inline static double deg2rad(double degrees) 
{
    return degrees * (MY_PI / 180.0);
}

inline static double rad2deg(double radians) 
{
    return radians * (180.0 / MY_PI);
}

inline static long fibonacci(const long n)
{
    if (n <= 0) return 0;
    if (n == 1) return 1;

    long a = 0, b = 1, temp;
    for (long i = 2; i <= n; ++i) 
    {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

inline static double my_fmod(double x, double y) {
    if (y == 0.0) return 0.0 / 0.0;  // NaN or handle error

    int quotient = (int)(x / y);    // truncate toward zero
    return x - (quotient * y);
}

double my_sin(double x);
double my_cos(double x);
double my_tan(double x);

#endif