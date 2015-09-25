#ifndef __GAMEFIELD_SCENE_H__
#define __GAMEFIELD_SCENE_H__

#include "cocos2d.h"
#include "field.h"

template <class T>
class Coordinates
{
public:
	T x;
	T y;
	Coordinates(){};
	Coordinates(const T & x_new, const T & y_new)
	{
		x = x_new;
		y = y_new;
	};
};

class GameField : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

//	void onMouseUp(cocos2d::Event *event);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);

//	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);

	CREATE_FUNC(GameField);	// implement the "static create()" method manually

private:
	Field gameField;

	//Длина и ширина плитки (ее размеры). x - длина, y - ширина.
	//cocos2d::Size sizetile;
	Coordinates<int> sizetile;

	// Координаты предыдущего клика (точка, в которую уже проложен путь). Координаты поля gameField.
	Coordinates<int> coordsPreviousClick;

	cocos2d::Vec2 origin;

	/* Считываем сюда из файла "filenameOfSprite.txt":
	1 - имя файла с картинкой background'а
	2 - имя файла с картинкой игрока,
	3 - имя файла с картинкой пути. */
	std::map<std::string, std::string> filenameOfSprite;
	void insertOneElementInFilenameOfSpriteFromString(const char * & fileContents, const std::string & fullPath, const std::string & key);		// Для метода fillFilenameOfSpriteFromFile
	void fillFilenameOfSpriteFromFile();		// Считывает из файла filenameOfSprite.txt в map filenameOfSprite имена файлов.

	void resetCoordinatesClickAndDeletePath();		// Сбрасывает coordsPreviousClick.x и coordsPreviousClick.y и удаляет путь, проложенный спрайтами от точки до точки.
	void resetCoordinatesClick();
	void deletePath();

	// c - коэффициент. Во сколько раз картинка будет больше плитки.
	void addSprite(const std::string & fn, int coordOfTileX, int coordOfTileY, double c, const std::string & name);
};

#endif // __HELLOWORLD_SCENE_H__