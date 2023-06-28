#pragma once
#ifndef __MAZE_GEN__
#define __MAZE_GEN__

#define __COUNT_OF_DIRECTIONS__ 4
#define __UP__ 0
#define __DOWN__ 1
#define __LEFT__ 2
#define __RIGHT__ 3

// ����� ����� � ��������, ������������ � �������
#define __ENTRY_NUM__ 3

// ����� ������ �� ���������, ������������ � �������
#define __EXIT_NUM__ 2

using namespace std;
#include <random>

struct Coordinates
{
	// ���������, ���������� �� ����������

	int x, y;
};

struct Cell
{
	// ���������, ���������� �� ������ � �������

	// ������, �������� ���������� � ������� ���� ����� ������
	// ������ (0 �������), ����� (1 �������), ����� (2 �������) � ������ (3 �������)
	bool walls[4];

	// ���� �� �������� ��� ������
	bool was_changed;
};

template <class T> void __add_el__(T*& arr, int& size, T el);
template <class T> void __delete_last_el__(T*& arr, int& size);

Cell** __init_cells__(int size);
Cell __check__(Cell** cells, int size, int x, int y, int direction);
void __randomize_cells__(Cell** cells, int size, int x, int y);
void __randomize_exit__(int** matrix, int size, int x, int y);

int** __convert_cells_to_matrix__(Cell** cells, int size);

int** generate_maze_matrix(int size, int x = 0, int y = 0, int z = 0)
{
	// ������� �������� ������� ��������� �������� size �� ��������� ����� (x; y). size, x � y - �������� �����. �������� ������� ������������ �� �������

	if (!x || !y)
	{
		x = 2 * (rand() % (size / 2 - 1) + 1) + 1;
		y = 2 * (rand() % (size / 2 - 1) + 1) + 1;
	}

	// �������������� ������� ������
	Cell** cells = __init_cells__(size / 2);

	// ������ ������ � ������
	__randomize_cells__(cells, size / 2, x / 2, y / 2);

	// ������������ ������� ������ � ������� int
	int** matrix = __convert_cells_to_matrix__(cells, size);

	// ������ ���� � ����� �� ���������
	if (z != 0)
		matrix[y][x] = __ENTRY_NUM__;

	__randomize_exit__(matrix, size, x, y);

	return matrix;
}

void __randomize_exit__(int** matrix, int size, int x, int y)
{
	/*
	������� ���������� �������� ������ �� ������� ��������� matrix �������� size �� ������������ ��� ����� (x; y)
	������� ������:
		������� ������� �� ������ �������� (�� ��������):
			1 | 2
		   --+--
			3 | 4

		� ����������� �� ������������ ����� ��� �������������� ��������.
		���� ���� ���������� �� ����� ���� ��� ���� ��������� ��� �������������� ��������� �� ���� ���� ��� ������ ��������� ��������������.
		�����, � ����������� �� �������� �����, �������� ������ ������������, ��� ����� ������� (1 -> 4, 2 -> 3, 3 -> 2, 4 -> 1). � ���� �������� �������� ���������� ����������, �� ������� � ������� ����� ����.
		�� ��������� ����������� �������� ����� __EXIT_NUM__
	*/

	// ��������, � ������� ���������� ���� (x; y)
	int quarter;

	// ������ �������� �����
	if (x < size / 2 && y < size / 2)
	{
		quarter = 1;
	}
	else if (x > size / 2 && y < size / 2)
	{
		quarter = 2;
	}
	else if (x < size / 2 && y > size / 2)
	{
		quarter = 3;
	}
	else if (x > size / 2 && y > size / 2)
	{
		quarter = 4;
	}
	else if (x < size / 2)
	{
		quarter = (rand() % 2) ? 2 : 4;
	}
	else if (x > size / 2)
	{
		quarter = (rand() % 2) ? 1 : 3;
	}
	else if (y < size / 2)
	{
		quarter = (rand() % 2) ? 3 : 4;
	}
	else if (y > size / 2)
	{
		quarter = (rand() % 2) ? 1 : 2;
	}
	else
	{
		quarter = rand() % 4 + 1;
	}

	// ���������� ������
	int exit_x, exit_y;

	// ������ ��������� ������ � ����������� �� �������� ����� (� �����, ���� �� ��������� ����������� ����� �� ����)
	do
	{
		switch (quarter)
		{
		case 1:
			exit_x = rand() % (size / 2 - 1) + size / 2 + 1; // �� size / 2 + 1 �� size - 2
			exit_y = rand() % (size / 2 - 1) + size / 2 + 1; // �� size / 2 + 1 �� size - 2

			break;

		case 2:
			exit_x = rand() % (size / 2 - 1) + 1;                 // �� 1 �� size / 2 - 1
			exit_y = rand() % (size / 2 - 1) + size / 2 + 1; // �� size / 2 + 1 �� size - 2

			break;

		case 3:
			exit_x = rand() % (size / 2 - 1) + size / 2 + 1; // �� size / 2 + 1 �� size - 2
			exit_y = rand() % (size / 2 - 1) + 1;                // �� 1 �� size / 2 - 1

			break;

		case 4:
			exit_x = rand() % (size / 2 - 1) + 1; // �� 1 �� size / 2 - 1
			exit_y = rand() % (size / 2 - 1) + 1; // �� 1 �� size / 2 - 1

			break;
		}
	} while (matrix[exit_y][exit_x]);

	// ������ �� ���������� ������ ����� __EXIT_NUM__
	matrix[exit_y][exit_x] = __EXIT_NUM__;
}

