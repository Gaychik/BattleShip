#pragma once
#include <map>
#include <vector>

using namespace std;
struct Ship
{

	Ship(char _view, vector<pair<char, int>> _coords) :view{_view}
	{
		for (auto p : _coords)
		{
			position[p] = _view;
		}
	}
private:
	char view;
public:
	map<pair<char, int>, char> position;
};