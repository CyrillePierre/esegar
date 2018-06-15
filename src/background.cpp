#include "background.hpp"

using namespace cocos2d;

bool Background::init(cocos2d::Size size, float cellSize) {
	if(!DrawNode::init()) return false;

	setContentSize(size);

	// draw a grid
	Color4F color{1, 1, 1, 1};
	Vec2 halfSize = size/2;
	drawRect(-halfSize, halfSize, color);
	for(float i = cellSize - halfSize.x; i < halfSize.x; i += cellSize)
		drawLine({i, -halfSize.y}, {i, halfSize.y}, color);
	for(float i = cellSize - halfSize.y; i < halfSize.y; i += cellSize)
		drawLine({-halfSize.x, i}, {halfSize.x, i}, color);

	return true;
}