int** __convert_cells_to_matrix__(Cell** cells, int size)
{
	// ������� �������������� ������� ������ cell �������� size � ������� int. �������� ������� ������������ �� �������

	int** matrix = new int* [size];

	for (int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];

		for (int j = 0; j < size; j++)
		{
			if (!i || i == size - 1 || !j || j == size - 1)
				matrix[i][j] = 1;
			else
			{
				if (i % 2)
				{
					if (!(j % 2))
						matrix[i][j] = cells[i / 2][j / 2].walls[__LEFT__];

					else
						matrix[i][j] = 0;
				}

				else
				{
					if (!(j % 2))
						matrix[i][j] = 1;

					else
						matrix[i][j] = cells[i / 2][j / 2].walls[__UP__];
				}
			}
		}
	}

	return matrix;
}

Cell __check__(Cell** cells, int size, int x, int y, int direction)
{
	// ������� �������� ������ � ����������� direction �� ������ �� ����������� (x; y) � ������� ������ cells �������� size. ������ � �������� ����������� ������������ �� �������

	 // � ����������� �� ����������� ������������ �� ��� ���� ������ 
	switch (direction)
	{
	case __UP__:
		if (!y)
			return { {1, 1, 1, 1}, 1 };

		return cells[--y][x];

	case __DOWN__:
		if (y == size - 1)
			return { {1, 1, 1, 1}, 1 };

		return cells[++y][x];

	case __LEFT__:
		if (!x)
			return { {1, 1, 1, 1}, 1 };

		return cells[y][--x];

	case __RIGHT__:
		if (x == size - 1)
			return { {1, 1, 1, 1}, 1 };

		return cells[y][++x];
	}
}

