#include <iostream>
#include "gamescene.hpp"
#include "playerball.hpp"
#include "background.hpp"
#include "foodgenerator.hpp"
#include "util/factory.hpp"
#include "aiball.hpp"

using namespace cocos2d;

bool GameScene::init() {
	if(!Scene::init()) return false;

	Size fieldSize{2000, 2000};

	// the root node of all game elements
	auto field = Node::create();
	field->setContentSize(fieldSize);
	addChild(field);

	auto background = Factory<Background>::create(fieldSize, 50);
	background->setOpacity(50);
//	background->setPositionNormalized({.5, .5});
	field->addChild(background);

	auto foods = Node::create();
	field->addChild(foods, 0, "foods");
	auto foodGenerator = Factory<FoodGenerator>::create(foods);
	field->addChild(foodGenerator);

	auto balls = Node::create();
	balls->setContentSize(fieldSize);
	field->addChild(balls, 1, "balls");

	auto playerball = Factory<PlayerBall>::create(10, {.8, .7, .2, 1});
	balls->addChild(playerball);

	// the player ball is always on the center of the screen
	Vec2 halfScreenSize = getContentSize() / 2;
	field->schedule([=] (float dt) {
		if (!playerball->isRunning()) return;
		field->setPosition(halfScreenSize - playerball->getPosition());
	}, "camera_center");

	// create enemies
	for(int i = 0; i < 10; ++i) {
		Color4F color{rand_0_1(), rand_0_1(), rand_0_1(), 1};
		auto aiball = Factory<AiBall>::create(random(50, 150), color);
		balls->addChild(aiball);
		aiball->setPositionNormalized({random(-.5f, .5f), random(-.5f, .5f)});
	}

	return true;
}
