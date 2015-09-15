#ifndef __GAMEFIELD_SCENE_H__
#define __GAMEFIELD_SCENE_H__

#include "cocos2d.h"
#include "field.h"

class GameField : public cocos2d::Layer
{
	Field gameField;	// Нужно ли сделать эту переменную глобальной/синглтоном? Либо оставить тут.
	int tileWidth;		// Ширина плитки
	int tileHeight;		// Длина плитки
	int coordsPreviousClickX = -1;		// Координаты предыдущего клика (точка, в которую уже продожен путь)
	int coordsPreviousClickY = -1;
	cocos2d::Vec2 origin;
	void resetCoordinatesClickAndDeletePath();		// Сбрасывает coordsPreviousClickX и coordsPreviousClickY и удаляет путь, проложенный спрайтами от точки до точки.
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onMouseUp(cocos2d::Event *event);

	void addSprite(int coordOfTileX, int coordOfTileY, double c, int tag, int zOrder);		// c - коэффициент. Во сколько раз картинка будет больше плитки.

	CREATE_FUNC(GameField);	// implement the "static create()" method manually
};

#endif // __HELLOWORLD_SCENE_H__