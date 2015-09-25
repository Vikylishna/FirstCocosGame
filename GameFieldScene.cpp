#include "GameFieldScene.h"
#include <string>
#include <algorithm>
#include <CCFileUtils.h>

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

	// Считываем из файла имена файлов, которые будем использовать для спрайтов.
	fillFilenameOfSpriteFromFile();

	// Фон.
	auto sprite_background = Sprite::create(filenameOfSprite["background"], Rect(0, 0, visibleSize.width, visibleSize.height));	//"whiteBackground.jpg"
	sprite_background->setPosition(origin + visibleSize/2);		// +Point(visibleSize.width / 2, visibleSize.height / 2));	// +Point(-80, 80));
	addChild(sprite_background);

	gameField.createField();

	/* Длина и ширина одной плитки.
	 Ширину делим на кол-во столбцов.
	 Высоту делим на кол-во строк. y */
	//sizetile.setSize(visibleSize.width / gameField.getColumnNums(), visibleSize.height / gameField.getRowNums());
	sizetile.x = visibleSize.width / gameField.getColumnNums();		// Ширину делим на кол-во столбцов. x
	sizetile.y = visibleSize.height / gameField.getRowNums();	// Высоту делим на кол-во строк. y

	coordsPreviousClick.x = -1;
	coordsPreviousClick.y = -1;

	// Заполняем поле игры плитками
	for (int i = 0; i < gameField.getRowNums(); i++)		// Проходим строки
	{
		for (int j = 0; j < gameField.getColumnNums(); j++)		// Проходим столбцы
		{
			// gameField.getValue(i, j) - тип текущей плитки.
			addSprite(gameField.getTypetileFilename(gameField.getValue(i, j)), j, i, 1, "tile");
		}
	}



	///////////////////////////////////////////////////////////////////
	///
	///  Touch
	///
	///////////////////////////////////////////////////////////////////
/*
	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseUp = CC_CALLBACK_1(GameField::onMouseUp, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse_listener, this);
*/
	return true;
}

// Функция заполнения мэпа. key - ключ. Значение считывается из строки, которую считали из файла.
// Имена файлов должны быть < 50 символов.
void GameField::insertOneElementInFilenameOfSpriteFromString(const char * & fileContentsBegin, const std::string & fullPath, const std::string & key)
{
	char fn[50];		// Имя файла должно иметь длину <= 50.

	while ((*fileContentsBegin) != 61 && (*fileContentsBegin) != '\0')		// Пропускаем непотребные символы.
	{
		fileContentsBegin++;
	}
	fileContentsBegin++;		// пропускаем '='
	fileContentsBegin++;		// пропускаем после "=" 1 символ (пробел).
	int i = 0;
	while (*fileContentsBegin != ' ' && *fileContentsBegin != '\0')		// Считываем имя файла до пробела.
	{
		fn[i] = *fileContentsBegin;
		fileContentsBegin++;
		i++;
	}
	fn[i] = '\0';
	//CCLOG("MY STRING %s", fn);
	filenameOfSprite.insert(std::pair<std::string, std::string>(key, std::string(fn)));		// Вставка в мэп.
}

void GameField::fillFilenameOfSpriteFromFile()
{
	std::string path = "filenameOfSprite.txt";
	ssize_t fileSize = 0;		// Размер содержимого файла, который мы будем читать.

	// Получаем полный путь к файлу.
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path.c_str());

	// Если файл не существует.
	if (!CCFileUtils::sharedFileUtils()->isFileExist(fullPath))
	{
		CCLOG("File %s not exists.", path.c_str());

		return;
	}

	// Считываем содержимое из файла.
	//unsigned char * fileContents = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &fileSize);
	//unsigned char * fileContentsBegin = fileContents;

	std::string fileContents = CCFileUtils::sharedFileUtils()->getStringFromFile(fullPath.c_str());
	const char * fileContentsBegin = fileContents.c_str();		// Указатель, которым будем ходить по строке.

	insertOneElementInFilenameOfSpriteFromString(fileContentsBegin, fullPath, "background");
	insertOneElementInFilenameOfSpriteFromString(fileContentsBegin, fullPath, "player");
	insertOneElementInFilenameOfSpriteFromString(fileContentsBegin, fullPath, "path");

	//delete[] fileContents;

	/* Тест.
	for (auto iter = filenameOfSprite.begin(); iter != filenameOfSprite.end(); iter++)
		CCLOG("%s %s", iter->first.c_str(), iter->second.c_str()); */
}

void GameField::resetCoordinatesClick()
{
	coordsPreviousClick.x = -1;
	coordsPreviousClick.y = -1;
}

