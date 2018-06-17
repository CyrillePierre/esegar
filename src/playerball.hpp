#pragma once

#include "ball.hpp"

/**
 * This ball is controlled by the player using the mouse and the keyboard
 */
class PlayerBall : public Ball {
	cocos2d::Vec2       _mousePosInView = cocos2d::Vec2::ZERO;

public:
	bool init(float mass, cocos2d::Color4F const & color);
	virtual void move(float dt);
};
