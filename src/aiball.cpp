#include "aiball.hpp"

using namespace cocos2d;

bool AiBall::init(float mass, Color4F const & color) {
	if (!Ball::init(mass, color)) return false;
	_speed.set(random(-100.f, 100.f), random(-100.f, 100.f));
	return true;
}


void AiBall::move(float dt) {
	Node * ballsNode = getParent();
	Vector<Node*> const & balls = ballsNode->getChildren();
	Vec2 pos = getPosition();

	_speed.setZero();

	// attraction / repulsion from other balls
	for(auto node : balls) {
		auto ball = static_cast<Ball*>(node);
		Vec2 dist = ball->getPosition() - pos;
		dist -= ball->radius() * dist.getNormalized();
		if(dist.getLengthSq() < sightRange * sightRange) {
			Vec2 ds = 1.5e6 * dist.getNormalized() / dist.lengthSquared();
			if (ball->radius() < _radius * eatMaxScale)
				_speed += ds;
			else if (ball->radius() * eatMaxScale > _radius)
				_speed -= ds;
		}
	}

	// repulsion from walls
	Vec2 const hFieldSize = getParent()->getContentSize() / 2;
	float leftDist  = pos.x + hFieldSize.x;
	float rightDist = pos.x - hFieldSize.x;
	float botDist   = pos.y + hFieldSize.y;
	float topDist   = pos.y - hFieldSize.y;

	_speed.x += 1e7 * (1 / leftDist / leftDist  - 1 / rightDist / rightDist);
	_speed.y += 1e7 * (1 / botDist / botDist - 1 / topDist / topDist);

	// speed limitation
	float maxSpeed = maxMouseDist * speedCoef * std::pow(_mass, -.3f);
	if (_speed.lengthSquared() > maxSpeed * maxSpeed)
		_speed = maxSpeed * _speed.getNormalized();

	moveWithConstraints(_speed * dt);
}
