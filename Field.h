#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <queue>

class Field
{
public:
	Field();
	int get_m();			// Кол-во плиток в высоту (кол-во строк)
	int get_n();			// Кол-во плиток в длину (кол-во столбцов)
	int get_value(int y, int x);
	bool check_passible_and_correct(int y1, int x1);		// Проверяет клетку на проходимость и на то, что методу передали годные координаты. Возвращает 1, если все ок.

	// Возвращает путь, если он существует (из (x1,y1), (x2,y2)).  Если не существует->пустой вектор.
	std::vector<std::pair<int, int>> find_the_shortest_path(int y1, int x1, int y2, int x2);
private:
	int m;		// Кол-во строк
	int n;		// Кол-во столбцов
	std::vector<std::vector<int>> field;	//Вектор, содержащий типы плиток поля.
	void add_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector < std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x);
	void add_all_adjacent_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector < std::vector<int>> & path, int y, int x);
};

#endif /* FIELD_H */