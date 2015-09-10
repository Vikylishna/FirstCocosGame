#include "Field.h"
#include <fstream>

int Field::get_m()
{
	return m;
}

int Field::get_n()
{
	return n;
} 

int Field::get_value(int i, int j)
{
	return field[i][j];
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