#include <2d/CCDrawNode.h>
#include <cocos2d.h>
#include <base/ccRandom.h>
#include "foodgenerator.hpp"

using namespace cocos2d;

bool FoodGenerator::init(Node * foods) {
	schedule([this] (float) {
		Vec2 spawnSize = getParent()->getContentSize() / 2 - Size{15, 15};
		float radius = random(4.f, 10.f);
		Vec2 pos{random(-spawnSize.x, spawnSize.x), random(-spawnSize.y, spawnSize.y)};
		Color4F color{rand_0_1(), rand_0_1(), rand_0_1(), 1};

		auto food = DrawNode::create();
		food->setContentSize({radius * 2, radius * 2});
		food->drawDot(Vec2::ZERO, radius, color);
		food->setPosition(pos);
		getParent()->getChildByName("foods")->addChild(food);

		// wave scale action
		float time = random(.7f, 2.f);
		food->runAction(RepeatForever::create(Sequence::create(
			EaseSineInOut::create(ScaleTo::create(time, 1.2f)),
			EaseSineInOut::create(ScaleTo::create(time, .8f)), nullptr)));
		
	}, .2, "gen");

}
