#pragma once

#include <set>
#include <2d/CCNode.h>

class CameraLayer : public cocos2d::Node {
	std::set<cocos2d::Node *> _targets;

public:
};
