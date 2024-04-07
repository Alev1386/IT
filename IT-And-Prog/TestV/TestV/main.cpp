#include <iostream>
#include <fstream>
#define SPACE 32// пробел
#define ENDL 10//переход на новую строку

using namespace std;
const char* FNAME = "test.txt";
int** read_file_write_matr(const char* NAME, int* sizem);
int** write_matr_from_consol(int* sizem);
int task1(int** matr, int* sizem);
int* task2(int** matr, int* sizem);
void print_matr(int** matr, int* sizem);
int* size_matr(const char* NAME);
int* size_matr_cons();
int main() {
	cout << "enter with: \n0 - file;\n1 - console;" << endl;
	int option;
	cin >> option;
	int** Matr;
	int* sze_Matr;
	int str;
	if (option == 0) {
		sze_Matr = size_matr(FNAME);
		
		switch (sze_Matr[0])
		{
		case -1:
			cout << "file not found" << endl;
			return -1;
		case -2:
			cout << "file is empty" << endl;
			return -1;
		default:
			cout << sze_Matr[0] << endl;
			break;
		}
		cout << sze_Matr << endl;

		Matr = read_file_write_matr(FNAME, sze_Matr);


	}

	else {
		sze_Matr = size_matr_cons();
		Matr = write_matr_from_consol(sze_Matr);
	}
	print_matr(Matr, sze_Matr);//вывод матрицы

	/////task1/////
	str = task1(Matr, sze_Matr);
	cout << "The answer for the first task: " << str << " without even numbers" << endl;

	/////task2/////
	int* answer2 = task2(Matr, sze_Matr);
	switch (answer2[0])
	{
	case 0:
		cout << "No repeats" << endl;
		break;
	case 1:
		cout << "The answer for the second task: " << answer2[1] << endl;
		break;
	default:
		break;
	}
}
int** read_file_write_matr(const char* NAME, int* sizem) {

	int** readMatr = new int* [sizem[0]];
	ifstream fin(NAME);
	for (int i = 0; i < sizem[0]; ++i) {
		readMatr[i] = new int[sizem[1]];
		for (int j = 0; j < sizem[1]; ++j) {
			fin >> readMatr[i][j]; cout << readMatr[i][j];
			if (fin.fail()) {
				fin.eof();
				cout << "enter only digits" << endl;
				return 0;
			}
		}
	}
	return readMatr;
}

int* size_matr(const char* NAME) {
	int* res = new int[2];
	res[0] = 1;
	res[1] = 1;
	ifstream fin(NAME);
	if (!fin) {
		res[0] = -1;
		fin.eof();
		return res;
	}
	if (fin.eof()) {
		res[0] = -2;
		fin.eof();
		return res;
	}
	if (fin.good()) {
		char buff;
		while (!fin.eof()) {
			buff = fin.get();
			if (buff == SPACE and res[0] == 1) {
				res[1]++;
			}
			if (buff == ENDL) {
				res[0]++;
			}
		}
	}
	fin.close();
	//cout << res[0] << endl << res[1];
	return res;
}
void print_matr(int** matr, int* sizem) {
	for (int i = 0; i < sizem[0]; ++i) {
		for (int j = 0; j < sizem[1]; ++i) {
			cout << matr[i][j];
		}
	}
}

int** write_matr_from_consol(int* sizem) {
	int** Matrix = new int* [sizem[0]];
	cout << "enter matrix:\n";
	for (int i = 0; i < sizem[0]; ++i) {
		Matrix[i] = new int[sizem[1]];
		for (int j = 0; j < sizem[1]; ++j) {
			cin >> Matrix[i][j];
		}
	}
	return Matrix;
}
int* size_matr_cons() {
	int* sizem = new int[2];
	cout << "enter matrix size: \n";
	cin >> sizem[0] >> sizem[1];
	return sizem;
}

int task1(int** matr, int* sizem) {
	int str = 0;
	for (int i = 0; i < sizem[0]; ++i) {
		str++;
		for (int j = 0; j < sizem[1]; ++j) {
			if (matr[i][j] % 2 == 0) {
				str--;// если находим строку с четным числом, то уменьшаем счетчик
				break;
			}

		}
	}
	return str;
}

int* task2(int** matr, int* sizem) {
	int* answer = new int[2];
	answer[0] = 0;
	for (int i = 0; i < sizem[0]; ++i) {
		for (int j = 0; j < sizem[1]; ++j) {
			int repeat = -1;//счетчик количства повторов для текущей переменной
			for (int n = 0; n < sizem[0]; ++n) {
				for (int m = 0; m < sizem[1]; ++m) {
					if (matr[n][m] == matr[i][j]) {
						repeat++;// при нахождении повтора переменной, увеличиваем счетчик

					}
				}
			}
			if ((repeat > 0 and matr[i][j] >= answer[1] and answer[0] == 1) or (answer[0] == 0 and repeat > 0)) {//сравнение с предыдущей максимальной переменной, при наличии повторов
				answer[1] = matr[i][j];
				answer[0] = 1;
			}
		}
	}
	return answer;
}