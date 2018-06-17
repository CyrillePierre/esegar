#include <2d/CCDrawNode.h>
#include <base/ccRandom.h>
#include "foodgenerator.hpp"

using namespace cocos2d;

bool FoodGenerator::init(Node * foods) {
	schedule([this] (float) {
		Vec2 spawnSize = getParent()->getContentSize() / 2 - Size{15, 15};
		float radius = random(2.f, 10.f);
		Vec2 pos{random(-spawnSize.x, spawnSize.x), random(-spawnSize.y, spawnSize.y)};
		Color4F color{rand_0_1(), rand_0_1(), rand_0_1(), 1};

		auto food = DrawNode::create();
		food->setContentSize({radius * 2, radius * 2});
		food->drawDot(pos, radius, color);
		getParent()->getChildByName("foods")->addChild(food);
	}, .1, "gen");

}
