#include <vector>

class Field
{
public:
	Field();
	int get_m();
	int get_n();
	int get_value(int i, int j);
private:
	std::vector<std::vector<int>> field;	//Вектор, содержащий типы плиток поля.
	int m;		// Кол-во строк
	int n;		// Кол-во столбцов
};