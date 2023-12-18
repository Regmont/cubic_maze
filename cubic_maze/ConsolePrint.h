#pragma once

void Print_Custom_Dif(int size, int lvls, char elem_1, char elem_2)
{
	//Функция выводит настройку сложности

	cout << endl << endl << "\tadjust  difficulty" << endl << endl;

	//строка 1
	cout << "        " << char(201);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "        " << char(186) << "   level size   " << char(186) << endl;

	//строка 3
	cout << "       " << elem_1 << char(186);
	for (int i = 0; i < 16; i++)
		cout << ' ';
	cout << char(186) << endl;

	//строка 4
	cout << "        " << char(186) << "<-     " << size;
	if (size < 10)
		cout << ' ';
	cout << "     ->" << char(186) << endl;

	//строка 5
	cout << "        " << char(200);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(188) << endl;

	//строка 6
	cout << "        " << char(201);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 7
	cout << "        " << char(186) << "amount of levels" << char(186) << endl;

	//строка 8
	cout << "       " << elem_2 << char(186);
	for (int i = 0; i < 16; i++)
		cout << ' ';
	cout << char(186) << endl;

	//строка 9
	cout << "        " << char(186) << "<-     " << lvls;
	if (lvls != 10)
		cout << ' ';
	cout << "     ->" << char(186) << endl;

	//строка 10
	cout << "        " << char(200);
	for (int i = 0; i < 16; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << endl << endl;
	cout << "    use W, S and A, D to switch";
}

void Print_Diffs(char elem_1, char elem_2, char elem_3, char elem_4)
{
	//Функция выводит экран сложностей

	cout << endl << endl << "\tselect difficulty" << endl << endl;

	//строка 1
	cout << "  " << char(201);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "  " << char(186) << "easy" << char(186) << char(186) << "normal" << char(186);
	cout << char(186) << "hard" << char(186) << char(186) << "custom" << char(186) << endl;

	//строка 3
	cout << "  " << char(200);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 4; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 6; i++)
		cout << char(205);
	cout << char(188) << endl;

	//Отображение выбранного элемента
	cout << "  ";
	for (int i = 0; i < 6; i++)
		cout << elem_1;
	for (int i = 0; i < 8; i++)
		cout << elem_2;
	for (int i = 0; i < 6; i++)
		cout << elem_3;
	for (int i = 0; i < 8; i++)
		cout << elem_4;

	cout << endl << endl;
	cout << "       use A, D to switch";
}

void Print_Wall(int** matr, int lvlSize, int x, int y)
{
	//Функция выводит нужную стену

	int max_el = lvlSize - 1;	//Самый дальний элемент от начала

	//Является ли внешней стеной
	if (x == 0 || y == 0 || x == max_el || y == max_el)
	{
		if (x == 0 && y == 0)
			cout << char(201);								//угол право-низ
		else if (x == 0 && y == max_el)
			cout << char(200);								//право-верх
		else if (x == max_el && y == 0)
			cout << char(187);								//угол лево-низ
		else if (x == max_el && y == max_el)
			cout << char(188);								//угол лево-верх
		else if (y == 0)
			matr[y + 1][x] != 1 ? cout << char(205) : cout << char(203);	// " = " или тройник лево-право-низ
		else if (y == max_el)
			matr[y - 1][x] != 1 ? cout << char(205) : cout << char(202);	// " = " или тройник лево-право-верх
		else if (x == 0)
			matr[y][x + 1] != 1 ? cout << char(186) : cout << char(204);	// " || " или тройник право-верх-низ
		else
			matr[y][x - 1] != 1 ? cout << char(186) : cout << char(185);	// " || " или тройник лево-верх-низ
	}
	else
	{
		int L = matr[y][x - 1];
		int R = matr[y][x + 1];
		int U = matr[y - 1][x];
		int D = matr[y + 1][x];

		if (L == 1 && R == 1 && U == 1 && D == 1)
			cout << char(206);									//крест
		else if (R == 1 && U != 1 && D == 1)
			L != 1 ? cout << char(201) : cout << char(203);		//угол право-низ + тройник (лево)
		else if (L != 1 && R == 1 && U == 1)
			D != 1 ? cout << char(200) : cout << char(204);		//угол право-верх + тройник (низ)
		else if (L == 1 && R != 1 && D == 1)
			U != 1 ? cout << char(187) : cout << char(185);		//угол лево-низ + тройник (верх)
		else if (L == 1 && D != 1 && U == 1)
			R != 1 ? cout << char(188) : cout << char(202);		//угол лево-верх + тройник (право)
		else if (U != 1 && D != 1)
			cout << char(205);									// " = "
		else if (L != 1 && R != 1)
			cout << char(186);									// " || "
	}
}

