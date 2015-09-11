#include "GameFieldScene.h"
#include <string>
#include "field.h"
#include "functions.h"
#include <algorithm>
#define COCOS2D_DEBUG 1
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

	// Игровое поле
	Field field;

	//Вектор с именами файлов, из которых мы создаем спрайты.
	std::vector<std::string> filename(4);
	fill_arr_filename(filename);		// Заполняем его.

	//Длина и ширина одной плитки.
	int rectWidth = visibleSize.width / field.get_n();	//Ширину делим на кол-во столбцов. x
	int rectHeight = visibleSize.height / field.get_m();	//Длину делим на кол-во строк. y

	// Заполняем поле игры плитками
	for (int i = 0; i < field.get_m(); i++)		//Проходим строки
	{
		for (int j = 0; j < field.get_n(); j++)		//Проходим столбцы
		{
			auto sprite1 = Sprite::create(filename[field.get_value(i, j)], Rect(0, 0, rectWidth - 2, rectHeight - 2));	//("mysprite.png", Rect(0,0,rectWidth,40))
			sprite1->setAnchorPoint(Vec2(0, 0));
			sprite1->setPosition(origin + Point(1, 1) + Point(rectWidth*j, rectHeight * i));		//(x - ширина, j - столбец;  y - высота, i - строка)
			addChild(sprite1, 10);
		}
	}

	// Добавим спрайт персонажа
	auto cat_sprite = Sprite::create("cat.png");
	//Изменим его: сделаем нужного зазмера.
	double coeff1 = ((double)rectWidth * 0.75) / ((double)cat_sprite->getBoundingBox().size.width);		//getContentSize().height - то же самое
	double coeff2 = ((double)rectWidth * 0.75) / ((double)cat_sprite->getBoundingBox().size.height);
	double coeff = std::min(coeff1, coeff2);
	//log("COEFF = %f", cat_sprite->getBoundingBox().size.width);
	cat_sprite->setScale(coeff1);		//Определили и задали требуемый размер
	cat_sprite->setAnchorPoint(Vec2(0.5, 0.5));
	cat_sprite->setPosition(origin + Point(rectWidth / 2, rectHeight / 2));
	cat_sprite->setTag(4);
	addChild(cat_sprite, 12);

	///////////////////////////////////////////////////////////////////
	///
	///  Touch
	///
	///////////////////////////////////////////////////////////////////

	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseUp = CC_CALLBACK_1(GameField::onMouseUp, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse_listener, this);

	return true;
}

void GameField::onMouseUp(Event *event)
{// Тут будет что-то другое. Я просто смотрю как оно работает.

	if (this->getChildByTag(4) != NULL)		//Если объект с тегом 4 существует, а это cat.
		log("It is exist");
	else
		log("Cat don't exist");

}