#include <iostream>     //стандартные потоки ввода/вывода
#include <fstream>		//файловые потоки ввода/вывода
using namespace std;

const char* FNAME = "Test1.txt";
/////32 - space
/////10 - endl

////////////////////////////////////////////vars/////////////////////////////////
int sizem = 0;
char* arr = new char[sizem];
int newline[2] = { 0,0 };

int str1[255];
int str2[255];


//////////////////////////////Prorots//////////////////////////////////////
void resize_arr();
void first();






//////////////////////////////MAIN/////////////////////////////////////////////
int main() {
	cout << str1[100] << endl;
	for (int i = 0; i < 255; i++)
	{
		str1[i] = 0;
		str2[i] = 0;
	}
	//////////////////////////FILE///////////////////////////////////////
	ifstream fin(FNAME);
	/////////EXIST////////////////////////////////////////
	if (!fin)
	{
		cout << "File " << FNAME << " is not found\n";
		fin.close();
		system("pause");
		return 1;
	} // end if
	///////////NOT EMPTY//////////////////////////////////
	if (fin.eof()) 	//empty
	{
		cout << "File " << FNAME << " is empty\n";
		fin.close();
		system("pause");
		return 1;
	} // end if
	/////////////////////////READ/////////////////////////
	if (fin.good())
	{
		while (!fin.eof()) {
			resize_arr();
			arr[sizem - 1] = fin.get();
			if (int(arr[sizem - 1]) == 10)
			{
				if (newline[0] == 0) {
					newline[0] = sizem - 1;
				}
				else if (newline[1] == 0)
				{
					newline[1] = sizem - 1;
				}
				else {
					cout << "Too many strings! Only 3 must be included!" << endl;
					return 0;
				}
			}
			if (int(arr[sizem - 1]) == 32 and newline[0] == 0) {
				cout << "Only 1 word must be included in 1st string!" << endl;
				return 0;
			}
		}
		cout << "Reading ended!" << endl;
		fin.close();
	}
	//for (int i = 0; i < sizem; i++)
	//{
	//	cout << arr[i];

	//}
	//cout << endl;

	//////////////////////////////////FirstIssue/////////////////////////////////////////////
	for (int i = newline[0] + 1; i < newline[1]; i++)
	{
		str1[int(arr[i])]++;
	}
	for (int i = newline[1] + 1; i < sizem; i++)
	{
		str2[int(arr[i])]++;
	}
	for (int i = 0; i < 255; i++)
	{
		if (str1[i] != 0 and str2[i] != 0) {
			int k;
			if (str1[i] < str2[i]) {
				k = str1[i];
			}
			else {
				k = str2[i];
			}
			cout << "Symbol <" << char(i) << "> repeats " << k << " times." << endl;
		}
	}
	//////////////////////SecondIssue//////////////////////////////////////////////
	//char w[newline[0]];
	//hi

}


////////////////////////////////////////////Funcs////////////////////////////
void resize_arr() {
	size_t newSize = sizem + 1;
	char* newArr = new char[newSize];
	memcpy(newArr, arr, sizem * sizeof(char));
	sizem = newSize;
	delete[] arr;
	arr = newArr;
}