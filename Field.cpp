#include "Field.h"
#include <fstream>

int Field::get_m()		// ���-�� ������ � ������ (���-�� �����)
{
	return m;
}

int Field::get_n()		// ���-�� ������ � ����� (���-�� ��������)
{
	return n;
} 

int Field::get_value(int y, int x)
{
	return field[y][x];
}

bool Field::passable(int y, int x){
	return (field[y][x] == 0 || field[y][x] == 1) ? true : false;
}

Field::Field()
{
	std::ifstream F1;		// ����� ��� ���������� �� ����� ������� ����
	F1.open("size_field.txt", std::ios::in);
	F1 >> m;
	F1 >> n;
	F1.close();

	std::ifstream F;		// ����� ��� ���������� �� ����� ����� ������
	F.open("rectangle_type.txt", std::ios::in);

	field.resize(m);
	// ��������� ���� Field ������ ������
	for (int i = 0; i < m; i++)
	{
		field[i].resize(n);
		for (int j = 0; (j < n) && (!F.eof()); j++)
			F >> field[i][j];
	}
	F.close();
}

bool find_the_shortest_path(int y1, int x1, int y2, int x2){		// ���������� true, ���� ���������� ���� �� (x1,y1), (x2,y2).
	return true;
}