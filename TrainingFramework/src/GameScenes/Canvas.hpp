#pragma once

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <list>
#include <map>
#include <memory>
#include "BaseObject.h"

// Stores objects and draw them on the screen
// Canvas stores references to Objects
// Be sure to remove them
class Canvas
{
public:
	// TODO: DANGER!
	// I'd love to turn shared_ptr into weak_ptr
	// But technical difficulty: 
	// weak_ptr breaks here because it does not have operator==
	using CanvasLayer = std::list<std::shared_ptr<BaseObject>>;
	using LayerID = int;

	// Draw this Canvas on the screen
	// A canvas will be draw from the bottom layer up
	// Earliest inserted objects will be drawn first 
	void Draw();

	// Insert a newObject into a Canvas layer
	// Doesn't check for object duplication. Becareful!
	void Insert(LayerID id, std::shared_ptr<BaseObject> newObject);

	// Remove an Object from a Canvas layer
	void Remove(LayerID id, std::shared_ptr<BaseObject> object);

	// Remove an Object from Canvas
	void Remove(std::shared_ptr<BaseObject> object);

	// Clear everything on canvas
	void Clear();



	// TODO: Lists of shared_ptr mean
	// opportunities for memory leaks
	// TODO: Create an Iterator class

	// Return references of all objects in a Layer
	CanvasLayer GetLayer(LayerID id);

	// Return references of all objects of the Canvas
	CanvasLayer GetAll();

private:
	std::map<LayerID, CanvasLayer> _canvasLayers;
};

#endif /* CANVAS_HPP */