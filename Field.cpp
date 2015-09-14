#include "Field.h"
#include <fstream>
#include <queue>

int Field::get_m()		// Кол-во плиток в высоту (кол-во строк)
{
	return m;
}

int Field::get_n()		// Кол-во плиток в длину (кол-во столбцов)
{
	return n;
} 

int Field::get_value(int y, int x)
{
	return field[y][x];
}

Field::Field()
{
	std::ifstream F1;		// Поток для считывания из файла размера поля
	F1.open("size_field.txt", std::ios::in);
	F1 >> m;
	F1 >> n;
	F1.close();

	std::ifstream F;		// Поток для считывания из файла типов плиток
	F.open("rectangle_type.txt", std::ios::in);

	field.resize(m);
	// Заполняем поле Field типами плиток
	for (int i = 0; i < m; i++)
	{
		field[i].resize(n);
		for (int j = 0; (j < n) && (!F.eof()); j++)
			F >> field[i][j];
	}
	F.close();
}

bool Field::check_passible_and_correct(int y, int x)		// Возвращает 1, если клетка ок
{
	return (y >= 0 && y < m && x >= 0 && x < n && field[y][x] != 2 && field[y][x] != 3) ? true : false;
}

// Если все норм., помещаем вершины в очередь и добавляем к ним путь.
void Field::add_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x)
{
	// Смотрим, чтобы добавляемые в очередь вершины были: проходимы, непросмотрены.
	if (check_passible_and_correct(new_y, new_x) && path[new_y][new_x] == -1)
	{
		q.push(std::pair<int, int>(new_y, new_x));		// Помещаем вершину в очередь.
		path[new_y][new_x] = path[old_y][old_x] + 1;	// [old_y][old_x] - откуда пришли.
	}
}

// Проходится по всем вмежным с (x, y) вершинам, кладет их в очередь и добавляет к ним путь.
void Field::add_all_adjacent_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int y, int x)
{
	add_vertex_in_queue_and_update_path(q, path, y + 1, x, y, x);		// Обходим все смежные с (x, y) вершины по часовой стрелке.
	add_vertex_in_queue_and_update_path(q, path, y, x + 1, y, x);
	add_vertex_in_queue_and_update_path(q, path, y - 1, x, y, x);
	add_vertex_in_queue_and_update_path(q, path, y, x - 1, y, x);
}



// Возвращает путь, если он существует (из (y1, x1) в (y2, x2)). Если не существует->пустой вектор.
// Путь от (y1, x1) к (y2, x2) возвращается в обратном порядке, т.е. от (y2, x2) к (y1, x1)
std::vector<std::pair<int, int>> Field::find_the_shortest_path(int y1, int x1, int y2, int x2)
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

		// Если мы встретили "конечную, требуемую" вершину. Путь найден. Вершина находится наверху стека.
		if (current_vertex.first == y2 && current_vertex.second == x2)
		{
			flag = 1;
			break;
		}
		q.pop();

		// Просматриваем все смежные с текущей вершиной вершины ( <= 4 ) и смотрим, чтобы они были: проходимы, непросмотрены.
		// Если все норм., помещаем вершины в очередь и добавляем к ним путь.
		add_all_adjacent_vertex_in_queue_and_update_path(q, path, current_vertex.first, current_vertex.second);
	}
	// К этому моменту путь найден.
	std::vector<std::pair<int, int>> shortest_path;
	if (flag == 1)		// Если путь есть, построим его по таблице путей.
	{
		int x = x2, y = y2;		// Координаты конца пути.
		int current = path[y][x];
		while (current != 0)
		{
			current = path[y][x];		// Сохраняем текушую длину пути.
			shortest_path.push_back(std::pair<int, int>(y, x));		// Записываем последнюю точку пути в вектор shortest_path
			// Ищем предыдущую точку пути. Точку, значение в которой == current - 1
			if ((y + 1 >= 0) && (y + 1 < m) && (path[y + 1][x] == current - 1))
			{
				
			}

		}
	}


/*	std::ofstream F("test.txt", std::ios::out);
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