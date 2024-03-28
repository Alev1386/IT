#include <iostream>
#include <fstream>		//�������� ������ �����/������
#include <cmath>
using namespace std;

#define SPACE 32//��� �������
#define ENDL 10//��� �������� �� ����� ������

const char* FNAME = "matrix.txt";

int* params1;
/////////////////prots///////////////////////////////
int** create_matrix(int *params);//�������� �������
int** get_matrix_from_console();//��������� ������� �� �������
int* get_params();//������ ���������� ������� � �������
int** get_matrix_from_file(const char *NAME);//������ ������� �� �����
int* check_params(const char* NAME);//�������� ���������� ������� � �����
int multyply_elements_in_row(int** matrix, int* params,int currentr);//������������ ��������� ������
void print_matrix(int** matrix, int* params);//����� �������
bool set_option();

int main() {
	setlocale(LC_ALL, "rus");
	int** matrix;
	if (set_option() == 0)
	{
		cout << "���� ����� �������" << endl;
		matrix = get_matrix_from_console();
	}
	else
	{
		cout << "���� ����� ����" << endl;
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
			cout << "������������ ��������� � <" << i+1 << "> ������ ����� <" << mult<<"> \n";
			if (mult > max_mult) {
				max_mult = mult;
			}
		}
	}
	cout << "������������ ������������ �� ������ = " << max_mult << endl;

	delete[] matrix;
}

///////////////////funcs///////////////////////////////////
int** create_matrix(int *params) {//� ������� ��������� ������ �� 2 �������� (����� ����� � ����� ��������)
	int** result = new int* [params[0]];//��������� ������
	for (int i = 0; i < params[0]; i++) {//����� ������ �� �������
		result[i] = new int[params[1]];
	}
	return result;
}
int** get_matrix_from_console() {
	int* params = get_params();//������������ � ������������ ��������� �������
	params1 = params;
	int** matrix = create_matrix(params);//������ ������ �������
	for (int i = 0; i < params[0]; ++i)//����������� ������� � ������������
	{
		for (int j = 0; j < params[1]; ++j) {
			cout << "������� ������� � �������� :(" << i+1 << "," << j+1 << ") :";
			cin >> matrix[i][j];
			if (cin.fail()) {
				cout << "������! ������ ������� ������ ��������� ����� �����!" << endl;
				return 0;
			}
			cout << matrix[i][j] << endl;
		}
	}
	return matrix;
}
int* get_params() {
	int* params = new int[2];
	cout << "������� ����� �����" << endl;
	cin >> params[0];
	cout << params[0] << endl;
	if (params[0] <= 0 )
	{
		cout << "���������� ����� ������ ���� ����������� ������" << endl;
		return 0;
	}
	cout << "������� ����� ��������" << endl;
	cin >> params[1];
	cout << params[1] << endl;
	if (params[1] <= 0)
	{
		cout << "���������� �������� ������ ���� ����������� ������" << endl;
		return 0;
	}
	return params;
}
int** get_matrix_from_file(const char* NAME) {
	ifstream fin(NAME); //��������� ����
	int* params = check_params(NAME);
	int** arr; //�������
	arr = new int* [params[0]]; //�������������
	for (int i = 0; i < params[0]; i++) //�������
	{
		arr[i] = new int[params[1]];
		for (int j = 0; j < params[1]; j++) //������ ���������
			fin >> arr[i][j];
		if (fin.fail())
		{
			cout << "������! ������ ����� ������ ����������� � �����!" << endl;
			return 0;
		}
	}
	cout << "������ ����� ��������!" << endl;
	fin.close(); //��������� ����
	return arr;
}
int* check_params(const char* NAME) {
	ifstream fin(NAME);//���������� ����
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
	cout << "\n�������� �������: \n";
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
	cout << "�������� ������ ����� �������: \n 1.����� ������� \n 2. ����� ����" << endl;
	int option;
	cin >> option;
	return option - 1;
}
