#include "Unit.hpp"
#include "box2d/b2_fixture.h"

Unit::Unit():
	Sprite2D()
{
	Init();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur.tga");

	_currentAnim = IDLE;

	for (int iii = 0; iii < ANIM::MAX_ANIM; ++iii)
	{
		auto anim = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 2, iii, 0.15);
		anim->SetSize(50, 50);
		anim->Set2DPosition(200, 200);
		_anims.push_back(anim);
	}
}

void Unit::SetSize(GLint width, GLint height)
{
	Sprite2D::SetSize(width, height);

	for (int iii = 0; iii < ANIM::MAX_ANIM; ++iii)
	{
		_anims[iii]->SetSize(width, height);
	}
}

void Unit::RegisterToWorld(b2World* world)
{
	// Bla bla bla
	// Go to Wall.cpp for more detailed comments
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2BodyType::b2_dynamicBody;
	auto phyPos = ToPhysicCoordinate(GetPosition());
	std::cout << "Unit PhyPos: " << phyPos.x << " " << phyPos.y << "\n";
	groundBodyDef.position.Set(phyPos.x, phyPos.y);
	groundBodyDef.allowSleep = false;
	groundBodyDef.enabled = true;

	_body = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	auto phySize = ToPhysicCoordinate(GetSize());
	groundBox.SetAsBox(phySize.x, phySize.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	// Attach the body to the shape
	_body->CreateFixture(&fixtureDef);

	std::cout << "_body Pos: " << _body->GetPosition().x << " " << _body->GetPosition().x << "\n";
}


void Unit::Draw()
{
	GetCurrentAnim()->Draw();
}


void Unit::Update(float delta)
{
	GetCurrentAnim()->Update(delta);

	auto objPos = ToGraphicCoordinate(_body->GetPosition());
	GetCurrentAnim()->Set2DPosition(objPos.x, objPos.y);
}


std::shared_ptr<SpriteAnimation> Unit::GetCurrentAnim()
{
	return _anims[_currentAnim];
}

bool Unit::HandleKeyPress(const InputEventKeyPress* ev)
{
	b2Vec2 maxForceX = ToPhysicCoordinate(Vector2(100, 0)); 
	b2Vec2 maxForceY = ToPhysicCoordinate(Vector2(0, 100));

	if (ev->IsPressed())
	{
		if (ev->Key() == KEY_MOVE_LEFT)
			_body->ApplyForceToCenter(-maxForceX, true);

		if (ev->Key() == KEY_MOVE_RIGHT)
			_body->ApplyForceToCenter(maxForceX, true);

		if (ev->Key() == KEY_MOVE_BACKWARD)
			_body->ApplyForceToCenter(maxForceY, true);

		if (ev->Key() == KEY_MOVE_FORWARD)
			_body->ApplyForceToCenter(-maxForceY, true);
	}/*
	else
	{
		if (ev->Key() == KEY_MOVE_LEFT ||
			ev->Key() == KEY_MOVE_RIGHT)
			force.x = 0;

		if (ev->Key() == KEY_MOVE_BACKWARD ||
			ev->Key() == KEY_MOVE_FORWARD)
			force.y = 0;
	}*/

	if (_body->GetLinearVelocity() != b2Vec2_zero)
		_currentAnim = ANIM::RUN;
	else
		_currentAnim = ANIM::IDLE;
	
	auto pos = _body->GetPosition();
	std::cout <<"Pos: "<< pos.x <<" " << pos.y << "\n";
	//_body->SetLinearVelocity(force);
			
	
	return false;
}
