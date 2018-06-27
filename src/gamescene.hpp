#pragma once

#include <2d/CCScene.h>

class PlayerBall;

class GameScene : public cocos2d::Scene {
	char _i = 0;
	PlayerBall * _playerball;

public:
    virtual bool init();
};
