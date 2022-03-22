#include "Unit.hpp"
Theseus::Theseus(std::string animTextrName, Vector2 initPos):
	SolidObject(std::shared_ptr<Texture>(nullptr), initPos)
{
	/*
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture(animTextrName);
	//SpriteAnimation(..., GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime)
	//_anim = std::make_shared<SpriteAnimation>(model, shader, texture);
	*/
}


void Theseus::Draw()
{
	//_anim->Draw();
}


void Theseus::Update(float delta)
{
	//_anim->Update(delta);
}