#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include <stdbool.h>
#include "Shape.h"

/**
 * @see Shape.cpp
 */
typedef struct _Circle
{
    double x, y, r;
} Circle;
Circle *Circle_Self(Shape *self);
bool Circle_overlap(Shape *const, Shape *const);
double Circle_center_x(Shape *const self);
double Circle_center_y(Shape *const self);
void Circle_update_center_x(Shape *const self, int x);
void Circle_update_center_y(Shape *const self, int y);
ShapeType Circle_getType();
Shape *New_Circle(double x, double y, double r);
ShapeType Circle_getType();
#endif
