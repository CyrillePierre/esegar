#include "gamescene.hpp"
#include "playerball.hpp"
#include "background.hpp"
#include "util/factory.hpp"

using namespace cocos2d;

bool GameScene::init() {
	if(!Scene::init()) return false;

	Size fieldSize{2000, 2000};

	// the root node of all game elements
	auto field = Node::create();
	field->setContentSize(fieldSize);
	addChild(field);

	auto background = Factory<Background>::create(fieldSize, 50);
	background->setPositionNormalized({.5, .5});
	field->addChild(background);

	auto playerball = Factory<PlayerBall>::create(10, {.8, .7, .2, 1});
	playerball->setPositionNormalized({.5, .5});
	field->addChild(playerball);

	// the player ball is always on the center of the screen
	Vec2 halfScreenSize = getContentSize() / 2;
	field->schedule([=] (float dt) {
		field->setPosition(halfScreenSize - playerball->getPosition());
	}, "camera_center");

	return true;
}
