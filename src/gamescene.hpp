#pragma once

#include <2d/CCScene.h>
#include "util/factory.hpp"

class GameScene : public cocos2d::Scene, util::Factory<GameScene> {
public:
	using util::Factory<GameScene>::create;
    virtual bool init();
};
