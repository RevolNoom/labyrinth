#include "SolidObject.hpp"

SolidObject::SolidObject(std::shared_ptr<Texture> texture, Vector2 pos) :
	Sprite2D(texture)
{
	//SetPosition(Vector3(pos.x, pos.y, 0));
	Set2DPosition(pos);
	RegisterToWorld(pos);
}

void SolidObject::RegisterToWorld(Vector2 pos)
{
	// yeeted right out of the Documentation

	// TODO: Maybe I miscalculated. Each scene
	// should have an independent World

	// Specify the initial position of the body
	b2BodyDef groundBodyDef;
	// TODO: Set the position according to sprite 
	groundBodyDef.position.Set(pos.x, pos.y);

	// Create a body from definition. The World will contain it
	_body = TopdownWorld::get_instance()->CreateBody(&groundBodyDef);

	// Create the collision shape for this body
	// TODO: Set the Size of this body according to the sprite
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	// Attach the body to the shape
	_body->CreateFixture(&groundBox, 0.0f);

	// TODO: A conversion from pixel to meter is needed.
}


Vector2 SolidObject::GetSize() const
{
	return Vector2((GLfloat)m_iWidth, (GLfloat)m_iHeight);
}