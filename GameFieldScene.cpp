#include "GameFieldScene.h"
#include <string>
#include "functions.h"
#include <algorithm>

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

// Сбрасывает coordsPreviousClickX и coordsPreviousClickY и удаляет путь, проложенный спрайтами от точки до точки.
void GameField::resetCoordinatesClickAndDeletePath()
{
	coordsPreviousClickX = -1;
	coordsPreviousClickY = -1;

//	while (this->getChildByTag(13) != NULL)
//		this->removeChildByTag(13);

	cocos2d::Vector<Node *> vecChildren = this->getChildren();
	for (Vector<Node *>::iterator iter = vecChildren.begin(); iter != vecChildren.end(); iter++){
		int tag = (*(*iter)).getTag();
		if (tag == 13)
			this->removeChild(*iter, true);
	}
}

void GameField::onMouseUp(Event *event)
{
	EventMouse* e = (EventMouse*)event;
//	Point click = Point(e->getCursorX(), e->getCursorY()) - Director::getInstance()->getVisibleOrigin();

	// 1. Рассчитываем, в какую плитку попали
	int coordOfTileX = (e->getCursorX() - origin.x) / tileWidth;
	int coordOfTileY = (e->getCursorY() - origin.y) / tileHeight;

	// 2. Смотрим, проходимая ли она.
	if (!gameField.check_passible_and_correct(coordOfTileY, coordOfTileX))
	{
		// Сюда идти мы не можем.
		//Сбрасываем координаты предыдущего клика. И удаляем путь, если он есть.
		resetCoordinatesClickAndDeletePath();
	}

	// 3. Если объект с тегом 4 не существует, а это наш персонаж - cat, добавляем его в сцену.
	if (this->getChildByTag(4) == NULL)
	{
		auto cat_sprite = Sprite::create("cat.png");	// Добавим спрайт персонажа
		//Изменим сделаем: сделаем нужного зазмера.
		double coeff1 = ((double)tileWidth * 0.75) / ((double)cat_sprite->getBoundingBox().size.width);		//getContentSize().height - то же самое
		double coeff2 = ((double)tileHeight * 0.75) / ((double)cat_sprite->getBoundingBox().size.height);
		double coeff = std::min(coeff1, coeff2);
		cat_sprite->setScale(coeff1);		//Определили и задали требуемый размер
		cat_sprite->setPosition((coordOfTileX * tileWidth + tileWidth / 2), (coordOfTileY * tileHeight + tileHeight / 2));		// Помещаем в место клика
		cat_sprite->setTag(4);		// Назначаем тег 4
		addChild(cat_sprite, 15);
		return;
	}

	// 4. Если координаты нажатой кнопки совпадают с предыдущими (повторное нажатие на одно и то же место), перемещаем персонажа-кота на новое место.
	if ((coordOfTileX == coordsPreviousClickX) && (coordOfTileY == coordsPreviousClickY))
	{
		// Перемещаем cat_sprite в новую позицию.
		(this->getChildByTag(4))->setPosition((coordOfTileX * tileWidth + tileWidth / 2), (coordOfTileY * tileHeight + tileHeight / 2));
		//Сбрасываем координаты предыдущего клика. И удаляем путь, если он есть.
		resetCoordinatesClickAndDeletePath();
	}

	// 5. Если координаты не совпадают с предыдущими, ищем путь и показываем его игроку.
	//Сбрасываем предыдущий клик. И удаляем путь, если он есть.
	resetCoordinatesClickAndDeletePath();

	Vec2 cat_position = (this->getChildByTag(4))->getPosition();		// Получаем текущие координаты кота.
	int currentCoordOfTileX = (cat_position.x - origin.x) / tileWidth;
	int currentCoordOfTileY = (cat_position.y - origin.y) / tileHeight;

	// Ищем кратчайший путь
	std::vector<std::pair<int, int>> shortest_path = gameField.find_the_shortest_path(currentCoordOfTileY, currentCoordOfTileX, coordOfTileY, coordOfTileX);
	if (shortest_path.size() != 0)		// Если путь есть
	{
		coordsPreviousClickX = coordOfTileX;		// Меняем координаты предыдущего клика.
		coordsPreviousClickY = coordOfTileY;
		// "Рисуем" путь.
		for (std::vector<std::pair<int, int>>::size_type i = 0; i < shortest_path.size(); i++)
		{
			shortest_path[i].first;
			auto path_sprite = Sprite::create("circle.png");	// Спрайт пути.
			//Изменим сделаем: сделаем нужного зазмера.
			double coeff1 = ((double)tileWidth * 0.4) / ((double)path_sprite->getBoundingBox().size.width);		//getContentSize().height - то же самое
			double coeff2 = ((double)tileHeight * 0.4) / ((double)path_sprite->getBoundingBox().size.height);
			double coeff = std::min(coeff1, coeff2);
			path_sprite->setScale(coeff1);		//Определили и задали требуемый размер
			path_sprite->setPosition((shortest_path[i].second * tileWidth + tileWidth / 2), (shortest_path[i].first * tileHeight + tileHeight / 2));		// Помещаем в место клика
			path_sprite->setTag(13);		// Назначаем тег 13. По нему будем удалять.
			addChild(path_sprite, 13);
		}
	}
}