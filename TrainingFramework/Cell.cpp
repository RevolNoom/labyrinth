#include "Cell.h"

Cell::Cell(Vector2 initPos): _wallDirection(0)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// Floor
	auto floorTxtr = ResourceManagers::GetInstance()->GetShader("Tile1.tga");
	_floorObj = std::make_shared<Sprite2D>(model, shader, floorTxtr);
	_floorObj->Set2DPosition(initPos);

	// Create Walls and Corners
}

void Cell::Draw()
{
	_floorObj->Draw();

	// Draw walls

	// Draw corners
}

void Cell::SetWalls(int wallBits)
{
	_wallDirection = wallBits & Wall::MASK;
}

bool Cell::IsRandomized()
{
	return _wallDirection & RANDOMIZED;
}