void __randomize_cells__(Cell** cells, int size, int x, int y)
{
	/*
	�������� ������� ��������� ���������
	�������� ���������� "����������������� ����� � �������" ��� ��� �������� "������������ ��������� ������������"

	������������ ��������� ������������ ����� ������� ����� �� ������, ������ ������ �� ������� ����������� ������ �����. ������� � ������ � ������������ (x; y), ��������� ����� �������� ��������� �������� ������, ������� ��� �� ���� ��������. ��������� ������� ����� ����� ����� �������� � �������� ����� ������ ��� ���������� � ��������� �� � ������. ������ �� ������, � ������� ��� ������ ��������, �� ������������ �� ����, ���� �� ��������� ������ � ������������ �������, ��������� ��������� ����, ������� ��� �����, ������������ ������ (�������� ����� ����������). ���� ������� ������������ �� ��� ���, ���� ������ ������ �� ����� ��������, � ���������� ���� ��������� ��������� �������� � ��������� ������.
	��������� ����� ���������, ��������� ���������� ������ ������ � � ��������� �� ����� �������� ������. ������ ��-�� ����, ��� � ������ ��������� ����� �����, ���������� �������������� ������� ������ � ������� int ��� �������� ������, ��-�� ���� ������ ������� ��������� ����� ���� ������ �������� ������
	*/

	// ���� �� �������� ��� ������
	bool flag_is_all_changed = 1;

	// ���� (���������� ������, ������� ���� ��������)
	int path_size = 0;
	Coordinates* path = new Coordinates[path_size];

	// �������� ������ �� ��� ���, ���� ��� �� ����� ��������
	do
	{
		flag_is_all_changed = 1;

		// ��������� ��������� ���� ������
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (!cells[i][j].was_changed)
				{
					flag_is_all_changed = 0;

					break;
				}
			}
		}

		// ��������� ����������� ��� "�����"
		int random_direction;

		// ��������� ��������� ������� "�����"
		bool is_all_neighbors_changed = __check__(cells, size, x, y, __UP__).was_changed && __check__(cells, size, x, y, __DOWN__).was_changed && __check__(cells, size, x, y, __LEFT__).was_changed && __check__(cells, size, x, y, __RIGHT__).was_changed;

		// ���� �� ��� ������ ��������, ������� "�����"
		if (!is_all_neighbors_changed)
		{
			// ��������� ������� ������ � ����, ���������� "�����"
			__add_el__(path, path_size, { x, y });

			// �������� ����������� ��� "�����" (�� ��� ����, ��� ������ ��� �� ��������)
			do
			{
				random_direction = rand() % __COUNT_OF_DIRECTIONS__;
			} while (__check__(cells, size, x, y, random_direction).was_changed);

			// ������ ��������� ������� ������ �� ���������
			cells[y][x].was_changed = 1;

			// � ����������� �� ����������� "�����" ������ ����� � �������� ����������
			switch (random_direction)
			{
			case __UP__:
				cells[y][x].walls[__UP__] = 0;
				cells[--y][x].walls[__DOWN__] = 0;
				cells[y][x].was_changed = 1;

				break;

			case __DOWN__:
				cells[y][x].walls[__DOWN__] = 0;
				cells[++y][x].walls[__UP__] = 0;
				cells[y][x].was_changed = 1;

				break;

			case __LEFT__:
				cells[y][x].walls[__LEFT__] = 0;
				cells[y][--x].walls[__RIGHT__] = 0;
				cells[y][x].was_changed = 1;

				break;

			case __RIGHT__:
				cells[y][x].walls[__RIGHT__] = 0;
				cells[y][++x].walls[__LEFT__] = 0;
				cells[y][x].was_changed = 1;

				break;
			}
		}
		else
		{
			// ���� ��� ������ ��������, ������������ ����� � ����� � ���������� ������� ���� � ���� ������, � ������� �� ��� ������ ��������
			for (int i = path_size - 1; i >= 0; i--)
			{
				// ������ ���������� �� ���������� ������ � ����
				x = path[i].x;
				y = path[i].y;

				// ��������� ��������� ���� �������
				bool is_all_new_neighbors_changed = __check__(cells, size, x, y, __UP__).was_changed && __check__(cells, size, x, y, __DOWN__).was_changed && __check__(cells, size, x, y, __LEFT__).was_changed && __check__(cells, size, x, y, __RIGHT__).was_changed;

				// ���� ������ �� ��� ������ ��������, ������������� ���� ����
				if (!is_all_new_neighbors_changed)
					break;

				// ������� ���������� ������ ����
				__delete_last_el__(path, path_size);
			}
		}
	} while (!flag_is_all_changed);

	// ������� ����
	delete[] path;
}

Cell** __init_cells__(int size)
{
	// ������������� ������� ������ �������� size. �� ��������� ������ ���������� �����������, � ������ �� �������� �����. �������� ������� ������ ������������ �� �������

	Cell** cells = new Cell * [size];

	for (int i = 0; i < size; i++)
	{
		cells[i] = new Cell[size];

		for (int j = 0; j < size; j++)
			cells[i][j] = { {1, 1, 1, 1}, 0 };
	}

	return cells;
}

template <class T>
void __delete_last_el__(T*& arr, int& size)
{
	// ������� �������� ���������� �������� � ������� arr �������� size

	T* temp_arr = new T[size - 1];

	for (int i = 0; i < size - 1; i++)
		temp_arr[i] = arr[i];

	arr = temp_arr;

	size--;
}

template <class T>
void __add_el__(T*& arr, int& size, T el)
{
	// ������� ���������� � ����� ������� arr �������� size �������� el

	T* temp_arr = new T[size + 1];

	for (int i = 0; i < size; i++)
		temp_arr[i] = arr[i];

	temp_arr[size] = el;

	arr = temp_arr;

	size++;
}

#endif