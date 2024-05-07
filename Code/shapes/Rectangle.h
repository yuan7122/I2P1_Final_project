#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "Shape.h"

/**
 * @see Shape.cpp
 */
typedef struct _Rectangle
{
	double x1, y1, x2, y2;
} Rectangle;
Rectangle *Rectangle_Self(Shape *self);
bool Rectangle_overlap(Shape *const, Shape *const);
double Rectangle_center_x(Shape *const self);
double Rectangle_center_y(Shape *const self);
void Rectangle_update_center_x(Shape *const self, int x);
void Rectangle_update_center_y(Shape *const self, int y);
ShapeType Rectangle_getType();
Shape *New_Rectangle(double x1, double y1, double x2, double y2);

#endif
