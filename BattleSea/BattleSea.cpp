#include "Map.h"
#include "Player.h"

int main()
{
	setlocale(LC_ALL, "");
	auto map = Map();
	map.show();
	char v;
	cout << "Как будут отображаться ваши корабли?" << endl;
	cin >> v;
	auto player = Player(v);
	int count_ship;
	cout << "Сколько кораблей вы хотите поставить на карту?" << endl;
	cin >> count_ship;
	for (size_t i = 0; i < count_ship; i++)
	{
		cout << "Введите размер корабля:" << endl;
		int size;
		cin >> size;
		player.create_Ship(&map, size);
	}
	system("cls");
	map.show();

}
