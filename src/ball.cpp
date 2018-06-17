#include "ball.hpp"

using namespace cocos2d;

bool Ball::init(float mass, Color4F const & color) {
	if(!DrawNode::init()) return false;

	_color = color;
	setMass(mass);
	scheduleUpdate();

	return true;
}


void Ball::setMass(float m) {
	_mass = m;
	_radius = std::sqrt(_mass / density);

	clear();
	drawDot(Vec2::ZERO, _radius, _color);
 }


void Ball::update(float dt) {
	DrawNode::update(dt);
	eat();
	move(dt);
}


void Ball::moveWithConstraints(Vec2 dp) {
	Vec2 const hFieldSize = getParent()->getContentSize() / 2;
	float sRadius = _radius - 15;
	Vec2 newPos = getPosition() + dp;

	// the ball cannot move out of the field
	if(newPos.x + sRadius > hFieldSize.x) newPos.x = hFieldSize.x - sRadius;
	else if(newPos.x - sRadius < -hFieldSize.x) newPos.x = -hFieldSize.x + sRadius;
	if(newPos.y + sRadius > hFieldSize.y) newPos.y = hFieldSize.y - sRadius;
	else if(newPos.y - sRadius < -hFieldSize.y) newPos.y = -hFieldSize.y + sRadius;

	setPosition(newPos);
}


void Ball::eat() {
	Vector<Node*> const & foods = getParent()->getChildByName("foods")->getChildren();
	float mass = _mass;
	std::vector<Node*> removeList;

	// increment the mass for every encountered food
	for(auto food : foods) {
		if((getPosition() - food->getPosition()).getLengthSq() < _radius * _radius) {
			float dmass = food->getContentSize().width / 2 ;
			dmass *= dmass * density;
			mass += dmass;
			removeList.push_back(food);
		}
	}

	for (auto node : removeList) node->removeFromParent();

	setMass(mass);
}
