#include "gamescene.hpp"
#include "playerball.hpp"

using namespace cocos2d;

bool GameScene::init() {
	if (!Scene::init()) return false;

	auto playerball = PlayerBall::create(10, Color4F{.8, .7, .2, 1});
	playerball->setPositionNormalized({.5, .5});
	addChild(playerball);

	return true;
}
