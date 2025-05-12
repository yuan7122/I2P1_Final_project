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
bool Rectangle_overlap(Shape *self, Shape *tar);
double Rectangle_center_x(Shape *self);
double Rectangle_center_y(Shape *self);
void Rectangle_update_center_x(Shape *self, int x);
void Rectangle_update_center_y(Shape *self, int y);
ShapeType Rectangle_getType();
Shape *New_Rectangle(double x1, double y1, double x2, double y2);

#endif
