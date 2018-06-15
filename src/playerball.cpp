#include <iostream>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerMouse.h>
#include "playerball.hpp"

using namespace cocos2d;

bool PlayerBall::init(float mass, Color4F const & color) {
	if(!DrawNode::init()) return false;

	_mass = mass;
	float radius = density * std::sqrt(_mass);
	drawDot(Vec2::ZERO, radius, color);

	// debug mouse node
	_mouseViewer = DrawNode::create();
	_mouseViewer->drawDot(Vec2::ZERO, 10, {1, 0, 0, 1});
	addChild(_mouseViewer);

	// Save the mouse position on the view
	auto elm = EventListenerMouse::create();
	elm->onMouseMove = [this] (EventMouse * em) {
		_mousePosInView = em->getLocationInView();
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(elm, this);

	scheduleUpdate();

	return true;
}


void PlayerBall::update(float dt) {
	DrawNode::update(dt);

	// Compute speed vector from mouse position
	_speed = convertToNodeSpace(_mousePosInView);
	_mouseViewer->setPosition(_speed);

	if(_speed.lengthSquared() > maxMouseDist * maxMouseDist) {
		_speed.normalize();
		_speed *= maxMouseDist;
	}
	_speed *= speedCoef;
	setPosition(getPosition() + _speed * dt);
}
