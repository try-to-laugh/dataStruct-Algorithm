#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<list>
#include<algorithm>
#include<ctime>
#include<cmath>

#define inf 10000

using namespace std;

void Generate_Graph(int **matrixDrow, int **Graph, int size, int amountP, int amountSw)
{
	//можно сделать проверку 
	//если колл-во ребер больше, чем (n-1)! ошибка так, как всех возможныз путей меньше 

	srand(time(NULL));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			matrixDrow[i][j] = 0;
		}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			Graph[i][j] = 0;
		}

	

	for (int i = 1; i <= amountP; i++)
	{
		int x = rand() % size;
		int y = rand() % size;

		if (matrixDrow[x][y] == 0) {
			matrixDrow[x][y] = i;
			continue;
		}
		i--;
	}

	//генерация ребер 
	int edge_to_line = static_cast<int>(amountSw / amountP); // сколько на одну линию
	int remainder = amountP - edge_to_line;

	//у каждой точки минимуи edge_to_line ребер
	for (int i = 1; i <= amountP; i++)
	{
		//координаты для подсчета веса
		int x1, y1, x2, y2;

		for (int h = 0; h < edge_to_line; h++)
		{
			//рандом от 1 до point 
			int point2 = rand() % amountP + 1;

			//чтобы не было путей из себя в себя || путь уже существует
			if (point2 == i || Graph[i - 1][point2 - 1] != 0) {
				h--;
				continue;
			}

			//поиск позиции в графе размещения
			for (int k = 0; k < size; k++)
				for (int j = 0; j < size; j++) {
					if (point2 == matrixDrow[k][j]) {
						x2 = j;
						y2 = k;
					}
					else if (i == matrixDrow[k][j]) {
						x1 = j;
						y1 = k;
					}
				}

			//подcчет веса ребра
			int temp = static_cast<int>(sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)) * 10);
			Graph[i - 1][point2 - 1] = temp;
			Graph[point2 - 1][i - 1] = temp;
		}
	}

	cout << "matrix: " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			cout << matrixDrow[i][j] << " ";
		}
		cout << endl;
	}
	cout << "graph: " << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			if (Graph[i][j] > 9) {
				cout << Graph[i][j] << " ";
			}
			else {
				cout << Graph[i][j] << "  ";
			}
		}
		cout << endl;
	}
}


int main()
{
	cout << "amount of point: ";
	int size;
	cin >> size;
	cout << "amount of edge: ";
	int edge;
	cin >> edge;

	int **matr = new int*[size];
	for (int i = 0; i < size; i++) {
		matr[i] = new int[size];
	}

	int **Graph = new int*[size];
	for (int i = 0; i < size; i++) {
		Graph[i] = new int[size];
	}

	Generate_Graph(matr, Graph, size, size, edge);
	system("pause");



	//ввод графа из матрицы

	/*ifstream fin("input.txt");
	if (!fin.is_open()) {
		cout << "error with open file" << endl;
	}

	string str;
	stringstream ss;
	getline(fin, str);
	ss << str;
	int N;
	ss >> N;
	cout << N << endl;
	int **matrix = new int*[N];
	for (int i = 0; i < N; i++) {
		matrix[i] = new int[N];
	}
	int m = 0;
	for (int k = 0; k < N; k++)
	{
		getline(fin, str);
		ss << str;
		for (int i = 0; i < N; i++)
		{
			fin >> matrix[m][i];
		}
		m++;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] < 10)
				cout << matrix[i][j] << "   ";
			else
				cout << matrix[i][j] << "  ";

		}
		cout << endl;
	}*/




	int *weight = new int[size];
	for (int i = 0; i < size; i++) {
		weight[i] = inf;
	}
	weight[0] = 0;

	list<int> pos;
	pos.push_back(0);
	int i = pos.front();
	cout << endl;

	//сам алгоритм
	while (!(pos.empty()))
	{
		int current = pos.front();
		for (int i = 0; i < size; i++)
		{
			if (Graph[current][i] == 0) {
				continue;
			}
			int path = weight[current] + Graph[current][i];
			if (weight[i] > path && path > 0)
			{
				weight[i] = path;
				pos.push_back(i);
			}
		}
		pos.pop_front();
	}
	//расстояния до каждой из вершин из 1

	cout << "weight: ";
	for (int i = 0; i < size; i++) { cout << weight[i] << " "; }
	cout << endl;
	//выычисление расстояния до определенной вершины
	int temp = weight[size - 1];
	int current = size - 1;
	vector<int> line;
	line.push_back(size - 1);
	while (temp != 0)
	{
		for (int i = size - 1; i >= 0; i--)
		{
			if (Graph[current][i] == 0) { continue; }
			int new_temp = temp - Graph[current][i];
			int toCompare = weight[i];
			if (new_temp == toCompare)
			{
				temp = new_temp;
				line.push_back(i);
				current = i;
				break;
			}
		}
	}

	vector<int>::iterator it = line.begin();
	reverse(line.begin(), line.end());
	cout << "path: ";
	while (it != line.end()) {
		cout << *it + 1 << " ";
		it++;
	}
	cout << endl;
	system("pause");
	return 0;
}


//1) написать считывание 
//2) обработка
//3) поиск пути
//4) вывод результата на экран