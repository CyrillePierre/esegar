#include <iostream>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerMouse.h>
#include "playerball.hpp"

using namespace cocos2d;

bool PlayerBall::init(float mass, Color4F const & color) {
	if(!DrawNode::init()) return false;

	setMass(mass);
	drawDot(Vec2::ZERO, _radius, color);

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


void PlayerBall::setMass(float m) {
	_mass = m;
	_radius = density * std::sqrt(_mass);
 }


void PlayerBall::update(float dt) {
	DrawNode::update(dt);

	// Compute speed vector from mouse position
	Vec2 speed = convertToNodeSpace(_mousePosInView);
	_mouseViewer->setPosition(speed);

	if(speed.lengthSquared() > maxMouseDist * maxMouseDist) {
		speed.normalize();
		speed *= maxMouseDist;
	}
	speed *= speedCoef;
	moveWithConstraints(speed * dt);
}


void PlayerBall::moveWithConstraints(Vec2 dp) {
	Vec2 const hFieldSize = getParent()->getContentSize() / 2;
	float sRadius = _radius - 15;
	Vec2 newPos = getPosition() + dp;

	// the ball cannot move out of the field
	if (newPos.x + sRadius > hFieldSize.x) newPos.x = hFieldSize.x - sRadius;
	else if (newPos.x - sRadius < -hFieldSize.x) newPos.x = -hFieldSize.x + sRadius;
	if (newPos.y + sRadius > hFieldSize.y) newPos.y = hFieldSize.y - sRadius;
	else if (newPos.y - sRadius < -hFieldSize.y) newPos.y = -hFieldSize.y + sRadius;

	setPosition(newPos);
}
