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
	setLocalZOrder(_mass);

	clear();
	drawDot(Vec2::ZERO, _radius, _color);
 }


void Ball::update(float dt) {
	DrawNode::update(dt);
	eat();
	eatEnemies();
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
	Node * foodsNode = getParent()->getParent()->getChildByName("foods");
	if (!foodsNode) return;
	Vector<Node*> const & foods = foodsNode->getChildren();
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


void Ball::eatEnemies() {
	Node * ballsNode = getParent();
	if (!ballsNode) return;
	Vector<Node*> const & balls = ballsNode->getChildren();
	float mass = _mass;
	std::vector<Node*> removeList;

	for(auto node : balls) {
		auto ball = static_cast<Ball*>(node);
		if(ball->_radius < eatMaxScale * _radius
			&& (getPosition() - ball->getPosition()).getLengthSq() < _radius * _radius)
		{
			mass += ball->_mass;
			removeList.push_back(node);
		}
	}

	for (auto node : removeList) node->removeFromParent();

	setMass(mass);
}
