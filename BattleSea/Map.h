#pragma once
#include <map>
#include <iostream>
#include "Ship.h"
//struct Cell
//{
//    Cell() {}
//    Cell(char _status, char _row, char _column) :status{ _status }, row{ _row }, column{_column}
//    {
//    }
//public:
//    char status;
//    char row;
//    char column;
//};
using namespace std;
struct Map 
{
    Map()
    {
            for (auto s : rows)
            {
                for (size_t i = 1; i < 11; i++)
                {
                    field[{s, i}] = '*';
                }
            }
    }
private:
    string rows = "ABCDEFGHIJ";
    void check_position_ship()
    {}
public:  

    void show()
    {    

        cout << "  ";
        for (size_t i = 1; i < 11; i++)
            cout <<i<<" ";
        cout << endl;
        for (auto s : rows)
        {
            cout << s<<" ";
            for (size_t i = 1; i < 11; i++)
            {
                cout << field[{s, i}] << " ";
            }
            cout << endl;
        }
    }
    void add_ship(Ship ship)
    {
        for (auto p: ship.position)
        {
            field[p.first] = p.second;
        }
    }
  
    map<pair<char,int>,char> field;

};