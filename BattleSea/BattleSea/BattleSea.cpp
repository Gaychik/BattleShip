#include "Map.h"
#include "Player.h"
#include "Computer.h"

int main()
{
	setlocale(LC_ALL, "");
	auto map_player = Map();
	auto map_computer = Map();
	auto computer = Computer('0');
	char v;
	cout << "Как будут отображаться ваши корабли?" << endl;
	cin >> v;
	auto player = Player(v);
	int count_ship;
	cout << "Сколько кораблей вы хотите поставить на карту?" << endl;
	cin >> count_ship;
	for (size_t i = 0; i < count_ship; i++)
	{
		int size=0;
		do {
			cout << "Введите размер корабля:" << endl;
			cin >>size;
			if (size>0 and size <5)
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

	for (size_t i = 0; i <5; i++)
	{
		int size=3;
		computer.create_Ship(&map_computer, size);
	}
	map_computer.show();

}
