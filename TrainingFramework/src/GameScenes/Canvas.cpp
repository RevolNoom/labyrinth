#include "Canvas.hpp"

void Canvas::Draw()
{
	for (auto& i : _canvasLayers)
		 for (auto& j : i.second)
			j->Draw();
}


void Canvas::Insert(LayerID id, std::shared_ptr<PhysicObject> newObject)
{
	_canvasLayers[id].emplace_back(newObject);
}

void Canvas::Remove(LayerID id, std::shared_ptr<PhysicObject> object)
{
	_canvasLayers[id].remove(object);
}

// Remove an Object from Canvas
// (or many, if they are duplicated)
void Canvas::Remove(std::shared_ptr<PhysicObject> object)
{
	for (auto& i : _canvasLayers)
		i.second.remove(object);
}

// Remove an Object from Canvas
// (or many, if they are duplicated)
void Canvas::Clear()
{
	_canvasLayers = {};
}

Canvas::CanvasLayer Canvas::GetLayer(LayerID id)
{
	return _canvasLayers[id];
}

Canvas::CanvasLayer Canvas::GetAll()
{
	Canvas::CanvasLayer sum;
	for (auto layer : _canvasLayers)
		sum.splice(sum.end(), layer.second);
	return sum;
}