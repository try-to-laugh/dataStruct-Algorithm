#include<iostream>

using namespace std;

void SortM(int arr[], int low, int hight,int lenth);
void blue(int m[], int size)
{
	cout << sizeof(m) / 4 << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int arr3[]{ 15,12,1,3,4,56,2 }; // она только для интов работает

	for (int i = 0; i < sizeof(arr3) / 4; i++)
		cout << arr3[i] << " ";
	cout << endl;
	SortM(arr3, 0, sizeof(arr3) / 4 - 1,sizeof(arr3)/4);
	for (int i = 0; i < sizeof(arr3) / 4; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

void SortM(int arr[], int low, int hight,int lenth)
{
	if (hight <= low) {
		return;
	}
	int mid = (hight + low) / 2;
	cout << "low: " << low << " " << "mid: " << mid << " " << "hight: " << hight << endl;
	SortM(arr, low, mid,lenth);
	SortM(arr, mid + 1, hight,lenth);
	int *buf = new int[lenth];
	for (int i = low; i <= hight; i++) {
		buf[i] = arr[i];
		cout << buf[i] << " ";
	}
	cout << endl;

	int i = low, j = mid + 1;
	for (int k = low; k <= hight; k++)
	{
		if (i > mid) {
			arr[k] = buf[j];
			j++;
		}
		else if (j > hight) {
			arr[k] = buf[i];
			i++;
		}
		else if (buf[j] < buf[i]) {
			arr[k] = buf[j];
			j++;
		}
		else {
			arr[k] = buf[i];
			i++;
		}
	}
}