void Print_Main_Screen(char elem_1, char elem_2)
{
	//Функция выводит главный экран
	cout << endl;
	cout << "    CUBIC  MAZE" << endl << endl;

	//строка 1
	cout << "    " << char(201);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "   " << elem_1 << char(186) << "  play  " << char(186) << endl;

	//строка 3
	cout << "    " << char(200);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(188) << endl;

	//строка 4
	cout << "    " << char(201);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 5
	cout << "   " << elem_2 << char(186) << "tutorial" << char(186) << endl;

	//строка 6
	cout << "    " << char(200);
	for (int i = 0; i < 8; i++)
		cout << char(205);
	cout << char(188) << endl;

	cout << endl;
	cout << "use W, S to switch";
}

void Print_End_Screen(char elem_1, char elem_2)
{
	//Функция выводит экран победы

	cout << endl << endl << "\t CONGRATULATIONS!" << endl;
	cout << " You've made it through the maze!" << endl << endl;

	//строка 1
	cout << "     " << char(201);
	for (int i = 0; i < 10; i++)
		cout << char(205);
	cout << char(187) << char(201);
	for (int i = 0; i < 9; i++)
		cout << char(205);
	cout << char(187) << endl;

	//строка 2
	cout << "     " << char(186) << "play again" << char(186) << char(186) << "quit game" << char(186) << endl;

	//строка 3
	cout << "     " << char(200);
	for (int i = 0; i < 10; i++)
		cout << char(205);
	cout << char(188) << char(200);
	for (int i = 0; i < 9; i++)
		cout << char(205);
	cout << char(188) << endl;

	//выбранный элемент
	cout << "     ";
	for (int i = 0; i < 12; i++)
		cout << elem_1;
	for (int i = 0; i < 11; i++)
		cout << elem_2;

	cout << endl << endl;
	cout << "       use A, D  to switch";
}

void Tutorial()
{
	//Функция выводит обучение

	int back = 0;

	cout << char(2) << " - you\n";
	cout << char(253) << " - portal to the next level\n";
	cout << char(15) << " - portal to the previous level\n";

	cout << endl;

	cout << "WASD - move\n";
	cout << "Q - using first portal " << char(253) << endl;
	cout << "E - using second portal " << char(15) << endl;
	cout << "P - exit the game while on the level\n";

	cout << endl << endl;

	cout << "press Enter to go back to main menu" << endl;

	while (_kbhit && back != 13)
	{
		back = _getch();
	}

	system("cls");
}

void Print_Player(int x, int y, int pl_coord, int cell, int lvlSize)
{
	//Функция выводит местоположение игрока

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };

	SetConsoleCursorPosition(h, c);	//Курсор помещается на координаты, где игрок
	cout << char(2);

	//Затирание места, где был ранее игрок
	switch (pl_coord)
	{
	case 1:
	{
		c.X++;
		break;
	}
	case 2:
	{
		c.X--;
		break;
	}
	case 3:
	{
		c.Y++;
		break;
	}
	case 4:
	{
		c.Y--;
		break;
	}
	}

	SetConsoleCursorPosition(h, c);

	//Проверка на наличие портала в месте, где был игрок
	if (cell < 2)
		cout << ' ';
	else if (cell == 2)
		cout << char(253);	//Телепорт вверх
	else
		cout << char(15);	//Телепорт вниз

	//Курсор перемещается для удобной игры
	c.X = lvlSize;
	if (y < lvlSize / 4)
		c.Y = lvlSize / 4;
	else if (y < lvlSize / 2)
		c.Y = lvlSize / 2;
	else if (y < lvlSize * 3 / 4)
		c.Y = lvlSize * 3 / 4;
	else
		c.Y = lvlSize;
	SetConsoleCursorPosition(h, c);
}