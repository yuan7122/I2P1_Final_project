#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>

typedef enum ShapeType
{
	POINT,
	RECTANGLE,
	CIRCLE
} ShapeType;

/**
 * @brief Base shape class.
 * @details The functions of its derived classes are all defined in Shape.c.
 * @see Shape.c
 */

typedef struct _Shape Shape;
typedef bool (*fptrOverlap)(Shape *const, Shape *const);
typedef double (*fptrCenterX)(Shape *const);
typedef double (*fptrCenterY)(Shape *const);
typedef void (*fptrUpdateCenterX)(Shape *const, int);
typedef void (*fptrUpdateCenterY)(Shape *const, int);
typedef ShapeType (*fptrGetType)();
struct _Shape
{
	void *pDerivedObj;
	fptrOverlap overlap;
	fptrCenterX center_x;
	fptrCenterY center_y;
	fptrUpdateCenterX update_center_x;
	fptrUpdateCenterY update_center_y;
	fptrGetType getType;
};
Shape *New_Shape();

#endif
