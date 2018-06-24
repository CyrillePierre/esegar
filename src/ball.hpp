#pragma once

#include <2d/CCDrawNode.h>

/**
 * The ball is an abstract class corresponding to a moveable ball.
 */
struct Ball : cocos2d::DrawNode {
protected:
	static constexpr float speedCoef    = 9;
	static constexpr float maxMouseDist = 100;
	static constexpr float density      = .03;
	static constexpr float boxOffset    = 15;
	static constexpr float eatMaxScale  = .75;

	float               _mass;
	float               _radius;
	cocos2d::Color4F    _color;

public:
    bool init(float mass, cocos2d::Color4F const & color);
	virtual void update(float dt);
	virtual void move(float dt) = 0;

protected:
	void setMass(float m);
	void moveWithConstraints(cocos2d::Vec2 dp);
	void eat();
	void eatEnemies();
};
