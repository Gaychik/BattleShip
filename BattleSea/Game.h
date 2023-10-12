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
		cout << "��������..." << endl;
		generate_ships_computer();
		update_state_game();
		while (is_end_game())
		{
			battle_player();
			battle_comp();
		}
		if (score_computer>score_player)
			cout << "������� ���������!!!" << endl;
		else
			cout << "������� �����!!!" << endl;

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
			cout << "������� ����� �� ������� ������ �������� ����: " << endl;
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
					cout << "���������!" << endl;
					//�������� ������� �� ������ �����������
					if (check_destroyed_ship(s.position, '1'))
					{
						//���� ������� ���������, �� ��� ���� ��������� ������
						score_player += 1;
						cout << "������� ���������� ��������� ���������!" << endl;
					}
					break;
				}
			}
			if (is_equal == 0)
			{
				map_computer.field[target_point] = 'x';
				cout << "������!"<<endl;
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
						//���� ������� ���������, �� ��� ���� ��������� ����������
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
		cout << "��� ���������� ��������!" << endl;
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
		//�������� ����, ������� ������ �� ����������� �����, 
		//���� false - ����� ������
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
		cout << "��� ����� ������������ ���� �������?" << endl;
		cin >> v;
		player = Player(v);
		int count_ship;
		cout << "������� �������� �� ������ ��������� �� �����?" << endl;
		cin >> count_ship;
		for (size_t i = 0; i < count_ship; i++)
		{
			int size = 0;
			do {
				cout << "������� ������ �������:" << endl;
				cin >> size;
				if (size > 0 and size < 5)
				{
					break;
				}
				cout << "������������ ������ �������. ��������� ����!" << endl;
				//������ ������ �� �������� ����� ����������� �������, ������� �� �����������, ������ ������� �� ������ �������
				cin.clear();
				//������� �������
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (true);

			player.create_Ship(&map_player, size);
		}
		system("cls");
	}


};