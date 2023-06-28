#pragma once
#ifndef __MAZE_GEN__
#define __MAZE_GEN__

#define __COUNT_OF_DIRECTIONS__ 4
#define __UP__ 0
#define __DOWN__ 1
#define __LEFT__ 2
#define __RIGHT__ 3

// Номер входа в лабиринт, записываемый в матрицу
#define __ENTRY_NUM__ 3

// Номер выхода из лабиринта, записываемый в матрицу
#define __EXIT_NUM__ 2

using namespace std;
#include <random>

struct Coordinates
{
	// Структура, отвечающая за координаты

	int x, y;
};

struct Cell
{
	// Структура, отвечающая за клетку в матрице

	// Массив, хранящий информацию о наличии стен возле клетки
	// сверху (0 элемент), снизу (1 элемент), слева (2 элемент) и справа (3 элемент)
	bool walls[4];

	// Была ли изменена эта клетка
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
	// Функция создания матрицы лабиринта размером size из заданного места (x; y). size, x и y - нечётные числа. Итоговая матрица возвращается из функции

	if (!x || !y)
	{
		x = 2 * (rand() % (size / 2 - 1) + 1) + 1;
		y = 2 * (rand() % (size / 2 - 1) + 1) + 1;
	}

	// Инициализируем матрицу клеток
	Cell** cells = __init_cells__(size / 2);

	// Создаём тунели в стенах
	__randomize_cells__(cells, size / 2, x / 2, y / 2);

	// Конвертируем матрицу клеток в матрицу int
	int** matrix = __convert_cells_to_matrix__(cells, size);

	// Создаём вход и выход из лабиринта
	if (z != 0)
		matrix[y][x] = __ENTRY_NUM__;

	__randomize_exit__(matrix, size, x, y);

	return matrix;
}

void __randomize_exit__(int** matrix, int size, int x, int y)
{
	/*
	Функция случайного создания выхода из матрицы лабиринта matrix размером size по расположению его входа (x; y)
	Принцип работы:
		Матрица делится на четыре четверти (по середине):
			1 | 2
		   --+--
			3 | 4

		В зависимости от расположения входа ему сопоставляется четверть.
		Если вход расположен на стыке двух или всех четвертей ему сопоставляется случайная из этих двух или четырёх четвертей соответственно.
		Далее, в зависимости от четверти входа, четверть выхода определяется, как самая дальняя (1 -> 4, 2 -> 3, 3 -> 2, 4 -> 1). В этой четверти случайно выбираются координаты, на которых в матрице стоит ноль.
		На выбранных координатах ставится число __EXIT_NUM__
	*/

	// Четверть, в которой расположен вход (x; y)
	int quarter;

	// Расчёт четверти входа
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

	// Координаты выхода
	int exit_x, exit_y;

	// Расчёт координат выхода в зависимости от четверти входа (в цикле, пока на выбранных координатах стоит не ноль)
	do
	{
		switch (quarter)
		{
		case 1:
			exit_x = rand() % (size / 2 - 1) + size / 2 + 1; // От size / 2 + 1 до size - 2
			exit_y = rand() % (size / 2 - 1) + size / 2 + 1; // От size / 2 + 1 до size - 2

			break;

		case 2:
			exit_x = rand() % (size / 2 - 1) + 1;                 // От 1 до size / 2 - 1
			exit_y = rand() % (size / 2 - 1) + size / 2 + 1; // От size / 2 + 1 до size - 2

			break;

		case 3:
			exit_x = rand() % (size / 2 - 1) + size / 2 + 1; // От size / 2 + 1 до size - 2
			exit_y = rand() % (size / 2 - 1) + 1;                // От 1 до size / 2 - 1

			break;

		case 4:
			exit_x = rand() % (size / 2 - 1) + 1; // От 1 до size / 2 - 1
			exit_y = rand() % (size / 2 - 1) + 1; // От 1 до size / 2 - 1

			break;
		}
	} while (matrix[exit_y][exit_x]);

	// Ставим на координаты выхода число __EXIT_NUM__
	matrix[exit_y][exit_x] = __EXIT_NUM__;
}

