// * ������������ �����
#include <stdio.h> // ���������� ��� ������� �������
#include <stdlib.h> // ��� ������ � ������������ �������
#include<locale.h> 
#include<math.h>

typedef double(*TFun)(double); // �������� ������������ ���� ���������� �� ������� � 1-� ����������.

// * ��������� �������
double Y(double x); // ���������� �������
double V(double x); // �������� ������� 
double* tabl_func(TFun f, double xmin, double xmax, double dx); // ������������� ������� �������������� �������
double* sort_func(double* x, int n, char c); // ���������� �������
int find_func(double* x, int size, double y); // ����� �������� � �������
double* calc_func(double* x, int size); // ���.�������
void DisplayArray(double* x, int n); // ����� �� ����� ������
int GetSizeArray(double xmin, double xmax, double dx); // ��������� ������� ��� ������� �������������� �������

int main(void)
{
	setlocale(LC_ALL, "RUS");
	int success_work = 0; // ��� ������������ ������ �����
	while (1)
	{
		double xmin, xmax, dx; 
		int main_item; // ��� ������ �������
		printf("�������� �������: \n");
		printf("1. ���������� �������\n");
		printf("2. �������� �������\n");
		scanf("%d", &main_item);
		switch (main_item)
		{
		case 1:
			printf("������� ����������� �������� xmin<0 � ������������ �������� xmax>0 � ��� ���������:\n");
			scanf("%lf%lf%lf", &xmin, &xmax, &dx);
			printf("x\t\t | y\n");
			puts("---------------------------");
			for (double x = xmin; x <= xmax; x += dx) // ������������� �������
				printf("%lf\t | %lf\n", x, Y(x));

			// ** ��� ����
			// * ������������� �������
			printf("������������������ ������:\n");
			double* arr_first = tabl_func(Y, xmin, xmax, dx);
			int sizeArr = GetSizeArray(xmin, xmax, dx);
			DisplayArray(arr_first, sizeArr);
			puts("------");

			// * ���������� � �����
			int c1;
			printf("������� 1, ����� ������������� ������ �� �����������, � 0 ���� �� ��������:\n");
			scanf("%d", &c1);
			printf("��������������� ������:\n");
			DisplayArray(sort_func(arr_first, sizeArr, c1), sizeArr);
			puts("------");

			// * ���. �������
			printf("������� (����������� ������� ������� ��������� � �����):\n");
			DisplayArray(calc_func(arr_first, sizeArr), sizeArr);

			break;
		case 2:
			
			printf("������� ����������� �������� xmin<0 � ������������ �������� xmax>0 � ��� ���������:\n");
			scanf("%lf%lf%lf", &xmin, &xmax, &dx);
			printf("x\t\t | y\n");
			puts("---------------------------");
			for (double x = xmin; x <= xmax; x += dx)
				printf("%lf\t | %lf\n", x, V(x));

			// ** ��� ����
			// * ������������� �������
			printf("������������������ ������:\n");
			double* arr_second = tabl_func(V, xmin, xmax, dx);
			DisplayArray(arr_second, GetSizeArray(xmin, xmax, dx));
			puts("------");

			// * ���������� � �����
			int c2;
			printf("������� 1, ����� ������������� ������ �� �����������, � 0 ���� �� ��������:\n");
			scanf("%d", &c2);
			printf("��������������� ������:\n");
			DisplayArray(sort_func(arr_second, sizeArr, c2), sizeArr);
			puts("------");

			// * ���. �������
			printf("������� (����������� ������� ������� ��������� � �����):\n");
			DisplayArray(calc_func(arr_second, sizeArr), sizeArr);
			break;
		default:
			printf("������. ������������ ����� �������\n");
			success_work = -1;
			break;
		}
		if (success_work == -1) // ���� ������� ��� �����������, ���� �����������
		{
			success_work = 0;
			continue;
		}
		char a;
		printf("��������� ���������? <�� - y, ��� - ������� n>\n");
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
	int sizeArray = GetSizeArray(xmin, xmax, dx); // �������� ������ �������
	double* arr = malloc(sizeArray * sizeof(double)); // �������� ������ �������
	int i = 0;
	for (double x = xmin; x <= xmax; x += dx, i++) // �������������� ������
		arr[i] = f(x);
	return arr;
}


double* sort_func(double* x, int n, char c)
{
	int i, j, step;
	double tmp;
	if (c == 0) // ���������� �� ��������
	{
		for (step = n / 2; step > 0; step /= 2) // �������� ���������� ����� �� ��������
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
	else // �� ��������� �� �����������
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
	for (int i = 0; i < size; i++) // ���������� ������, ���� �������� �������� ��������� �������� �������
	{
		if (x[i] == y)
			return i;
	}
	return -1; // ���������� -1 , ���� ������ �� �������
}


double* calc_func(double* x, int size)
{
	double* temp = malloc(size * sizeof(double));
	double min = x[0];
	int index_min = 0;
	for (int i = 1; i < size; i++) // ������� ����������� ������� � ��� ������ � �������
	{
		if (x[i] < min)
		{
			min = x[i];
			index_min = i;
		}
	}
	for (int i = 0; i < index_min; i++) // �������� �������� �� ���.��������
		temp[i] = x[i];
	for (int i = index_min; i < size - 1; i++) // �������� �������� �� �������
		temp[i] = x[i + 1];
	temp[size - 1] = x[index_min]; // �������� ����������� ������� � �����
	return temp;
}




void DisplayArray(double* x, int n)
{
	for (int i = 0; i < n; i++) // ����� �� ����� ������, ��� n - ����������� �������
		printf("arr[%d] = %lf \n", i + 1, x[i]);
}


int GetSizeArray(double xmin, double xmax, double dx) // ��������� ������� ��� ������� �������������� �������
{
	int sizeArray = 0;
	for (double x = xmin; x <= xmax; x += dx)
		sizeArray++;
	return sizeArray;
}
