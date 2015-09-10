#include "GameFieldScene.h"
#include <fstream>
#include <string>
#include <field.h>
#include <functions.h>

USING_NS_CC;

Scene* GameField::createScene()
{
	auto scene = Scene::create();		// 'scene' is an autorelease object	
	auto layer = GameField::create();		// 'layer' is an autorelease object
	scene->addChild(layer);		// add layer as a child to scene
	return scene;		// return the scene
}

// on "init" you need to initialize your instance
bool GameField::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Фон.
	auto sprite_background = Sprite::create("white_background.jpg", Rect(0, 0, visibleSize.width, visibleSize.height));
	sprite_background->setAnchorPoint(Vec2(0, 0));
	sprite_background->setPosition(origin);// +Point(visibleSize.width / 2, visibleSize.height / 2));	// +Point(-80, 80));
	addChild(sprite_background, 0);

	Field field;		//!!!!!!!!!!!!!!!!!

	std::vector<std::string> filename(4);			//!!!!!!!!!!!!!!!!!!!!!!!!!!
	fill_arr_filename(filename);		// Вектор содержащий имена файлов, из которых мы создаем спрайты

	int rectWidth = visibleSize.width / field.get_n();	//Ширину делим на кол-во столбцов. x
	int rectHeight = visibleSize.height / field.get_m();	//Длину делим на кол-во строк. y

//	std::string filename;		//Название файла с картинкой
	// Заполняем поле игры плитками
	for (int i = 0; i < field.get_m(); i++)		//Проходим все строки
		for (int j = 0; j < field.get_n(); j++) {		//Проходимся по столбцам
	/*		switch (field.get_value(i, j))		// Определяем картинку, загружаемую текущей плитки
			{
			case 0:
				filename = "grass1.jpg";	// 0 - проходимый
				break;
			case 1:
				filename = "grass2.jpg";	// 1 - проходимый
				break;
			case 2:
				filename = "wall1.jpg";		// 2 - непроходимый
				break;
			case 3:
				filename = "wall2.jpg";		// 3 - непроходимый
				break;
			}*/

			auto sprite1 = Sprite::create(filename[field.get_value(i, j)], Rect(0, 0, rectWidth - 2, rectHeight - 2));	//("mysprite.png", Rect(0,0,rectWidth,40))
			sprite1->setAnchorPoint(Vec2(0, 0));
			sprite1->setPosition(origin + Point(1,1) + Point(rectWidth*j, rectHeight * i));		//(x - ширина, j - столбец;  y - высота, i - строка)
			addChild(sprite1, 10);
		}

	return true;
}