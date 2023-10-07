#pragma once
#include "Map.h"
#include "Ship.h"
#include <stdlib.h>
#include <string>

struct Player
{
	Player(char _status):status{_status}
	{
	}
public:
	void create_Ship(Map* m,int size_ship)
	{
		vector<pair<char, int>> data;
		string coord;
		cout << "�������� �������" << endl;
		for (size_t i = 0; i < size_ship; i++)
		{
			cin >> coord;
			data.push_back({ coord[0],coord.length() < 3 ? coord[1]-48: 10 });
		}
		auto ship=Ship(status, data);
      //���� ������� ���������� ��������, �� �� �� ����� ��������� ������� �������� �������
		if (m->add_ship(ship) == false)
		{
			cout << "������ ��� ���������� �������, ��������� �������!" << endl;
			create_Ship(m, size_ship);
		}
		else
		{
			ships.push_back(ship);
			system("cls");
			m->show();
			cout << "������� ������� ��������" << endl;
		}
	}
	vector<Ship> ships;
	char status;

};