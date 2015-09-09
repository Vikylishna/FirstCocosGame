#include "GameFieldScene.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

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

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
/*	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameField::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Just click into squares. You can do it!", "fonts/Marker Felt.ttf", 16);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
/*	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);*/

	//////////////////////////////////////
	//////////////////////////////////////
	int m = 15;		//Кол-во строк
	int n = 20;		//Кол-во столбцов
	int m_n = m * n;	//Общее количество


	std::vector <int> rectangle_type(m_n);	//Вектор, содержащий типы 4-хугольника.
	std::ifstream F;		// Поток для считывания из файла
	F.open("rectangle_type.txt", std::ios::in);			//СЛЕДИТЬ ЗА ТЕМ, ЧТОБЫ ФАЙЛ СУЩЕСТВОВАЛ И БЫЛ НУЖНОГО РАЗМЕРА, иначе поле будет оранжевым
	int i;
	for (int i = 0; (i < m_n) && (!F.eof()); i++){
		F >> rectangle_type[i];
	}
	F.close();
	//	if (i != m_n)		// Если файл закончился раньше, и часть массива rectangle_type осталась незаполненной
	// Проверка на то, что нет непотребных символов и цифр?

	int rectWidth = visibleSize.width / n;	//Ширину делим на кол-во столбцов.
	int rectHeight = visibleSize.height / m;	//Длину делим на кол-во строк.

	// 4 цвета и черная рамочка
	std::vector <Color4F> colors(5);
	colors[0] = Color4F(1, 0.3, 0.1, 1);		// 0 - проходимый, оранжевый
	colors[1] = Color4F(0.8, 0.8, 0.1, 1);		// 1 - проходимый, желтый
	colors[2] = Color4F(0, 0.5, 0, 1);			// 2 - непроходимый, зеленый
	colors[3] = Color4F(0.4, 0.4, 0.4, 1);		// 3 - непроходимый, серый
	colors[4] = Color4F(0, 0, 0, 1);			// 4 - рамочка, черный

	// 4 координаты четырехугольника
	Vec2 rectangle[4];
	rectangle[0] = Vec2(0, 0);
	rectangle[1] = Vec2(0, rectHeight);
	rectangle[2] = Vec2(rectWidth, rectHeight);
	rectangle[3] = Vec2(rectWidth, 0);

	// Заполняем поле игры квадратами
	for (int i = 0; i < m; i++)		//Проходим все строки
	for (int j = 0; j < n; j++) {		//Проходимся по столбцам
		// Определение цвета.
		int k = i * n + j;		// Индекс. (Кол-во нарисованных строк) * (кол-во плиток в строке) + номер плитки в текущей строке
		//rectangle_type[k] - цвет текущей плитки
		auto rectNode = DrawNode::create();
		rectNode->drawPolygon(rectangle, 4, colors[rectangle_type[k]], 1, colors[4]);		//Создаем полигон, потом даем ему координаты
		rectNode->setPosition(Vec2(origin.x + rectWidth*j, origin.y + rectHeight * i));	// (x - ширина, j - столбец;  y - высота, i - строка)
		this->addChild(rectNode);		// Добавляем, как-то цепляем к сцене, фиксируем на ней. Без этого действия ничего не отображается.
	}
	///////////////////////////////////////////////////////////////////////////////////

	return true;
}


void GameField::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
