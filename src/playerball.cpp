#include <iostream>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerMouse.h>
#include "playerball.hpp"

using namespace cocos2d;

bool PlayerBall::init(float mass, Color4F const & color) {
	if (!DrawNode::init()) return false;

	_mass = mass;
	float radius = density * std::sqrt(_mass);
	drawDot(Vec2::ZERO, radius, color);

	// debug mouse node
	auto mouseViewer = DrawNode::create();
	mouseViewer->drawDot(Vec2::ZERO, 10, {1, 0, 0, 1});
	addChild(mouseViewer);

	auto elm = EventListenerMouse::create();
	elm->onMouseMove = [this, mouseViewer] (EventMouse * em) {
		Vec2 mousePos = convertToNodeSpace(em->getLocationInView());
		std::cout << mousePos.x << ' ' << mousePos.y << std::endl;
		mouseViewer->setPosition(mousePos);
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(elm, mouseViewer);

	return true;
}


void PlayerBall::update(float dt) {
	DrawNode::update(dt);
	setPosition(getPosition() + _speed);
}
