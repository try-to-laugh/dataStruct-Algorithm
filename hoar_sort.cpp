#include<iostream>
#include<ctime>

void hoar_sort(int*, int, int);
void qs(int* s_arr, int first, int last);

using namespace std;

int main()
{
	srand(time(NULL));
	int *Test_massive = new int[10];
	cout << "unsotred:" << endl;
	for (int i = 0; i < 10; i++) {
		Test_massive[i] = rand() % 10;
		cout << Test_massive[i] << " ";
	}
	cout << endl;
	hoar_sort(Test_massive, 0, 9);
	cout << "sorted:" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << Test_massive[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

void hoar_sort(int *mass, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		cout << mass[i] << " ";
	}
	cout << endl;
	system("pause");
	int barrier = mass[end];
	int i = start, j = end;
	do
	{
		while (mass[i] < barrier) {i++;}
		while (mass[j] > barrier) {j--;}
		if (i <= j) {
			int temp = mass[i];
			mass[i] = mass[j];
			mass[j] = temp;
			i++;
			j--;
		}
		
	} while (i <= j);
	
	if (i < end)
		hoar_sort(mass, i, end);
	if (start < j)
		hoar_sort(mass, start, j);
	
}

void qs(int* s_arr, int first, int last)
{
	int i = first, j = last, x = s_arr[(first + last) / 2];

	do {
		while (s_arr[i] < x) i++;
		while (s_arr[j] > x) j--;

		if (i <= j) {
			if (s_arr[i] > s_arr[j]) swap(s_arr[i], s_arr[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		qs(s_arr, i, last);
	if (first < j)
		qs(s_arr, first, j);
}