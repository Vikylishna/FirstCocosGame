#include "GameFieldScene.h"
#include <cstdlib>		//��� rand
#include <ctime>
#include <fstream>
//#include <locale>

USING_NS_CC;

Scene* GameField::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameField::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameField::init()
{
	//setlocale(LC_ALL, "RUS");
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
	int m = 15;		//���-�� �����
	int n = 20;		//���-�� ��������
	int m_n = m * n;	//����� ����������


	std::vector <int> rectangle_type(m_n);	//������, ���������� ���� 4-����������.
	std::ifstream F;		// ����� ��� ���������� �� �����
	F.open("rectangle_type.txt", std::ios::in);			//������� �� ���, ����� ���� ����������� � ��� ������� �������, ����� ���� ����� ���������
	int i;
	for (int i = 0; (i < m_n) && (!F.eof()); i++){
		F >> rectangle_type[i];
	}
	F.close();
	//	if (i != m_n)		// ���� ���� ���������� ������, � ����� ������� rectangle_type �������� �������������
	// �������� �� ��, ��� ��� ����������� �������� � ����?

	int rectWidth = visibleSize.width / n;	//������ ����� �� ���-�� ��������.
	int rectHeight = visibleSize.height / m;	//����� ����� �� ���-�� �����.

	// 4 ����� � ������ �������
	Color4F orange(1, 0.3, 0.1, 1);		// 0 - ����������
	Color4F yellow(0.8, 0.8, 0.1, 1);	// 1 - ����������
	Color4F green(0, 0.5, 0, 1);		// 2 - ������������
	Color4F gray(0.4, 0.4, 0.4, 1);		// 3 - ������������
	Color4F black(0, 0, 0, 1);			// 4 - �������

	// 4 ���������� ����������������
	Vec2 rectangle[4];
	rectangle[0] = Vec2(0, 0);
	rectangle[1] = Vec2(0, rectHeight);
	rectangle[2] = Vec2(rectWidth, rectHeight);
	rectangle[3] = Vec2(rectWidth, 0);

	Color4F color;		// ���� �������� �������� (������� ���� � �����)
	// ��������� ���� ���� ����������
	for (int i = 0; i < m; i++)		//�������� ��� ������
	for (int j = 0; j < n; j++) {		//���������� �� ��������
		// ����������� �����.
		int k = i * n + j;		// ������. (���-�� ������������ �����) * (���-�� ������ � ������) + ����� ������ � ������� ������
		switch (rectangle_type[k])		// ���������� ���� �������� ��������
		{
		case 0:
			color = orange;
			break;
		case 1:
			color = yellow;
			break;
		case 2:
			color = green;
			break;
		case 3:
			color = gray;
			break;
		}
		auto rectNode = DrawNode::create();
		rectNode->drawPolygon(rectangle, 4, color, 1, black);		//������� �������, ����� ���� ��� ����������
		rectNode->setPosition(Vec2(origin.x + rectWidth*j, origin.y + rectHeight * i));	// (x - ������, j - �������;  y - ������, i - ������)
		this->addChild(rectNode);		// ���������, ���-�� ������� � �����, ��������� �� ���. ��� ����� �������� ������ �� ������������.
	}

	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	//touch


	return true;
}


void GameField::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
