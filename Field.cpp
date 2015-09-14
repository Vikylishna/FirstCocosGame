#include "Field.h"
#include <fstream>
#include <queue>

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

bool Field::check_passible_and_correct(int y, int x)		// ���������� 1, ���� ������ ��
{
	return (y >= 0 && y < m && x >= 0 && x < n && field[y][x] != 2 && field[y][x] != 3) ? true : false;
}

// ���� ��� ����., �������� ������� � ������� � ��������� � ��� ����.
void Field::add_vertex_in_queue_and_update_ways(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & ways, int new_y, int new_x, int old_y, int old_x)
{
	// �������, ����� ����������� � ������� ������� ����: ���������, �������������.
	if (check_passible_and_correct(new_y, new_x) && ways[new_y][new_x] == -1)
	{
		q.push(std::pair<int, int>(new_y, new_x));		// �������� ������� � �������.
		//q.emplace(std::pair<int, int>(new_y, new_x));
		ways[new_y][new_x] = ways[old_y][old_y] + 1;	// [old_y][old_x] - ������ ������.
	}
}

// ���������� �� ���� ������� � (x, y) ��������, ������ �� � ������� � ��������� � ��� ����.
void Field::add_all_adjacent_vertex_in_queue_and_update_ways(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & ways, int y, int x)
{
	add_vertex_in_queue_and_update_ways(q, ways, y + 1, x, y, x);		// ������� ��� ������� � (x, y) ������� �� ������� �������.
	add_vertex_in_queue_and_update_ways(q, ways, y, x + 1, y, x);
	add_vertex_in_queue_and_update_ways(q, ways, y - 1, x, y, x);
	add_vertex_in_queue_and_update_ways(q, ways, y, x - 1, y, x);
}



// ���������� ����, ���� �� ���������� (�� (x1,y1), (x2,y2)). ���� �� ����������->������ ������.
std::vector<std::pair<int, int>> Field::find_the_shortest_path(int y1, int x1, int y2, int x2)
{
	// ������ �����. ������ ������ �������� ����� ����. ���� (�������� � ���� ������ == -1) -> ��� ������ ��� �� ��������.
	std::vector<std::vector<int>> ways(m);
	for (std::vector < std::vector<int>>::size_type i = 0; i < m; i++)		// ������ ��� ������ �����������
		ways[i].resize(n, -1);
	
	// �������, ���������� ���� � ������������ (y, x).
	std::queue<std::pair<int, int>> q;
	q.push(std::pair<int, int>(y1, x1));	// ��������� ��������� ����� � �������.
	//q.emplace(std::pair<int, int>(y1, x1));
	ways[y1][x1] = 0;		// ���������� �� ��������� ������� == 0.

	bool flag = 0;		// ���� ��������, ����� �� ������ ������� ��� ���. 0 - ���.

	while (q.size() > 0)		// ���� �� ����������� ��� �������.
	{
		std::pair<int, int> current_vertex = q.front();		// ��������� �� ������� ������� (������� �������)

		// ���� �� ��������� "��������" �������. ���� ������. ������� ��������� ������� �����.
		if (current_vertex.first == y2 && current_vertex.second == x2)
		{
			flag = 1;
			break;
		}
		q.pop();

		// ������������� ��� ������� � ������� �������� ������� ( <= 4 ) � �������, ����� ��� ����: ���������, �������������.
		// ���� ��� ����., �������� ������� � ������� � ��������� � ��� ����.
		add_all_adjacent_vertex_in_queue_and_update_ways(q, ways, current_vertex.first, current_vertex.second);
	}

	std::ofstream F("test.txt", std::ios::out);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			F << ways[i][j] << " ";
		}
		F << '\n';
	}
	F.close();

	return std::vector<std::pair<int, int>>();
}