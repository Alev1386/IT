#include <iostream>
#include <fstream>		//файловые потоки ввода/вывода
#include <cmath>
using namespace std;

#define SPACE 32//Код пробела
#define ENDL 10//Код перехода на новую строку

const char* FNAME = "matrix.txt";

int* params1;
/////////////////prots///////////////////////////////
int** create_matrix(int *params);//создание матрицы
int** get_matrix_from_console();//получение матрицы из консоли
int* get_params();//запрос параметров матрицы в консоли
int** get_matrix_from_file(const char *NAME);//Чтение матрицы из файла
int* check_params(const char* NAME);//ПРоверка параметров матрицы в файле
int multyply_elements_in_row(int** matrix, int* params,int currentr);//Перемножение элементов строки
void print_matrix(int** matrix, int* params);//Вывод матрицы
bool set_option();

int main() {
	setlocale(LC_ALL, "rus");
	int** matrix;
	if (set_option() == 0)
	{
		cout << "Ввод через консоль" << endl;
		matrix = get_matrix_from_console();
	}
	else
	{
		cout << "Ввод через файл" << endl;
		matrix = get_matrix_from_file(FNAME);
		params1 = check_params(FNAME);
	}
	print_matrix(matrix, params1);
	////////////////////////////First issue//////////////////////
	int max_mult = 0;
	for (int i = 0; i < params1[0]; i++)
	{
		int mult = multyply_elements_in_row(matrix, params1, i);
		if (mult)
		{
			cout << "Произведение элементов в <" << i+1 << "> строке равно <" << mult<<"> \n";
			if (mult > max_mult) {
				max_mult = mult;
			}
		}
	}
	cout << "Максимальное произведение по строке = " << max_mult << endl;

	delete[] matrix;
}

///////////////////funcs///////////////////////////////////
int** create_matrix(int *params) {//в функцию передаётся массив на 2 элемента (Число строк и число столбцов)
	int** result = new int* [params[0]];//Размечаем строки
	for (int i = 0; i < params[0]; i++) {//Делим строки на столбцы
		result[i] = new int[params[1]];
	}
	return result;
}
int** get_matrix_from_console() {
	int* params = get_params();//Запрвашиваем у пользователя параметры матрицы
	params1 = params;
	int** matrix = create_matrix(params);//Создаём пустую матрицу
	for (int i = 0; i < params[0]; ++i)//Запрашиваем матрицу у пользователя
	{
		for (int j = 0; j < params[1]; ++j) {
			cout << "Введите элемент с индексом :(" << i+1 << "," << j+1 << ") :";
			cin >> matrix[i][j];
			if (cin.fail()) {
				cout << "Ошибка! Ячейки матрицы должны содержать целые числа!" << endl;
				return 0;
			}
			cout << matrix[i][j] << endl;
		}
	}
	return matrix;
}
int* get_params() {
	int* params = new int[2];
	cout << "Введите число строк" << endl;
	cin >> params[0];
	cout << params[0] << endl;
	if (params[0] <= 0 )
	{
		cout << "Количество строк должно быть натуральным числом" << endl;
		return 0;
	}
	cout << "Введите число столбцов" << endl;
	cin >> params[1];
	cout << params[1] << endl;
	if (params[1] <= 0)
	{
		cout << "Количество столбцов должно быть натуральным числом" << endl;
		return 0;
	}
	return params;
}
int** get_matrix_from_file(const char* NAME) {
	ifstream fin(NAME); //открываем файл
	int* params = check_params(NAME);
	int** arr; //матрица
	arr = new int* [params[0]]; //инициализация
	for (int i = 0; i < params[0]; i++) //массива
	{
		arr[i] = new int[params[1]];
		for (int j = 0; j < params[1]; j++) //чтение элементов
			fin >> arr[i][j];
		if (fin.fail())
		{
			cout << "Ошибка! Только числа должны содержаться в файле!" << endl;
			return 0;
		}
	}
	cout << "Чтение файла окончено!" << endl;
	fin.close(); //закрываем файл
	return arr;
}
int* check_params(const char* NAME) {
	ifstream fin(NAME);//Определяем файл
	int* params = new int[2];
	params[0], params[1] = 0, 0;
	/////////EXISTANCE////////////////////////////////////////
	if (!fin)
	{
		cout << "File " << NAME << " is not found\n";
		fin.close();
		system("pause");
		return 0;
	} // end if
	///////////NOT EMPTY//////////////////////////////////
	if (fin.eof()) 	//empty
	{
		cout << "File " << NAME << " is empty\n";
		fin.close();
		system("pause");
		return 0;
	} // end if
	int countr = 0;
	int countc = 0;
	while (!fin.eof())
	{
		char buf = fin.get();
		if (int(buf) == SPACE) {
			countc++;
		}
		if (int(buf) == ENDL)
		{
			countr++;
			if (countc >= params[1])
			{

				params[1] = countc;
			}
			countc = 0;
		}
	}
	params[0] = countr + 1;
	params[1]++;
	fin.close();
	return params;
}
int multyply_elements_in_row(int** matrix, int* params, int currentr) {
	int result = 1;
	for (int i = 0; i < params[1]; i++)
	{
		if (matrix[currentr][i] != 0) {
			result *= matrix[currentr][i];
		}
		else
		{
			return 0;
		}
	}
	return result;
}
void print_matrix(int** matrix, int* params) {
	cout << "\nЗаданная матрица: \n";
	for (int i = 0; i < params[0]; i++)
	{
		for (int j = 0; j < params[1]; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
bool set_option() {
	cout << "Выберите способ ввода матрицы: \n 1.Через консоль \n 2. Через файл" << endl;
	int option;
	cin >> option;
	return option - 1;
}
