#include "Collision.h"
#include "Common.h"

sfBool CollisionRectRect(sfFloatRect* const _rect1, sfFloatRect* const _rect2)
{
	if (sfFloatRect_intersects(_rect1, _rect2, NULL))
	{
		return sfTrue;
	}
	else
	{
		return sfFalse;
	}
    
}

sfBool CollisionPointRect(sfFloatRect* const _rect1, sfVector2i const _point)
{
	if (sfFloatRect_contains(_rect1, (float)_point.x, (float)_point.x))
	{
		return sfTrue;
	}
	else
	{
		return sfFalse;
	}
    
}

sfBool ColisionCircleCircle(sfVector2f _center1, float _radius1, sfVector2f _center2, float _radius2)
{
	float distance = sqrtf(powf(_center2.x - _center1.x, 2) + powf(_center2.y - _center1.y, 2));
	if (distance < _radius1 + _radius2)
	{
		return sfTrue;
	}
	else
	{
		return sfFalse;
	}
	
}

sfBool CollisionCircleRect(sfVector2f _center, float _radius, sfFloatRect* const _rect)
{
	sfVector2f closestPoint = { 0 };
	closestPoint.x = fmaxf(_rect->left, fminf(_center.x, _rect->left + _rect->width));
	closestPoint.y = fmaxf(_rect->top, fminf(_center.y, _rect->top + _rect->height));

	float distance = sqrtf(powf(_center.x - closestPoint.x, 2) + powf(_center.y - closestPoint.y, 2));
	if (distance < _radius)
	{
		return sfTrue;
	}
	else
	{
		return sfFalse;
	}
	
}

sfBool CollisionPointCircle(sfVector2f _point, sfVector2f _center, float _radius)
{
	float distance = sqrtf(powf(_point.x - _center.x, 2) + powf(_point.y - _center.y, 2));
	if (distance < _radius)
	{
		return sfTrue;
	}
	else
	{
		return sfFalse;
	}
	
}


