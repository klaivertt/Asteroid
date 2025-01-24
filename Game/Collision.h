#ifndef COLLISION_H
#define COLLISION_H

#include "Common.h"

// * @brief Checks for collision between two rectangles.
// *
// * This function checks if two rectangles intersect.
// *
// * @param _rect1 Pointer to the first rectangle.
// * @param _rect2 Pointer to the second rectangle.
// * @return sfBool True if the rectangles intersect, false otherwise.
sfBool CollisionRectRect(sfIntRect* const _rect1, sfIntRect* const _rect2);

// * @brief Checks for collision between a point and a rectangle.
// *
// * This function checks if a point is inside a rectangle.
// *
// * @param _rect1 Pointer to the rectangle.
// * @param _point The point to check.
// * @return sfBool True if the point is inside the rectangle, false otherwise.
sfBool CollisionPointRect(sfFloatRect* const _rect1, sfVector2i const _point);

// * @brief Checks for collision between two circles.
// *
// * This function checks if two circles intersect.
// *
// * @param _center1 The center of the first circle.
// * @param _radius1 The radius of the first circle.
// * @param _center2 The center of the second circle.
// * @param _radius2 The radius of the second circle.
// * @return sfBool True if the circles intersect, false otherwise.
sfBool ColisionCircleCircle(sfVector2f _center1, float _radius1, sfVector2f _center2, float _radius2);

// * @brief Checks for collision between a circle and a rectangle.
// *
// * This function checks if a circle intersects a rectangle.
// *
// * @param _center The center of the circle.
// * @param _radius The radius of the circle.
// * @param _rect float rect of the rectangle.
// * @return sfBool True if the circle intersects the rectangle, false otherwise.
sfBool CollisionCircleRect(sfVector2f _center, float _radius, sfFloatRect* const _rect);
#endif

