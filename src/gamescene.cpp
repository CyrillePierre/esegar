#include "gamescene.hpp"
#include "playerball.hpp"
#include "background.hpp"
#include "util/factory.hpp"

using namespace cocos2d;

bool GameScene::init() {
	if(!Scene::init()) return false;

	auto background = Factory<Background>::create({1000, 600}, 50);
	background->setPositionNormalized({.5, .5});
	addChild(background);

	auto playerball = Factory<PlayerBall>::create(10, {.8, .7, .2, 1});
	playerball->setPositionNormalized({.5, .5});
	addChild(playerball);

	return true;
}
