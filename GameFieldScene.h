#ifndef __GAMEFIELD_SCENE_H__
#define __GAMEFIELD_SCENE_H__

#include "cocos2d.h"
#include "field.h"

class GameField : public cocos2d::Layer
{
	Field gameField;
	int tileWidth;
	int tileHeight;
	cocos2d::Vec2 origin;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void GameField::onMouseUp(cocos2d::Event *event);

	CREATE_FUNC(GameField);	// implement the "static create()" method manually
};

#endif // __HELLOWORLD_SCENE_H__
