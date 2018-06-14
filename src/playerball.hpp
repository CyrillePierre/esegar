#pragma once

#include <2d/CCDrawNode.h>
#include "util/factory.hpp"

/**
 * This ball is controlled by the player using the mouse and the keyboard
 */
class PlayerBall : public cocos2d::DrawNode, util::Factory<PlayerBall> {
	static constexpr float speedCoef = 1;
	static constexpr float maxMouseDist = 100;
	static constexpr float density = 1;

	cocos2d::Vec2 _speed = cocos2d::Vec2::ZERO;
	float         _mass;

public:
	using util::Factory<PlayerBall>::create;
    bool init(float mass, cocos2d::Color4F const & color);
	virtual void update(float dt);
};
