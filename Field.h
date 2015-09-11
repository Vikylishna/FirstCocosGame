#ifndef FIELD_H
#define FIELD_H


#include <vector>

class Field
{
public:
	Field();
	int get_m();			// Кол-во плиток в высоту (кол-во строк)
	int get_n();			// Кол-во плиток в длину (кол-во столбцов)
	int get_value(int y, int x);
	bool passable(int y, int x);	//функция, определяющая, проходима ли плитка. Если проходима, возвращается true
	bool find_the_shortest_path(int y1, int x1, int y2, int x2);		// Возвращает true, если существует путь из (x1,y1), (x2,y2).
private:
	std::vector<std::vector<int>> field;	//Вектор, содержащий типы плиток поля.
	int m;		// Кол-во строк
	int n;		// Кол-во столбцов
};

#endif /* FIELD_H */