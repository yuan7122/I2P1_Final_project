#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "Shape.h"
#include <math.h>
#include <stdbool.h>

/**
 * @see Shape.c
 */
typedef struct _Point
{
    double x, y;
} Point;
Point *Point_Self(Shape *self);
bool Point_overlap(Shape *self, Shape *tar);
double Point_center_x(Shape *self);
double Point_center_y(Shape *self);
void Point_update_center_x(Shape *self, int x);
void Point_update_center_y(Shape *self, int y);
ShapeType Point_getType();
Shape *New_Point(double x, double y);
double Point_dist2(Point *p1, Point *p2);
double Point_dist(Point *p1, Point *p2);

#endif
