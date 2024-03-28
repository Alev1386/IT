#include <iostream>
#include <fstream>
using namespace std;
////////////////var//////////////
const int MAX_SIZE_A = 4;
const int MAX_SIZE_B = 3;
const char* FNAME = "test.txt";

int matrix[MAX_SIZE_A][MAX_SIZE_B];

void print_matrix(int a[MAX_SIZE_A][MAX_SIZE_B]);
void read_console(int a[MAX_SIZE_A][MAX_SIZE_B]);
int read_file(int a[MAX_SIZE_A][MAX_SIZE_B], const char* NAME);

int main() {
	int option;
	cin >> option;
	if (option == 1)
	{
		if (!read_file(matrix,FNAME)) {
			return -1;
		}
	}
	else {
		read_console(matrix);
	}
	print_matrix(matrix);
}

void print_matrix(int a[MAX_SIZE_A][MAX_SIZE_B]) {
	for (int i = 0; i < MAX_SIZE_A; i++)
	{
		for (int j = 0; j < MAX_SIZE_B; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
void read_console(int a[MAX_SIZE_A][MAX_SIZE_B]) {
	for (int i = 0; i < MAX_SIZE_A; i++)
	{
		for (int j = 0; j < MAX_SIZE_B; j++)
		{
			cin >> matrix[i][j];
		}
	}
}
int read_file(int a[MAX_SIZE_A][MAX_SIZE_B],const char* NAME) {
	ifstream fin(NAME);//Îןנוהוכÿול פאיכ
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
	for (int i = 0; i < MAX_SIZE_A; i++)
	{
		for (int j = 0; j < MAX_SIZE_B; j++)
		{
			fin >> a[i][j];
		}
	}
	fin.close();
	return 1;
}