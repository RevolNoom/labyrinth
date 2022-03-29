#include "Wall.h"

Wall::Wall(std::shared_ptr<Texture> texture):
	Sprite2D(texture)
{

}

void Wall::RegisterToWorld(b2World* world)
{
	// yeeted right out of the Documentation

	// Specify the initial position of the body
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2BodyType::b2_staticBody;// A wall does not move
	auto phyPos = ToPhysicCoordinate(GetPosition());

	groundBodyDef.position.Set(phyPos.x, phyPos.y);
	groundBodyDef.angle = GetRotation().z; // Set the body rotation

	// Create a body from definition. The World will contain it
	_body = world->CreateBody(&groundBodyDef);

	// Create the collision shape for this body
	b2PolygonShape groundBox;
	auto phySize = ToPhysicCoordinate(GetSize()); 
	std::cout << "Wall _body Size: " << phySize.x << " " << phySize.y << "\n";
	groundBox.SetAsBox(phySize.x, phySize.y);

	// Attach the body to the shape
	_body->CreateFixture(&groundBox, 0);
	std::cout << "Wall _body Pos: " << _body->GetPosition().x << " " << _body->GetPosition().y << "\n";
}
