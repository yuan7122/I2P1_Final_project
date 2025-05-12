#include "Shape.h"
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "../GAME_ASSERT.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../global.h"
/**
 * @file Shape.c
 * @brief All functions and implementations are defined here.
 */

bool checkOverlap_pp(Point *p1, Point *p2)
{
	return (p1->x == p2->x) && (p1->y == p2->y);
}

bool checkOverlap_pr(Point *p, Rectangle *r)
{
	return (r->x1 <= p->x && p->x <= r->x2) && (r->y1 <= p->y && p->y <= r->y2);
}

bool checkOverlap_pc(Point *p, Circle *c)
{
	return (c->r * c->r) <= Point_dist2(p, (Point *)(New_Point(c->x, c->y)->pDerivedObj));
}

bool checkOverlap_rr(Rectangle *r1, Rectangle *r2)
{
	return !(r1->x2 < r2->x1 || r2->x2 < r1->x1 || r1->y2 < r2->y1 || r2->y2 < r1->y1);
}

bool checkOverlap_rc(Rectangle *r, Circle *c)
{
	double x = max(r->x1, min(c->x, r->x2));
	double y = max(r->y1, min(c->y, r->y2));
	return (c->r * c->r) >= Point_dist2((Point *)(New_Point(c->x, c->y)->pDerivedObj), (Point *)(New_Point(x, y)->pDerivedObj));
}

bool checkOverlap_cc(Circle *c1, Circle *c2)
{
	double d = c1->r + c2->r;
	return ((d * d) >= Point_dist2((Point *)(New_Point(c1->x, c1->y)->pDerivedObj), (Point *)(New_Point(c2->x, c2->y)->pDerivedObj)));
}

bool Point_overlap(Shape *self, Shape *tar)
{
	Point *Self = (Point *)self->pDerivedObj;
	switch (tar->getType())
	{
	case POINT:
		return checkOverlap_pp(Self, (Point *)tar->pDerivedObj);
	case RECTANGLE:
		return checkOverlap_pr(Self, (Rectangle *)tar->pDerivedObj);
	case CIRCLE:
		return checkOverlap_pc(Self, (Circle *)tar->pDerivedObj);
	}
	GAME_ASSERT(false, "Unknown ShapeType.");
}

bool Rectangle_overlap(Shape *self, Shape *tar)
{
	Rectangle *Self = (Rectangle *)self->pDerivedObj;
	switch (tar->getType())
	{
	case POINT:
		return checkOverlap_pr((Point *)tar->pDerivedObj, Self);
	case RECTANGLE:
		return checkOverlap_rr(Self, (Rectangle *)tar->pDerivedObj);
	case CIRCLE:
		return checkOverlap_rc(Self, (Circle *)tar->pDerivedObj);
	}
	GAME_ASSERT(false, "Unknown ShapeType.");
}

bool Circle_overlap(Shape *self, Shape *tar)
{
	Circle *Self = (Circle *)self->pDerivedObj;
	switch (tar->getType())
	{
	case POINT:
		return checkOverlap_pc((Point *)tar->pDerivedObj, Self);
	case RECTANGLE:
		return checkOverlap_rc((Rectangle *)tar->pDerivedObj, Self);
	case CIRCLE:
		return checkOverlap_cc(Self, (Circle *)tar->pDerivedObj);
	}
	GAME_ASSERT(false, "Unknown ShapeType.");
}
Shape *New_Shape()
{
	return (Shape *)malloc(sizeof(Shape));
};