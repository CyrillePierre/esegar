#pragma once

#include "ball.hpp"

class AiBall : public Ball {
	static constexpr float sightRange = 1000;

	cocos2d::Vec2 _speed;

public:
	bool init(float mass, cocos2d::Color4F const & color);
	virtual void move(float dt);
};
