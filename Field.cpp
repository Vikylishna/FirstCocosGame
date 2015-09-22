#include "Field.h"
#include <fstream>
#include <queue>
#include "cocos2d.h"

Field::Field()
{

}

void Field::createField()
{
	// Заполняем вектора typetilePassable и typetileFilename
	readFilenamePassable();
	fillFieldMN();
	//Проверка.

	/*	CCLOG("typetilePassable.");
	for (int i = 0; i < typetilePassable.size(); i++)
	CCLOG("typetile = %u, passable = %u ", i, typetilePassable[i]);
	CCLOG("typetileFilename");
	for (int i = 0; i < typetileFilename.size(); i++)
	CCLOG("typetile = %u, filename = %s ", i, typetileFilename[i].c_str());
	CCLOG("\n Field.");
	for (int i = 0; i < m; i++){
	for (int j = 0; j < n; j++)
	CCLOG("typetile = %u ", field[i][j]);
	CCLOG("");
	}*/
}

/* Кол-во плиток в высоту (кол-во строк) */
int Field::getRowNums()
{
	return m;
}

/* Кол-во плиток в длину (кол-во столбцов) */
int Field::getColumnNums()
{
	return n;
}

/* Возвращает значение field[y][x]. */
int Field::getValue(int y, int x)
{
	return field[y][x];
}

/* Возвращает значение typetilePassable[i]. */
int Field::getTypetilePassable(int i)
{
	return typetilePassable[i];
}

/* Возвращает значение typetileFilename[i]. */
std::string Field::getTypetileFilename(int i)
{
	return typetileFilename[i];
}

/* Считывает из файла "filenamePassable.txt" имя файла, откуда берется картинка и проходимость плитки с такой картинкой.
Записывает их в:
    vector typetilePassable: индекс - тип плитки, значение - проходимость.
    vector typetileFilename: индекс - тип плитки, значение - имя файла. */
void Field::readFilenamePassable()
{
	std::string path = "filenamePassable.txt";
	FILE *file = fopen(path.c_str(), "r");		// Открываем файл для чтения.
	if (!file)
	{
		CCLOG("can not open file %s", path.c_str());
		return;
	}

	char fn[40];		// Имя файла должно иметь длину <= 40.
	int passable = 0;

	int check = 0;		// Проверка корректности чтения.
	// Считываем все строки из файла.
	while ((check = fscanf(file, "%s%u", fn, &passable)) != EOF && check == 2) {		// Считали 2 переменные. Если не 2, то до конца не дошли, пишем об этом в лог.
		// Записываем их в соответствующие vector'а
		typetilePassable.push_back(passable);
		std::string tmp(fn);
		typetileFilename.push_back(tmp);
	}
	if (check != -1) CCLOG("Uncorrect data in %s.", path.c_str());		// Если не дошли до конца файла.
	fclose(file);
}

/* Заполняет поле: считывает размерность поля из файла "field.txt" в переменные m и n и типы плиток (проходимость) в вектор field.
1-е число в файле - m (кол-во строк), второе - n (кол-во столбцов), остальные - field
*/
void Field::fillFieldMN()
{
	std::string path = "field.txt";
	FILE *file = fopen(path.c_str(), "r");		// Открываем файл для чтения.
	if (!file)
	{
		CCLOG("can not open file %s", path.c_str());
		return;
	}
	// Считываем размерность
	if (fscanf(file, "%u", &m) != 1)
		cocos2d::log("You must fill the file 'field.txt' correct! Wrong m.");
	if (fscanf(file, "%u", &n) != 1)
		cocos2d::log("You must fill the file 'field.txt' correct! Wrong n.");

	field.resize(m);
	// Заполняем поле Field типами плиток
	for (int i = 0; i < m; i++)
	{
		field[i].resize(n);
		for (int j = 0; j < n; j++)
		if (fscanf(file, "%u", &field[i][j]) != 1)		// Если не получилось считать, выводим ошибку в лог.
		{
			cocos2d::log("You must fill the file 'field.txt' correct! We need more types of tiles.");
		}
	}
	fclose(file);
}

/* Проверяет клетку на проходимость. */
bool Field::checkPassible(int y, int x)
{
	return typetilePassable[field[y][x]];
}

/* Проверяет клетку на то, что она имеет годные координаты. */
bool Field::checkCorrect(int y, int x)
{
	return (y >= 0 && y < m && x >= 0 && x < n) ? true : false;
}

/* Возвращает 1, если клетка ок. */
bool Field::checkCorrectAndPassible(int y, int x)
{
	return (checkCorrect(y, x) && checkPassible(y, x)) ? true : false;
}

/* Если все норм., помещаем вершины в очередь и добавляем к ним путь. */
void Field::addVertexInQueue(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int new_y, int new_x)
{
	// Смотрим, чтобы добавляемые в очередь вершины были: проходимы, непросмотрены и существовали.
	if (checkCorrectAndPassible(new_y, new_x) && path[new_y][new_x] == -1)
	{
		q.push(std::pair<int, int>(new_y, new_x));		// Помещаем вершину в очередь.
	}
}

