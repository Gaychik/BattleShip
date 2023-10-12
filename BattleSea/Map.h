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
    Map() {};
    Map(bool hide)
    {
        is_hide = hide;
            for (auto s : rows)
            {
                for (size_t i = 1; i < 11; i++)
                {
                    field[{s, i}] = '*';
                }
            }
    }
private:
    bool is_hide;
    string rows = "ABCDEFGHIJ";
    bool is_exist_ship(Ship ship)
    {
        for (auto p : ship.position)
        {
            if (field[p.first] != '*')return false;
        }
        return true;
    }
    bool check_position_ship(Ship ship)
    {  //Проверка общей строки и общего столбца
        auto first_pair = ship.position.begin();
        auto check_row = first_pair->first.first;//название строки
        auto check_column= first_pair->first.second;//название столбца
        if (ship.position.size() == 1) return true;
        for (auto p : ship.position)
        {
            if (check_column != p.first.second)
            {
                check_column = 0;
            }
            if (check_row != p.first.first)
            {
                check_row = '0';
            }
        }
        //Если название колонок разное и название строки одно и тоже
       //получили номер колонки первой точки
        if (check_column==0 and check_row!='0')
        {
            auto n = first_pair->first.second;
            for (auto p : ship.position)
            {
                if (p == *first_pair)continue;
                if (abs(n - p.first.second) != 1)//находим разность между номерами двух колонок
                    return false;
                n = p.first.second;//сохраняю следующий номер колонки
            }
            return true;
        }
           //Если колонка общая и название строк разное
          //получаю название строки первой точки
        else if (check_column !=0 and check_row == '0')
        {
            auto n = first_pair->first.first;
            for (auto p : ship.position)
            {
                if (p == *first_pair)continue;
                if (abs(n - p.first.first) != 1)//находим разность между строками, например, A-B=65-66=-1
                    return false;
                n = p.first.first;//сохраняю следующие название строки
            }
            return true;
        }
        
        return false;
         

    } 
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
    bool add_ship(Ship ship)
    {
        if (ship.position.size() == 0)
            return false;
      
        //Если точки корабля расположены рядом,не по диагонали и корабль  можно поставить на карту
        if (check_position_ship(ship) and is_exist_ship(ship))
        {
            if (is_hide == true)
            {
                for (auto p : ship.position)
                {
                    field[p.first] = p.second;
                }
            }
            return true;
        }  
        return false;
    }
  
    map<pair<char,int>,char> field;

};