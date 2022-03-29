#include "PhysicObject.hpp"


b2Vec2 PhysicObject::ToPhysicCoordinate(Vector3 graphicalWorldCoord)
{
	return ToPhysicCoordinate({ graphicalWorldCoord.x, graphicalWorldCoord.y }) ;
}

b2Vec2 PhysicObject::ToPhysicCoordinate(Vector2 graphicalWorldCoord)
{
	return b2Vec2(graphicalWorldCoord.x / GRAPHIC_TO_PHYSIC_SIZE_RATIO, 
					graphicalWorldCoord.y / GRAPHIC_TO_PHYSIC_SIZE_RATIO) ;
}

Vector2 PhysicObject::ToGraphicCoordinate(b2Vec2 physicalWorldCoord)
{
	return Vector2(physicalWorldCoord.x * GRAPHIC_TO_PHYSIC_SIZE_RATIO,
					physicalWorldCoord.y * GRAPHIC_TO_PHYSIC_SIZE_RATIO);
}
