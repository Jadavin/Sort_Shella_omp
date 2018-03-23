// Sort_Shella_omp.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

void ShellSort(double *,int *, int,int,int *); // прототип функции сортировки вставками
void Merge(double [], int, double [], int, double [], int);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	FILE *file;
#pragma warning(disable: 4996)

	file = fopen("massiv.txt", "w");
	const int n = 600;
	const int n1 = 5;
	int merge = 0;
	double original_massiv[n];
	double massiv_part_1[n / 2];
	double massiv_part_2[n / 2];
	int Delta[n1] = { /*701 ,301 ,132 ,*/57 ,23 ,10 ,4 ,1};
	double *p;
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		original_massiv[i] = rand();
	}
	p = original_massiv;
	memcpy(massiv_part_1, p, sizeof(double)*(n / 2));
	memcpy(massiv_part_2, p + n / 2, sizeof(double)*(n / 2));

	//for (int i = 0; i < 25000; i++)
	//{
	//	printf("%.0f\n", massiv_part_1[i]);
	//}
	fprintf(file, "Before sort\n");
	for (int i = 0; i<n; ++i) {
		fprintf(file, "%.0f\n", *(p+i));
	};
	
	ShellSort(massiv_part_1,Delta,n,n1,&merge);

	ShellSort(massiv_part_2, Delta, n, n1, &merge);


	while (merge==2)
	{
		Merge(p, n, massiv_part_1, n / 2, massiv_part_2, n / 2);
		printf("test\n");
		break;
	}
	

	fprintf(file, "After sort\n");
	for (int i = 0; i<n; ++i) {
		fprintf(file, "%.0f\n", *(p + i));
	};
	printf("Финиш\n");
	_getch();
    return 0;
}

void ShellSort(double *arrayPtr,int *arrayDelta, int N, int N1, int *merge) // сортировка вставками
{
	int i, j, k;
	double t;
	#pragma omp parallel for private (k)
	for (int y=0; y<N1; y++)
	{
		for (k = *(arrayDelta+y); k > 0; k /= 2)
		{
			for (i = k; i < N; i++)
			{
				t = arrayPtr[i];
				for (j = i; j >= k; j -= k)
				{
					if (t < arrayPtr[j - k])
						arrayPtr[j] = arrayPtr[j - k];
					else
						break;
				}
				arrayPtr[j] = t;
			}
		}
	}
	*merge += 1;
}

void Merge(double merged[], int lenD, double L[], int lenL, double R[], int lenR)
{
	int i = 0;
	int j = 0;
	while (i<lenL || j<lenR) {
		if (i<lenL & j<lenR) {
			if (L[i] <= R[j]) {
				merged[i + j] = L[i];
				i++;
			}
			else {
				merged[i + j] = R[j];
				j++;
			}
		}
		else if (i<lenL) {
			merged[i + j] = L[i];
			i++;
		}
		else if (j<lenR) {
			merged[i + j] = R[j];
			j++;
		}
	}
}
