#ifndef FIELD_H
#define FIELD_H


#include <vector>

class Field
{
public:
	Field();
	int get_m();			// ���-�� ������ � ������ (���-�� �����)
	int get_n();			// ���-�� ������ � ����� (���-�� ��������)
	int get_value(int y, int x);
	bool passable(int y, int x);	//�������, ������������, ��������� �� ������. ���� ���������, ������������ true
	bool find_the_shortest_path(int y1, int x1, int y2, int x2);		// ���������� true, ���� ���������� ���� �� (x1,y1), (x2,y2).
private:
	std::vector<std::vector<int>> field;	//������, ���������� ���� ������ ����.
	int m;		// ���-�� �����
	int n;		// ���-�� ��������
};

#endif /* FIELD_H */