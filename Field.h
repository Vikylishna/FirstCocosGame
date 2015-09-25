#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <queue>
#include <string>

/* Есть в ресурсах 3 файла, необходимых для этого класса:
filenamePassable.txt содержит:
    имя файла, откуда можно взять картинку для плитки,
	проходимость (проходима клетка с этим типом или нет).
field.txt содержит:
	размеры поля m x n. 1-е число m (кол-во строк в поле), 2-е число n (кол-во столбцов в поле)
	за размерами поля идет само поле.
*/

class Field
{
public:
	Field();
	void createField();		// Создает поле: загружает его из файла, формирует из файла массивы typetilePassable и typetileFilename.

	int getRowNums();				// Кол-во плиток в высоту (кол-во строк). m
	int getColumnNums();			// Кол-во плиток в длину (кол-во столбцов). n
	int getValue(int y, int x);		// Возвращает значение field[y][x]

	int getTypetilePassable(int i);	// Возвращает значение typetilePassable[i].
	std::string getTypetileFilename(int i);	// Возвращает значение typetileFilename[i].

	bool checkPassible(int y, int x);	// Проверяет клетку на проходимость.
	bool checkCorrect(int y, int x);		// Проверяет клетку на то, что она имеет годные координаты.
	bool checkCorrectAndPassible(int y1, int x1);		// Проверяет клетку на проходимость и на то, что методу передали годные координаты. Возвращает 1, если все ок.
	
	// Возвращает путь, если он существует (из (x1,y1), (x2,y2)).  Если не существует->пустой вектор.
	std::vector<std::pair<int, int>> findTheShortestPath(int y1, int x1, int y2, int x2);
private:
	std::vector<int> typetilePassable;		// Тип плитки, проходимость (0, 1). По типу получаем проходимость
	std::vector<std::string> typetileFilename;			// Тип плитки и имя файла, сожержащего соответствующую картинку. По типу получаем имя файла.
	int m;		// Кол-во строк.
	int n;		// Кол-во столбцов.
	std::vector<std::vector<int>> field;	// Вектор, содержащий типы плиток поля (typeTile).
	
	bool readString(const char* & fileContentsBegin, char * str);		// Считывает строку до пробела из строки, двигает указатель за считанную строку.
	bool readNumber(const char* & fileContentsBegin, int & num);		// Считывает число из строки, двигает указатель за это число.
	void readFilenamePassable();			// Считывает из файла "filenamePassable.txt" имя файла, откуда берется картинка и проходимость.
	void fillFieldMN();		// Заполняет поле: считывает размерность поля из файла "field.txt" в переменные m и n и типы плиток (проходимость) в вектор field.

	void addVertexInQueue(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int new_y, int new_x);
	void updatePath(std::vector< std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x);
	void addVertexInQueueAndUpdatePath(std::queue<std::pair<int, int>> & q, std::vector < std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x);
	void goToAllAdjacentVertices(std::queue<std::pair<int, int>> & q, std::vector < std::vector<int>> & path, int y, int x);
};

#endif /* FIELD_H */