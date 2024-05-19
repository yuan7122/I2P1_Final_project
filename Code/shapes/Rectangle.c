#include "Rectangle.h"
/**
 * @see Shape.cpp
 */
Rectangle *Rectangle_Self(Shape *self)
{
	return (Rectangle *)(self->pDerivedObj);
}
Shape *New_Rectangle(double x1, double y1, double x2, double y2)
{
	Rectangle *pDerivedObj = (Rectangle *)malloc(sizeof(Rectangle));
	pDerivedObj->x1 = x1;
	pDerivedObj->y1 = y1;
	pDerivedObj->x2 = x2;
	pDerivedObj->y2 = y2;
	Shape *pObj = New_Shape();
	pObj->overlap = Rectangle_overlap;
	pObj->center_x = Rectangle_center_x;
	pObj->center_y = Rectangle_center_y;
	pObj->update_center_x = Rectangle_update_center_x;
	pObj->update_center_y = Rectangle_update_center_y;
	pObj->getType = Rectangle_getType;
	pObj->pDerivedObj = pDerivedObj;
	return pObj;
}
double Rectangle_center_x(Shape *self)
{
	return (Rectangle_Self(self)->x1 + Rectangle_Self(self)->x2) / 2;
}
double Rectangle_center_y(Shape *self)
{
	return (Rectangle_Self(self)->y1 + Rectangle_Self(self)->y2) / 2;
}
void Rectangle_update_center_x(Shape *self, int x)
{
	Rectangle_Self(self)->x1 += x;
	Rectangle_Self(self)->x2 += x;
}
void Rectangle_update_center_y(Shape *self, int y)
{
	Rectangle_Self(self)->y1 += y;
	Rectangle_Self(self)->y2 += y;
}
ShapeType Rectangle_getType()
{
	return RECTANGLE;
}
