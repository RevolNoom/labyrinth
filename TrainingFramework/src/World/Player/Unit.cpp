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
		_anims.push_back(anim);
	}
	SetSize(50, 50);
}

void Unit::SetSize(GLint width, GLint height)
{
	Sprite2D::SetSize(width, height);

	for (int iii = 0; iii < ANIM::MAX_ANIM; ++iii)
		_anims[iii]->SetSize(width, height);
}

void Unit::RegisterToWorld(b2World* world)
{
	// Bla bla bla
	// Go to Wall.cpp for more detailed comments
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2BodyType::b2_dynamicBody;
	auto phyPos = ToPhysicCoordinate(GetPosition());
	groundBodyDef.position.Set(phyPos.x, phyPos.y);
	groundBodyDef.fixedRotation = true;

	_body = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	auto phySize = ToPhysicCoordinate(GetSize()/2);
	groundBox.SetAsBox(phySize.x, phySize.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	// Attach the body to the shape
	_body->CreateFixture(&fixtureDef);

	//std::cout << "Unit _body Size: " << phySize.x << " " << phySize.y << "\n";
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

void Unit::SetEnable(bool enable)
{
	_body->SetEnabled(enable);
}

void Unit::Set2DPosition(Vector2 newPos)
{
	Sprite2D::Set2DPosition(newPos);
	for (auto& a : _anims)
		a->Set2DPosition(newPos.x, newPos.y);
}


std::shared_ptr<SpriteAnimation> Unit::GetCurrentAnim()
{
	return _anims[_currentAnim];
}

bool Unit::HandleKeyPress(const InputEventKeyPress* ev)
{
	b2Vec2 maxVelo(ToPhysicCoordinate(Vector2(100, 100)));
	b2Vec2 velo(_body->GetLinearVelocity());

	if (ev->IsPressed())
	{
		if (ev->Key() == KEY_MOVE_LEFT)
			velo.x = -maxVelo.x;

		if (ev->Key() == KEY_MOVE_RIGHT)
			velo.x = +maxVelo.x;

		if (ev->Key() == KEY_MOVE_BACKWARD)
			velo.y = +maxVelo.y;

		if (ev->Key() == KEY_MOVE_FORWARD)
			velo.y = -maxVelo.y;
	}
	else
	{
		if (ev->Key() == KEY_MOVE_LEFT ||
			ev->Key() == KEY_MOVE_RIGHT)
			velo.x = 0;

		if (ev->Key() == KEY_MOVE_BACKWARD ||
			ev->Key() == KEY_MOVE_FORWARD)
			velo.y = 0;
	}

	_body->SetLinearVelocity(velo);

	if (velo.LengthSquared() > 0.001)
		_currentAnim = ANIM::RUN;
	else
		_currentAnim = ANIM::IDLE;


	//std::cout << "Unit _body Pos: " << _body->GetPosition().x << " " << _body->GetPosition().y << "\n";
			
	return false;
}
