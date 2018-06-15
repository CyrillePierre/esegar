#pragma once

#include <2d/CCDrawNode.h>

/**
 * This ball is controlled by the player using the mouse and the keyboard
 */
class Background : public cocos2d::DrawNode {
public:
    bool init(cocos2d::Size size, float cellSize);
};