void GameField::deletePath()
{
//	while (this->getChildByName("path") != NULL)
//		this->removeChildByName("path");

	cocos2d::Vector<Node *> vecChildren = this->getChildren();
	for (auto iter = vecChildren.begin(); iter != vecChildren.end(); iter++)
	{
		if ((*iter)->getName() == "path")		// Если это часть пути (спрайт пути), удаляем его.
			this->removeChild(*iter, true);
	}
}

// Сбрасывает coordsPreviousClick.x и coordsPreviousClick.y и удаляет путь, проложенный спрайтами от точки до точки.
void GameField::resetCoordinatesClickAndDeletePath()
{
	resetCoordinatesClick();
	deletePath();
}

// c - коэффициент. Во сколько раз картинка будет больше плитки.
void GameField::addSprite(const std::string & fn, int coordOfTileX, int coordOfTileY, double c, const std::string & spriteName)
{
	auto sprite = Sprite::create(fn);
	//Изменим спрайт: сделаем нужного размера. Подгоним к размеру плитки.
	double coeff1 = ((double)sizetile.x * c) / ((double)sprite->getContentSize().width);			//getBoundingBox().size.width);		//getContentSize().height - то же самое
	double coeff2 = ((double)sizetile.y * c) / ((double)sprite->getContentSize().height);		//getBoundingBox().size.height);
	double coeff = std::min(coeff1, coeff2);
	sprite->setScale(coeff1);		//Определили и задали требуемый размер.
	sprite->setPosition(origin + Point((coordOfTileX * sizetile.x + sizetile.x / 2), (coordOfTileY * sizetile.y + sizetile.y / 2)));	// Задаем координаты.
	sprite->setName(spriteName);		// Назначаем имя.
	addChild(sprite);
}

void GameField::onMouseUp(Event *event)
{
	EventMouse* e = (EventMouse*)event;
//	Point click = Point(e->getCursorX(), e->getCursorY()) - Director::getInstance()->getVisibleOrigin();

	// 1. Рассчитываем, в какую плитку попали. Получаем координаты клика по плитке поля gameField.
	Coordinates<int> coordsCurrentClick;
	coordsCurrentClick.x = (e->getCursorX() - origin.x) / sizetile.x;
	coordsCurrentClick.y = (e->getCursorY() - origin.y) / sizetile.y;

	// 2. Смотрим, проходимая ли она.
	if (!gameField.checkCorrectAndPassible(coordsCurrentClick.y, coordsCurrentClick.x))
	{
		// Плитка непроходимая.
		//Сбрасываем координаты предыдущего клика. И удаляем путь, если он есть.
		resetCoordinatesClickAndDeletePath();
		return;
	}

	// 3. Если объект с именем "player" не существует, а это наш персонаж - cat, добавляем его в сцену.
	if (this->getChildByName("player") == NULL)
	{
		addSprite(filenameOfSprite["player"], coordsCurrentClick.x, coordsCurrentClick.y, 0.75, "player");
		return;
	}

	// 4. Если координаты нажатой кнопки совпадают с предыдущими (повторное нажатие на одно и то же место), перемещаем персонажа-кота на новое место.
	if ((coordsCurrentClick.x == coordsPreviousClick.x) && (coordsCurrentClick.y == coordsPreviousClick.y))
	{
		// Перемещаем player'а в новую позицию.
		(this->getChildByName("player"))->setPosition((coordsCurrentClick.x * sizetile.x + sizetile.x / 2), (coordsCurrentClick.y * sizetile.y + sizetile.y / 2));
		//Сбрасываем координаты предыдущего клика. И удаляем путь, если он есть.
		resetCoordinatesClickAndDeletePath();
	}

	// 5. Если координаты не совпадают с предыдущими, ищем путь и показываем его игроку.
	//Сбрасываем предыдущий клик. И удаляем путь, если он есть.
	resetCoordinatesClickAndDeletePath();

	Vec2 cat_position = (this->getChildByName("player"))->getPosition();		// Получаем текущие координаты кота.
	int currentCoordOfTileX = (cat_position.x - origin.x) / sizetile.x;
	int currentCoordOfTileY = (cat_position.y - origin.y) / sizetile.y;

	// Ищем кратчайший путь
	std::vector<std::pair<int, int>> shortest_path = gameField.findTheShortestPath(currentCoordOfTileY, currentCoordOfTileX, coordsCurrentClick.y, coordsCurrentClick.x);
	if (shortest_path.size() != 0)		// Если путь есть
	{
		coordsPreviousClick.x = coordsCurrentClick.x;		// Меняем координаты предыдущего клика.
		coordsPreviousClick.y = coordsCurrentClick.y;
		// "Рисуем" путь.
		for (std::vector<std::pair<int, int>>::size_type i = 0; i < shortest_path.size(); i++)
		{
			addSprite(filenameOfSprite["path"], shortest_path[i].second, shortest_path[i].first, 0.3, "path");
		}
	}
}