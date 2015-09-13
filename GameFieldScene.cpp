#include "GameFieldScene.h"

#include <string>
//#include "field.h"
#include "functions.h"
#include "functions.h"
#include <algorithm>
#include <algorithm>
//#include "field.h"
//#define COCOS2D_DEBUG 1
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
	origin = Director::getInstance()->getVisibleOrigin();

	// Фон.
	auto sprite_background = Sprite::create("white_background.jpg", Rect(0, 0, visibleSize.width, visibleSize.height));
	sprite_background->setAnchorPoint(Vec2(0, 0));
	sprite_background->setPosition(origin);// +Point(visibleSize.width / 2, visibleSize.height / 2));	// +Point(-80, 80));
	addChild(sprite_background, 0);

	// Игровое поле
	//Field gameField;

	//Вектор с именами файлов, из которых мы создаем спрайты.
	std::vector<std::string> filename(4);
	fill_arr_filename(filename);		// Заполняем его.

	//Длина и ширина одной плитки.
	tileWidth = visibleSize.width / gameField.get_n();	//Ширину делим на кол-во столбцов. x
	tileHeight = visibleSize.height / gameField.get_m();	//Высоту делим на кол-во строк. y

	// Заполняем поле игры плитками
	for (int i = 0; i < gameField.get_m(); i++)		//Проходим строки
	{
		for (int j = 0; j < gameField.get_n(); j++)		//Проходим столбцы
		{
			auto sprite1 = Sprite::create(filename[gameField.get_value(i, j)], Rect(0, 0, tileWidth - 2, tileHeight - 2));	//("mysprite.png", Rect(0,0,rectWidth,40))
			sprite1->setAnchorPoint(Vec2(0, 0));
			sprite1->setPosition(origin + Point(1, 1) + Point(tileWidth*j, tileHeight * i));		//(x - ширина, j - столбец;  y - высота, i - строка)
			addChild(sprite1, 10);
		}
	}

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
{
	EventMouse* e = (EventMouse*)event;
//	Point click = Point(e->getCursorX(), e->getCursorY()) - Director::getInstance()->getVisibleOrigin();

	// Рассчитываем, в какую плитку попали
	int coordOfTileX = (e->getCursorX() - origin.x) / tileWidth;
	int coordOfTileY = (e->getCursorY() - origin.y) / tileHeight;

	//Смотрим, проходимая ли она.
	if ((coordOfTileY >= gameField.get_m()) || (coordOfTileX >= gameField.get_n()) || !(gameField.passable(coordOfTileY, coordOfTileX))) return;		//Если координата проходимая и если мы попали в поле, продолжаем
	
	if (this->getChildByTag(4) == NULL)		//Если объект с тегом 4 не существует, а это cat, добавляем его в сцену.
	{
		auto cat_sprite = Sprite::create("cat.png");	// Добавим спрайт персонажа
		//Изменим сделаем: сделаем нужного зазмера.
		double coeff1 = ((double)tileWidth * 0.75) / ((double)cat_sprite->getBoundingBox().size.width);		//getContentSize().height - то же самое
		double coeff2 = ((double)tileHeight * 0.75) / ((double)cat_sprite->getBoundingBox().size.height);
		double coeff = std::min(coeff1, coeff2);
		cat_sprite->setScale(coeff1);		//Определили и задали требуемый размер
		cat_sprite->setPosition((coordOfTileX * tileWidth + tileWidth / 2), (coordOfTileY * tileHeight + tileHeight / 2));		// Помещаем в место клика
		cat_sprite->setTag(4);		// Назначаем тег 4
		addChild(cat_sprite, 12);
		return;
	}
	Vec2 cat_position = (this->getChildByTag(4))->getPosition();		// Получаем текущие координаты кота.
	int currentCoordOfTileX = (cat_position.x - origin.x) / tileWidth;
	int currentCoordOfTileY = (cat_position.y - origin.y) / tileHeight;
	log("current cat x = %d y = %d", currentCoordOfTileX, currentCoordOfTileY);
	log("new cat x = %d y = %d", coordOfTileX, coordOfTileY);
	if (gameField.find_the_shortest_path(currentCoordOfTileY, currentCoordOfTileX, coordOfTileY, coordOfTileX))		// Если путь есть
	{
		(this->getChildByTag(4))->setPosition((coordOfTileX * tileWidth + tileWidth / 2), (coordOfTileY * tileHeight + tileHeight / 2));		// Перемещаем cat_sprite в новую позицию.
	}

}