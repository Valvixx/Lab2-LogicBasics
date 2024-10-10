#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(linker, "/STACK:1672272216")
int main(void)
{

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	clock_t start, end; // объявляем переменные для определения времени выполнения
	double time_spent;

	int size = 2000;

	int i = 0, j = 0, r;
	int a[2000][2000], b[2000][2000], c[2000][2000], elem_c;

	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < size)
	{
		while (j < size)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < size)
	{
		while (j < size)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}

	start = clock();

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			elem_c = 0;
			for (r = 0; r < size; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}

	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;

	printf("Multiplication time: %.6f seconds\n", time_spent);
	return(0);
}
