#include "Point.h"
#include <math.h>

/**
 * @see Shape.c
 */
Point *Point_Self(Shape *self)
{
    return (Point *)self->pDerivedObj;
}
Shape *New_Point(double x, double y)
{
    Point *pDerivedObj = (Point *)malloc(sizeof(Point));
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    Shape *pObj = New_Shape();
    pObj->overlap = Point_overlap;
    pObj->center_x = Point_center_x;
    pObj->center_y = Point_center_y;
    pObj->update_center_x = Point_update_center_x;
    pObj->update_center_y = Point_update_center_y;
    pObj->getType = Point_getType;
    pObj->pDerivedObj = pDerivedObj;
    return pObj;
}
double Point_center_x(Shape *self)
{
    return Point_Self(self)->x;
}
double Point_center_y(Shape *self)
{
    return Point_Self(self)->y;
}
void Point_update_center_x(Shape *self, int x)
{
    Point_Self(self)->x += x;
}
void Point_update_center_y(Shape *self, int y)
{
    Point_Self(self)->y += y;
}
ShapeType Point_getType()
{
    return POINT;
}
double Point_dist2(Point *p1, Point *p2)
{
    return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y);
}
double Point_dist(Point *p1, Point *p2)
{
    return sqrt(Point_dist2(p1, p2));
}
