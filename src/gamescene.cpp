#include "gamescene.hpp"
#include "playerball.hpp"
#include "background.hpp"
#include "util/factory.hpp"

using namespace cocos2d;

bool GameScene::init() {
	if(!Scene::init()) return false;

	// the root node of all game elements
	auto field = Node::create();
	field->setContentSize(getContentSize());
	addChild(field);

	auto background = Factory<Background>::create({1000, 600}, 50);
	background->setPositionNormalized({.5, .5});
	field->addChild(background);

	auto playerball = Factory<PlayerBall>::create(10, {.8, .7, .2, 1});
	playerball->setPositionNormalized({.5, .5});
	field->addChild(playerball);

	field->schedule([this, field, playerball] (float dt) {
		static Vec2 const halfSize = this->getContentSize() / 2;
		field->setPosition(halfSize - playerball->getPosition());
	}, "camera_center");

	return true;
}
