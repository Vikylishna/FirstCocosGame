#include "cocos2d.h"
//#include <vector>

class Field
{
public:
	Field();
	int get_m();
	int get_n();
	int get_value(int i, int j);
private:
	std::vector<std::vector<int>> field;	//������, ���������� ���� ������ ����.
	int m;		// ���-�� �����
	int n;		// ���-�� ��������
};

//#endif // __HELLOWORLD_SCENE_H__
