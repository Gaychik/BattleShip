#pragma once
#include "Map.h"
#include "Ship.h"
#include <stdlib.h>
#include <string>
#include "time.h"


struct Computer
{
	Computer() {};
	
	Computer(char _status) :status{ _status }
	{
	}
private :

	

public:
	vector<pair<char, int>> buffer_points;
	void create_Ship(Map* m, int size_ship)
	{
		
		Ship ship;
		//≈сли корабль невозможно добавить, то мы по новой запускаем функцию создани€ корабл€
		while(m->add_ship(ship,ships) == false)
		{
			srand(time(NULL));
			vector<pair<char, int>> data;
			pair<char,int> random_point = { rand() % 10 + 65, rand() % 10 + 1 };
			data.push_back(random_point);
			auto random_path = rand() % 2;//случайно выбираетс€ направление формировани€ корабл€
			switch (random_path)
			{
			case 0://‘иксируем название строки
				for (size_t i = 1; i < size_ship; i++) 
				{
					data.push_back({ random_point.first,random_point.second+i});
				}
				break;
			case 1://‘иксируем номер колонки
				for (size_t i = 1; i < size_ship; i++)
				{
					data.push_back({ random_point.first+i,random_point.second });
				}
				break;
			default:
				break;
			}	
			
		    ship = Ship(status, data);
		}
		ships.push_back(ship);
	}
	vector<Ship> ships;
	char status;

};