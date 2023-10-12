#pragma once
#include "Map.h"
#include "Player.h"
#include "Computer.h"


struct Game
{
	Game()
	{
		generate_ships_player();
		generate_ships_computer();
		while (true)
		{

			battle_player();
			battle_comp();
		}
	}
	void update_state_game()
	{
		system("cls");
		map_player.show();
		map_computer.show();
	}
	void battle_player()
	{
		bool win = 1;
		while (win)
		{
			bool is_equal = 0;
			string coord;
			cout << "Введите точку по которой будете наносить удар: " << endl;
			cin >> coord;
			pair<char, int> target_point = { coord[0], coord.length() < 3 ? coord[1] - 48 : 10 };
			for (auto s : computer.ships)
			{
				if (s.position.count(target_point) > 0)
				{
					map_computer.field[target_point] = '0';
					is_equal = 1;
					update_state_game();
					cout << "Попадание!" << endl;
					break;
				}
			}
			if (is_equal == 0)
			{
				cout << "Промах!"<<endl;
				win = 0;
				//тупик
			}
		}
	}
	void battle_comp()
	{
		bool win = 1;
		while (win)
		{
			bool is_equal = 0;
			pair<char, int> target_point = { rand() % 10 + 65, rand() % 10 + 1 };
				
			for (auto s : player.ships)
			{
				if (s.position.count(target_point) > 0)
				{
					map_player.field[target_point] = '0';
					is_equal = 1;
					break;
				}
			}
			if (is_equal == 0)
			{
				win = 0;
			}
		}
		update_state_game();
		cout << "Ход компьютера завершен!" << endl;
    }



    private:
	Map map_computer,map_player;
	Computer computer;
	Player player;
	void generate_ships_computer()
	{//Передаем флаг, который влияет на отображение карты, 
		//если false - карта скрыта
		map_computer = Map(false);
		computer = Computer('0');
		for (size_t i = 0; i < 5; i++)
		{
			int size = 2;
			computer.create_Ship(&map_computer, size);
		}
		map_computer.show();
	}
	void generate_ships_player()
	{
		map_player = Map(true);
		char v;
		cout << "Как будут отображаться ваши корабли?" << endl;
		cin >> v;
		player = Player(v);
		int count_ship;
		cout << "Сколько кораблей вы хотите поставить на карту?" << endl;
		cin >> count_ship;
		for (size_t i = 0; i < count_ship; i++)
		{
			int size = 0;
			do {
				cout << "Введите размер корабля:" << endl;
				cin >> size;
				if (size > 0 and size < 5)
				{
					break;
				}
				cout << "Некорректный размер корабля. Повторите ввод!" << endl;
				//чтение данных из входного потка закончилось ошибкой, символы не прочитались, нуджно вручную их оттуда удалить
				cin.clear();
				//удаляем символы
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (true);

			player.create_Ship(&map_player, size);
		}
		system("cls");
		map_player.show();
	}


};