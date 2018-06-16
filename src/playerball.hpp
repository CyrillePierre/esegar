#pragma once

#include <2d/CCDrawNode.h>

/**
 * This ball is controlled by the player using the mouse and the keyboard
 */
class PlayerBall : public cocos2d::DrawNode {
	static constexpr float speedCoef    = 2;
	static constexpr float maxMouseDist = 100;
	static constexpr float density      = 10;
	static constexpr float boxOffset    = 15;

	cocos2d::Vec2       _mousePosInView = cocos2d::Vec2::ZERO;
	float               _mass;
	float               _radius;
	cocos2d::DrawNode * _mouseViewer;

public:
    bool init(float mass, cocos2d::Color4F const & color);
	virtual void update(float dt);

private:
	void setMass(float m);
	void moveWithConstraints(cocos2d::Vec2 dp);
};
