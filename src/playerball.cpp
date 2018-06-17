#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerMouse.h>
#include "playerball.hpp"

using namespace cocos2d;

bool PlayerBall::init(float mass, Color4F const & color) {
	if (!Ball::init(mass, color)) return false;

	// Save the mouse position on the view
	auto elm = EventListenerMouse::create();
	elm->onMouseMove = [this] (EventMouse * em) {
		_mousePosInView = em->getLocationInView();
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(elm, this);

	return true;
}


void PlayerBall::move(float dt) {
	// Compute speed vector from mouse position
	Vec2 speed = convertToNodeSpace(_mousePosInView);
	if(speed.lengthSquared() > maxMouseDist * maxMouseDist) {
		speed.normalize();
		speed *= maxMouseDist;
	}
	speed *= speedCoef / std::pow(_mass, .3f);
	moveWithConstraints(speed * dt);
}
