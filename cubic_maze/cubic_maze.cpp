#include <iostream>
#include <conio.h>
using namespace std;

enum Move { LEFT = 97, RIGHT = 100, UP = 119, DOWN = 115, TP_UP = 113, TP_DOWN = 101 };

int main()
{
    Move player;

    //Пример матрицы с лабиринтом
    int matr[11][11] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                         1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                         1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1,
                         1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
                         1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1,
                         1, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1,
                         1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                         1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1,
                         1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1,
                         1, 0, 0, 0, 1, 0, 0, 0, 1, 3, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }; 

    int x = 9, y = 9;   //правый нижний угол на цифре 3

    while (_kbhit)
    {
        player = (Move)_getch();            //Считывание нажатой клавиши

        if (player < 90)                    //Если введена заглавная буква, её регистр меняется на прописную
            player = Move(player + 32);

//        cout << player;

        switch (player)
        {
            case LEFT:
            {
                if (matr[y][x - 1] != 1)
                    x--;

                break;
            }
            case RIGHT:
            {
                if (matr[y][x + 1] != 1)
                    x++;

                break;
            }
            case UP:
            {
                if (matr[y - 1][x] != 1)
                    y--;

                break;
            }
            case DOWN:
            {
                if (matr[y + 1][x] != 1)
                    y++;

                break;
            }
            case TP_UP:
            {
//                if (matr[z][y][x] == 2)
                    //z++;

                break;
            }
            case TP_DOWN:
            {
//                if (matr[z][y][x] == 3)
                    //z--;

                break;
            }
        }

        cout << "x = " << x << " y = " << y << endl;
    }
}