/* Если все норм., помещаем вершины в очередь и добавляем к ним путь. */
void Field::updatePath(std::vector< std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x)
{
	// Смотрим, чтобы добавляемые в очередь вершины были: проходимы, непросмотрены и существовали.
	if (checkCorrectAndPassible(new_y, new_x) && path[new_y][new_x] == -1)
	{
		path[new_y][new_x] = path[old_y][old_x] + 1;	// [old_y][old_x] - откуда пришли.
	}
}

/* Если все норм., помещаем вершины в очередь и добавляем к ним путь. */
void Field::addVertexInQueueAndUpdatePath(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x)
{
	addVertexInQueue(q, path, new_y, new_x);
	updatePath(path, new_y, new_x, old_y, old_x);
}

// Проходится по всем вмежным с (x, y) вершинам, кладет их в очередь и добавляет к ним путь.
void Field::goToAllAdjacentVertices(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int y, int x)
{
	addVertexInQueueAndUpdatePath(q, path, y + 1, x, y, x);		// Обходим все смежные с (x, y) вершины по часовой стрелке.
	addVertexInQueueAndUpdatePath(q, path, y, x + 1, y, x);
	addVertexInQueueAndUpdatePath(q, path, y - 1, x, y, x);
	addVertexInQueueAndUpdatePath(q, path, y, x - 1, y, x);
}

// Возвращает путь, если он существует (из (y1, x1) в (y2, x2)). Если не существует->пустой вектор.
// Путь от (y1, x1) к (y2, x2) возвращается в обратном порядке, т.е. от (y2, x2) к (y1, x1)
std::vector<std::pair<int, int>> Field::findTheShortestPath(int y1, int x1, int y2, int x2)
{
	// Вектор путей. Каждая ячейка содержит длину пути. Если (значение в этой ячейке == -1) -> эта ячейка еще не посещена.
	std::vector<std::vector<int>> path(m);
	for (std::vector < std::vector<int>>::size_type i = 0; i < m; i++)		// Делаем его нужной размерности
		path[i].resize(n, -1);
	
	// Очередь, содержащая пары с координатами (y, x).
	std::queue<std::pair<int, int>> q;
	q.push(std::pair<int, int>(y1, x1));	// Поместили начальную точку в очередь.
	path[y1][x1] = 0;		// Расстояние до начальной вершины == 0.

	bool flag = 0;		// Флаг отражает, нашли мы нужную вершину или нет. 0 - нет.

	while (q.size() > 0)		// Пока не просмотрели все доступные вершины.
	{
		std::pair<int, int> current_vertex = q.front();		// Извлекаем из очереди вершину (текущая вершина)

		// Если мы встретили "конечную, требуемую" вершину. Путь найден. Вершина находится наверху очереди.
		if (current_vertex.first == y2 && current_vertex.second == x2)
		{
			flag = 1;
			break;
		}
		q.pop();

		/* Просматриваем все смежные с текущей вершиной вершины ( <= 4 ) и смотрим, чтобы они были: проходимы, непросмотрены.
		Если все норм., помещаем вершины в очередь и добавляем к ним путь. */
		goToAllAdjacentVertices(q, path, current_vertex.first, current_vertex.second);
	}

	// К этому моменту путь найден.
	// Ищем его в матрице путей.
	std::vector<std::pair<int, int>> shortest_path;
	if (flag == 1)		// Если путь есть, построим его по таблице путей.
	{
		int x = x2, y = y2;		// Координаты конца пути.
		int current = path[y][x];	// Чиселка - текущее значение пути, сколько осталось клеток до достижения цели - конечной точки.
		while (current != 0)
		{
			shortest_path.push_back(std::pair<int, int>(y, x));		// Записываем последнюю точку пути в вектор shortest_path
			// Ищем предыдущую точку пути. Точку, значение в которой == current - 1. Проверяем окрестность точки, в которой находимся.
			if (checkCorrect(y + 1, x) && (path[y + 1][x] == current - 1))
				y++;

			else if (checkCorrect(y, x + 1) && (path[y][x + 1] == current - 1))
				x++;

			else if (checkCorrect(y - 1, x) && (path[y - 1][x] == current - 1))
				y--;

			else if (checkCorrect(y, x - 1) && (path[y][x - 1] == current - 1))
				x--;

			// Нашли точку.
			current = path[y][x];		// Сохраняем новую длину пути. То же самое, что current--
		}
		//shortest_path.push_back(std::pair<int, int>(y1, x1));		// Заталкиваем последнюю точку. Не нужна: на ней кот.
	}

// Тест, вывод пути.
//	for (int i = 0; i < shortest_path.size(); i++)
//cocos2d::log("y = %d, x = %d", shortest_path[i].first, shortest_path[i].second);

/*	Тест, вывод матрицы путей.
std::ofstream F("test.txt", std::ios::out);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			F << ways[i][j] << " ";
		}
		F << '\n';
	}
	F.close();*/

	return shortest_path;
}