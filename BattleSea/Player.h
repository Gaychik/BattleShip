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
		cout << "Добавьте корабль" << endl;
		for (size_t i = 0; i < size_ship; i++)
		{
			cin >> coord;
			data.push_back({ coord[0],coord.length() < 3 ? coord[1]-48: 10 });
		}
		auto ship=Ship(status, data);
		ships.push_back(ship);
		m->add_ship(ship);
		system("cls");
		m->show();
		cout << "Корабль успешно добавлен" << endl;
	}
	vector<Ship> ships;
	char status;

};