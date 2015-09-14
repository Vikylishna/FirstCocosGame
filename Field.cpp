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
void Field::add_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int new_y, int new_x, int old_y, int old_x)
{
	// �������, ����� ����������� � ������� ������� ����: ���������, �������������.
	if (check_passible_and_correct(new_y, new_x) && path[new_y][new_x] == -1)
	{
		q.push(std::pair<int, int>(new_y, new_x));		// �������� ������� � �������.
		path[new_y][new_x] = path[old_y][old_x] + 1;	// [old_y][old_x] - ������ ������.
	}
}

// ���������� �� ���� ������� � (x, y) ��������, ������ �� � ������� � ��������� � ��� ����.
void Field::add_all_adjacent_vertex_in_queue_and_update_path(std::queue<std::pair<int, int>> & q, std::vector< std::vector<int>> & path, int y, int x)
{
	add_vertex_in_queue_and_update_path(q, path, y + 1, x, y, x);		// ������� ��� ������� � (x, y) ������� �� ������� �������.
	add_vertex_in_queue_and_update_path(q, path, y, x + 1, y, x);
	add_vertex_in_queue_and_update_path(q, path, y - 1, x, y, x);
	add_vertex_in_queue_and_update_path(q, path, y, x - 1, y, x);
}



// ���������� ����, ���� �� ���������� (�� (y1, x1) � (y2, x2)). ���� �� ����������->������ ������.
// ���� �� (y1, x1) � (y2, x2) ������������ � �������� �������, �.�. �� (y2, x2) � (y1, x1)
std::vector<std::pair<int, int>> Field::find_the_shortest_path(int y1, int x1, int y2, int x2)
{
	// ������ �����. ������ ������ �������� ����� ����. ���� (�������� � ���� ������ == -1) -> ��� ������ ��� �� ��������.
	std::vector<std::vector<int>> path(m);
	for (std::vector < std::vector<int>>::size_type i = 0; i < m; i++)		// ������ ��� ������ �����������
		path[i].resize(n, -1);
	
	// �������, ���������� ���� � ������������ (y, x).
	std::queue<std::pair<int, int>> q;
	q.push(std::pair<int, int>(y1, x1));	// ��������� ��������� ����� � �������.
	path[y1][x1] = 0;		// ���������� �� ��������� ������� == 0.

	bool flag = 0;		// ���� ��������, ����� �� ������ ������� ��� ���. 0 - ���.

	while (q.size() > 0)		// ���� �� ����������� ��� ��������� �������.
	{
		std::pair<int, int> current_vertex = q.front();		// ��������� �� ������� ������� (������� �������)

		// ���� �� ��������� "��������, ���������" �������. ���� ������. ������� ��������� ������� �����.
		if (current_vertex.first == y2 && current_vertex.second == x2)
		{
			flag = 1;
			break;
		}
		q.pop();

		// ������������� ��� ������� � ������� �������� ������� ( <= 4 ) � �������, ����� ��� ����: ���������, �������������.
		// ���� ��� ����., �������� ������� � ������� � ��������� � ��� ����.
		add_all_adjacent_vertex_in_queue_and_update_path(q, path, current_vertex.first, current_vertex.second);
	}
	// � ����� ������� ���� ������.
	std::vector<std::pair<int, int>> shortest_path;
	if (flag == 1)		// ���� ���� ����, �������� ��� �� ������� �����.
	{
		int x = x2, y = y2;		// ���������� ����� ����.
		int current = path[y][x];
		while (current != 0)
		{
			current = path[y][x];		// ��������� ������� ����� ����.
			shortest_path.push_back(std::pair<int, int>(y, x));		// ���������� ��������� ����� ���� � ������ shortest_path
			// ���� ���������� ����� ����. �����, �������� � ������� == current - 1
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