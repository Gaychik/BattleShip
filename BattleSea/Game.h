#pragma once
#include "Map.h"
#include "Player.h"
#include "Computer.h"
#include <chrono>
#include <thread>
struct Game
{
	Game()
	{
		generate_ships_player();
		cout << "Загрузка..." << endl;
		generate_ships_computer();
		update_state_game();
		while (is_end_game())
		{
			battle_player();
			battle_comp();
		}
		if (score_computer>score_player)
			cout << "Победил компьютер!!!" << endl;
		else
			cout << "Победил игрок!!!" << endl;

	}
	void update_state_game()
	{
		system("cls");
		cout << "Player: " << score_player << "    Computer: " << score_computer << endl;
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
			for (auto &s : computer.ships)
			{
				if (s.position.count(target_point) > 0)
				{
					s.position[target_point] = '1';
					map_computer.field[target_point] = '1';
					is_equal = 1;
					update_state_game();
					cout << "Попадание!" << endl;
					//Проверка корабля на полное уничтожение
					if (check_destroyed_ship(s.position, '1'))
					{
						//Если корабль уничтожен, то доп очко достается игроку
						score_player += 1;
						cout << "Корабль противника полностью уничтожен!" << endl;
					}
					break;
				}
			}
			if (is_equal == 0)
			{
				map_computer.field[target_point] = 'x';
				cout << "Промах!"<<endl;
				win = 0;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
			update_state_game();
		}
	}

	void battle_comp()
	{
		bool win = 1;
		while (win)
		{
			bool is_equal = 0;
			pair<char, int> target_point;
			do
			{
				target_point = { rand() % 10 + 65, rand() % 10 + 1 };
			} while (count(computer.buffer_points.begin(), computer.buffer_points.end(), target_point) > 0);
            
			computer.buffer_points.push_back(target_point);
				
			for (auto &s : player.ships)
			{
				if (s.position.count(target_point) > 0)
				{
					s.position[target_point] = '0';
					map_player.field[target_point] = '0';
					if (check_destroyed_ship(s.position, '0'))
						//Если корабль уничтожен, то доп очко достается компьютеру
						score_computer += 1;
					is_equal = 1;
					break;
				}
			}
			if (is_equal == 0)
			{
				map_player.field[target_point] = 'x';
				win = 0;
			}
		}
		update_state_game();
		cout << "Ход компьютера завершен!" << endl;
    }
    private:
	int score_player, score_computer;
	Map map_computer,map_player;
	Computer computer;
	Player player;
	bool is_end_game()
	{
		return score_player == size(computer.ships) or score_computer == size(player.ships);
	}
	bool check_destroyed_ship(map<pair<char,int>,char> points_ship,char view)
	{
		for (auto p: points_ship)
		{
			if (p.second != view) return false;
		}
		return true;
	}
	void generate_ships_computer()
	{
		//Передаем флаг, который влияет на отображение карты, 
		//если false - карта скрыта
		map_computer = Map(true);
		computer = Computer('0');
		int size = 4;
		for (size_t i = 1; i < 5; i++)
		{
			for (size_t j = 0; j < i; j++)
			{
				computer.create_Ship(&map_computer, size);
			}
			size -= 1;
		}
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
	}


};