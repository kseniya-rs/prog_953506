#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h> 

void EnterInt(int* _i)  //проверка ввода

{
	char ch;
	int i;
	int correct;
	do
	{
		correct = scanf_s("%9d%c", &i, &ch, 1);

		if (!(correct > 0 && i >= 0 && (ch == '\n' || ch == ' ')))
		{
			printf("Incorrect input, try again:\n");
		}


	} while (!(correct > 0 && i >= 0 && (ch == '\n' || ch == ' ')));


	/* Set value */
	*_i = i;

}

void FillArrayRandom(int** const arr, const int rows, const int columns) //Рандомное заполнние
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			arr[i][j] = rand() % 2;
		}
	}
}

void FillArrayManually(int** const arr, const int rows, const int columns) //Заполнение массива вручную
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			EnterInt(&(arr[i][j]));
		}
	}
}

void PrintArray(int** const  arr, const int rows, const int columns) //Вывод
{
	printf_s("\n");

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf_s("\n");
}

int** MemoryAllocation(int* rows, int* cols)
{

	printf_s("Введите кол-во строк массива ");
	EnterInt(rows);
	printf_s("Введите кол-во столбцов массива ");
	EnterInt(cols);

	int** arr = (int**)malloc(*rows * sizeof(int*)); 
	if (arr)
	{
		for (int i = 0; i < *rows; i++)
		{
			if (arr[i] = (int*)malloc(*cols * sizeof(int))) //Выделение памяти
			{
				continue;
			}
			printf_s("Память не выделена для указателя %d !\n", i);
			exit(1);

		}
		printf_s("Выберите способ заполнения:\n1 - случайный\n2 - вручную\n");

		// Способ ввода
		int input;

		while (1)
		{
			EnterInt(&input);

			if (input == 1)
			{
				FillArrayRandom(arr, *rows, *cols);
				break;
			}
			else if (input == 2)
			{
				FillArrayManually(arr, *rows, *cols);
				break;
			}
			else
			{
				printf("Повторите ввод\n");
				continue;

			}
		}

		return arr;

	}

	else
	{
		printf_s("Память не выделена для массива указателей!\n");
		exit(1);
	}
}

void MemoryDeletion(int** arr, int* rows) // Очистка
{
	for (int i = 0; i < *rows; i++)
	{
		free(arr[i]);
	}
	free(arr);

}

// Функция возвращает указатель на повёрнутую матрицу 

int** Rotation(int** arr, int* rows, int* cols, int* counter)
{
	while (*counter < 4)
	{
		int** newMatrix = (int**)malloc(*cols * sizeof(int*));

		for (int i = 0; i < *cols; i++)
		{
			newMatrix[i] = (int*)malloc(*rows * sizeof(int));
		}

		int newColumn, newRow = 0;

		for (int oldColumn = *cols - 1; oldColumn >= 0; oldColumn--)
		{
			newColumn = 0;
			for (int oldRow = 0; oldRow < *rows; oldRow++)
			{
				newMatrix[newRow][newColumn] = arr[oldRow][oldColumn];

				newColumn++;
			}

			newRow++;
		}

		for (int i = 0; i < *rows; i++)
		{
			free(arr[i]);
		}
		free(arr);
		int tmp = *rows;
		*rows = *cols;
		*cols = tmp;
		arr = newMatrix;
		(*counter)++;
		return arr;;
	}

}

int main(void)
{
	setlocale(LC_ALL, "Rus");
	int  m1, n1, m2, n2;
	int counter = 0;
	srand(time(NULL));
	int** k, ** l;
	k = l = NULL;
	printf_s("Первый ввод для скважины, второй ввод для включа\n");
	k = MemoryAllocation(&m1, &n1);
	l = MemoryAllocation(&m2, &n2);
	PrintArray(k, m1, n1);
	PrintArray(l, m2, n2);
	int flag_count = 0;
	int flag_count_1s = 0;
	for (size_t i = 0; i < m2; i++)
	{
		for (size_t j = 0; j < n2; j++)
		{
			if (l[i][j] == 1)
			{
				flag_count_1s++;
			}
		}
	}

	while (counter < 4 && flag_count != flag_count_1s)
	{
		for (int s = 0; flag_count != flag_count_1s && s < m1 - m2 + 1; s++)
		{
			for (int t = 0; flag_count != flag_count_1s && t < n1 - n2 + 1; t++)
			{

				flag_count = 0;

				for (int i = 0, j; i < m2; i++)
				{
					for (j = 0; j < n2; j++)
					{
						if (l[i][j] == 1) {
							if (k[i + s][j + t] == 0) {
								flag_count++;
							}
							else {
								break;
							}
						}
					}
					if (j != n2) {
						break;
					}
				}
			}
		}
		l = Rotation(l, &m2, &n2, &counter);
	}

	if (flag_count == flag_count_1s)
	{
		printf_s("Ключ подошёл!\n");
	}
	else
	{
		printf_s("Ключ не подходит!\n");
	}

	MemoryDeletion(k, &m1);
	MemoryDeletion(l, &m2);
	system("pause");
	return 0;
}