int** __convert_cells_to_matrix__(Cell** cells, int size)
{
	// Функция преобразования матрицы клеток cell размером size в матрицу int. Итоговая матрица возвращается из функции

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
	// Функция проверки клетки в направлении direction от клетки по координатам (x; y) в матрице клеток cells размером size. Клетка в заданном направлении возвращается из функции

	 // В зависимости от направления возвращается та или иная клетка 
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
	Основная функция генерации лабиринта
	Алгоритм называется "рандомизированный поиск в глубину" или ещё алгоритм "рекурсивного обратного отслеживания"

	Пространство лабиринта представляет собой большую сетку из клеток, вокруг каждой из которых расположены четыре стены. Начиная с клетки с координатами (x; y), компьютер затем выбирает случайную соседнюю клетку, которая еще не была посещена. Компьютер удаляет стену между двумя клетками и отмечает новую клетку как посещенную и добавляет ее в массив. Доходя до клетки, у которой все соседи изменены, он возвращается по пути, пока не достигает клетки с непосещенным соседом, продолжая генерацию пути, посещая эту новую, непосещенную клетку (создавая новое соединение). Этот процесс продолжается до тех пор, пока каждая клетка не будет посещена, в результате чего компьютер полностью вернется к начальной клетке.
	Благодаря этому алгоритму, генерация происходит весьма быстро и в лабиринте не будет закрытых комнат. Однако из-за того, что в основе алгоритма лежат стены, приходится конвертировать матрицу клеток в матрицу int для удобного вывода, из-за чего размер матрицы лабиринта может быть только нечётным числом
	*/

	// Были ли изменены все клетки
	bool flag_is_all_changed = 1;

	// Путь (координаты клеток, которые были пройдены)
	int path_size = 0;
	Coordinates* path = new Coordinates[path_size];

	// Изменяем клетки до тех пор, пока все не будут изменены
	do
	{
		flag_is_all_changed = 1;

		// Проверяем состояние всех клеток
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

		// Рандомное направление для "червя"
		int random_direction;

		// Проверяем состояние соседей "червя"
		bool is_all_neighbors_changed = __check__(cells, size, x, y, __UP__).was_changed && __check__(cells, size, x, y, __DOWN__).was_changed && __check__(cells, size, x, y, __LEFT__).was_changed && __check__(cells, size, x, y, __RIGHT__).was_changed;

		// Если не все соседи изменены, пускаем "червя"
		if (!is_all_neighbors_changed)
		{
			// Добавляем текущую клетку в путь, пройденный "червём"
			__add_el__(path, path_size, { x, y });

			// Выбираем направление для "червя" (он идёт туда, где клетка ещё не изменена)
			do
			{
				random_direction = rand() % __COUNT_OF_DIRECTIONS__;
			} while (__check__(cells, size, x, y, random_direction).was_changed);

			// Меняем состояние текущей клетки на изменённое
			cells[y][x].was_changed = 1;

			// В зависимости от направления "червя" ломаем стены и изменяем координаты
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
			// Если все соседи изменены, откатываемся назад в цикле к предыдущем клеткам пути и ищем клетку, у которой не все соседи изменены
			for (int i = path_size - 1; i >= 0; i--)
			{
				// Меняем координаты на предыдущую клетку в пути
				x = path[i].x;
				y = path[i].y;

				// Проверяем состояние всех соседей
				bool is_all_new_neighbors_changed = __check__(cells, size, x, y, __UP__).was_changed && __check__(cells, size, x, y, __DOWN__).was_changed && __check__(cells, size, x, y, __LEFT__).was_changed && __check__(cells, size, x, y, __RIGHT__).was_changed;

				// Если соседи не все соседи изменены, останавливаем этот цикл
				if (!is_all_new_neighbors_changed)
					break;

				// Удаляем предыдущую клетку пути
				__delete_last_el__(path, path_size);
			}
		}
	} while (!flag_is_all_changed);

	// Удаляем путь
	delete[] path;
}

Cell** __init_cells__(int size)
{
	// Инициализация матрицы клеток размером size. По умолчанию клетка помечается неизменённой, и вокруг неё ставятся стены. Итоговая матрица клеток возвращается из функции

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
	// Функция удаления последнего элемента в массиве arr размером size

	T* temp_arr = new T[size - 1];

	for (int i = 0; i < size - 1; i++)
		temp_arr[i] = arr[i];

	arr = temp_arr;

	size--;
}

template <class T>
void __add_el__(T*& arr, int& size, T el)
{
	// Функция добавления в конец массива arr размером size элемента el

	T* temp_arr = new T[size + 1];

	for (int i = 0; i < size; i++)
		temp_arr[i] = arr[i];

	temp_arr[size] = el;

	arr = temp_arr;

	size++;
}

#endif