#include "aiball.hpp"

using namespace cocos2d;

bool AiBall::init(float mass, Color4F const & color) {
	if (!Ball::init(mass, color)) return false;
	_speed.set(random(-100.f, 100.f), random(-100.f, 100.f));
	return true;
}


void AiBall::move(float dt) {
	_speed += 5 * Vec2(random(-1.f, 1.f), random(-1.f, 1.f));

	if(_speed.lengthSquared() > maxMouseDist * maxMouseDist) {
		_speed.normalize();
		_speed *= maxMouseDist;
	}
	_speed *= speedCoef / std::pow(_mass, .3f);
	moveWithConstraints(_speed * dt);
}
