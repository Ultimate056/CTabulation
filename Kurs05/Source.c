// * Заголовочные файлы
#include <stdio.h> // Подключает все базовые функции
#include <stdlib.h> // для работы с динамической памятью
#include<locale.h> 
#include<math.h>

typedef double(*TFun)(double); // Создание собственного типа указателей на функции с 1-м аргументом.

// * Прототипы функций
double Y(double x); // Монотонная функция
double V(double x); // Кусочная функция 
double* tabl_func(TFun f, double xmin, double xmax, double dx); // Инициализация массива табулированной функции
double* sort_func(double* x, int n, char c); // Сортировка массива
int find_func(double* x, int size, double y); // Поиск значений в массиве
double* calc_func(double* x, int size); // Инд.задание
void DisplayArray(double* x, int n); // Вывод на экран массив
int GetSizeArray(double xmin, double xmax, double dx); // Получение размера для массива табулированной функции

int main(void)
{
	setlocale(LC_ALL, "RUS");
	int success_work = 0; // Для корректности работы цикла
	while (1)
	{
		double xmin, xmax, dx; 
		int main_item; // Для выбора функции
		printf("Выберите функцию: \n");
		printf("1. Монотонная функция\n");
		printf("2. Кусочная функция\n");
		scanf("%d", &main_item);
		switch (main_item)
		{
		case 1:
			printf("Введите минимальное значение xmin<0 и максимальное значение xmax>0 и шаг табуляции:\n");
			scanf("%lf%lf%lf", &xmin, &xmax, &dx);
			printf("x\t\t | y\n");
			puts("---------------------------");
			for (double x = xmin; x <= xmax; x += dx) // Табулирование функции
				printf("%lf\t | %lf\n", x, Y(x));

			// ** Доп блок
			// * Инициализация массива
			printf("Инициализированный массив:\n");
			double* arr_first = tabl_func(Y, xmin, xmax, dx);
			int sizeArr = GetSizeArray(xmin, xmax, dx);
			DisplayArray(arr_first, sizeArr);
			puts("------");

			// * Сортировка и поиск
			int c1;
			printf("Нажмите 1, чтобы отсортировать массив по возрастанию, и 0 если по убыванию:\n");
			scanf("%d", &c1);
			printf("Отсортированный массив:\n");
			DisplayArray(sort_func(arr_first, sizeArr, c1), sizeArr);
			puts("------");

			// * Инд. Задание
			printf("Задание (минимальный элемент массива поместить в конец):\n");
			DisplayArray(calc_func(arr_first, sizeArr), sizeArr);

			break;
		case 2:
			
			printf("Введите минимальное значение xmin<0 и максимальное значение xmax>0 и шаг табуляции:\n");
			scanf("%lf%lf%lf", &xmin, &xmax, &dx);
			printf("x\t\t | y\n");
			puts("---------------------------");
			for (double x = xmin; x <= xmax; x += dx)
				printf("%lf\t | %lf\n", x, V(x));

			// ** Доп блок
			// * Инициализация массива
			printf("Инициализированный массив:\n");
			double* arr_second = tabl_func(V, xmin, xmax, dx);
			DisplayArray(arr_second, GetSizeArray(xmin, xmax, dx));
			puts("------");

			// * Сортировка и поиск
			int c2;
			printf("Нажмите 1, чтобы отсортировать массив по возрастанию, и 0 если по убыванию:\n");
			scanf("%d", &c2);
			printf("Отсортированный массив:\n");
			DisplayArray(sort_func(arr_second, sizeArr, c2), sizeArr);
			puts("------");

			// * Инд. Задание
			printf("Задание (минимальный элемент массива поместить в конец):\n");
			DisplayArray(calc_func(arr_second, sizeArr), sizeArr);
			break;
		default:
			printf("Ошибка. Неправильный выбор функции\n");
			success_work = -1;
			break;
		}
		if (success_work == -1) // Если человек ввёл неправильно, цикл продолжится
		{
			success_work = 0;
			continue;
		}
		char a;
		printf("Повторить программу? <Да - y, Нет - введите n>\n");
		scanf("%d", &a);
		if ((a = getchar()) == 'n')
			break;
		else
			system("cls");
	}
	system("pause");
	return 0;
}


double Y(double x)
{
	return x * atan(x) - log(sqrt(1 + pow(x, 2)));
}
double V(double x)
{
	if (x > 1)
		return 1 + sqrt(cos(pow(x, 2) + 1));
	else if (x == 1)
		return -2 - pow(sin(x), 2);
	else
		return exp(-cos(x));
}

double* tabl_func(TFun f, double xmin, double xmax, double dx)
{
	int sizeArray = GetSizeArray(xmin, xmax, dx); // Получаем размер массива
	double* arr = malloc(sizeArray * sizeof(double)); // Выделяем память массиву
	int i = 0;
	for (double x = xmin; x <= xmax; x += dx, i++) // Инициализируем массив
		arr[i] = f(x);
	return arr;
}


double* sort_func(double* x, int n, char c)
{
	int i, j, step;
	double tmp;
	if (c == 0) // Сортировка по убыванию
	{
		for (step = n / 2; step > 0; step /= 2) // Алгоритм сортировки Шелла по убыванию
			for (i = step; i < n; i++)
			{
				tmp = x[i];
				for (j = i; j >= step; j -= step)
				{
					if (tmp > x[j - step])
						x[j] = x[j - step];
					else
						break;
				}
				x[j] = tmp;
			}
	}
	else // по умолчанию по возрастанию
	{
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				tmp = x[i];
				for (j = i; j >= step; j -= step)
				{
					if (tmp < x[j - step])
						x[j] = x[j - step];
					else
						break;
				}
				x[j] = tmp;
			}
	}
	return x;
}


int find_func(double* x, int size, double y)
{
	for (int i = 0; i < size; i++) // Возвращает индекс, если заданное значение равняется элементу массива
	{
		if (x[i] == y)
			return i;
	}
	return -1; // Возвращает -1 , если ничего не найдено
}


double* calc_func(double* x, int size)
{
	double* temp = malloc(size * sizeof(double));
	double min = x[0];
	int index_min = 0;
	for (int i = 1; i < size; i++) // Находим минимальный элемент и его индекс в массиве
	{
		if (x[i] < min)
		{
			min = x[i];
			index_min = i;
		}
	}
	for (int i = 0; i < index_min; i++) // Копируем элементы до мин.элемента
		temp[i] = x[i];
	for (int i = index_min; i < size - 1; i++) // Копируем элементы со сдвигом
		temp[i] = x[i + 1];
	temp[size - 1] = x[index_min]; // Копируем минимальный элемент в конец
	return temp;
}




void DisplayArray(double* x, int n)
{
	for (int i = 0; i < n; i++) // Вывод на экран массив, где n - размерность массива
		printf("arr[%d] = %lf \n", i + 1, x[i]);
}


int GetSizeArray(double xmin, double xmax, double dx) // Получение размера для массива табулированной функции
{
	int sizeArray = 0;
	for (double x = xmin; x <= xmax; x += dx)
		sizeArray++;
	return sizeArray;
}
