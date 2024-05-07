#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "Shape.h"
#include <math.h>

/**
 * @see Shape.c
 */
typedef struct _Point
{
    double x, y;
} Point;
Point *Point_Self(Shape *self);
bool Point_overlap(Shape *const, Shape *const);
double Point_center_x(Shape *const self);
double Point_center_y(Shape *const self);
void Point_update_center_x(Shape *const self, int x);
void Point_update_center_y(Shape *const self, int y);
ShapeType Point_getType();
Shape *New_Point(double x, double y);
double Point_dist2(Point *p1, Point *p2);
double Point_dist(Point *p1, Point *p2);

#endif
