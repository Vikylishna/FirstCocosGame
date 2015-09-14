#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <queue>

class Field
{
public:
	Field();
	int get_m();			// ���-�� ������ � ������ (���-�� �����)
	int get_n();			// ���-�� ������ � ����� (���-�� ��������)
	int get_value(int y, int x);
	bool check_passible_and_correct(int y1, int x1);		// ��������� ������ �� ������������ � �� ��, ��� ������ �������� ������ ����������. ���������� 1, ���� ��� ��.

	// ���������� ����, ���� �� ���������� (�� (x1,y1), (x2,y2)).  ���� �� ����������->������ ������.
	std::vector<std::pair<int, int>> find_the_shortest_path(int y1, int x1, int y2, int x2);
private:
	int m;		// ���-�� �����
	int n;		// ���-�� ��������
	std::vector<std::vector<int>> field;	//������, ���������� ���� ������ ����.
	void add_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector < std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x);
	void add_all_adjacent_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector < std::vector<int>> & path, int y, int x);
};

#endif /* FIELD_H */