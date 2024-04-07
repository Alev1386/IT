#include <iostream>     //стандартные потоки ввода/вывода
#include <fstream>		//файловые потоки ввода/вывода
using namespace std;
/////////////////////////////////define/////////////////////////
#define SPACE 32//Код пробела
#define ENDL 10//Код перехода на новую строку

const char* FNAME = "Test1.txt";//тестовый файл


////////////////////////////////////////////vars/////////////////////////////////
int sizem = 0;//количество символов в файле
char* arr = new char[sizem];//Массив хранящий все данные из файла
int newline[2] = { 0,0 };//Порядковые номера символов перехода на новую строку

int str1[255];//Счётчик количества символов по каждому символу таблицы ASCII 
int str2[255];//Счётчик количества символов по каждому символу таблицы ASCII 

int wordInFirstStr = 0;//Повторы заданного слова в первой строке
int wordInSecondStr = 0;//Повторы заданного слова во второй строке
int lenCounter = 0;//Переменная для прохода по слову из первой строки


//////////////////////////////Prorots//////////////////////////////////////
void resize_arr();
int get_option();
int read_file(const char* NAME, char* file);
int read_console(char* file);





//////////////////////////////MAIN/////////////////////////////////////////////
int main() {
	for (int i = 0; i < 255; i++)//Зануляем все элементы массивов
	{
		str1[i] = 0;
		str2[i] = 0;
	}
	if (get_option() == 1)
	{
		switch (read_file(FNAME, arr))
		{
		case -1:
			cout << "File " << FNAME << " is not found\n";
			return -1;
		case -2:
			cout << "File " << FNAME << " is empty\n";
			return -1;
		case -3:
			cout << "Too many strings! Only 3 must be included!" << endl;
			return -1;
		case -4:
			cout << "Only 1 word must be included in 1st string!" << endl;
			return -1;
		default:
			cout << "Reading ended!" << endl;
			break;
		}
	}
	else {
		cin.get();
		for (int i = 0; i < 3; i++)
		{
			int flag = 0;
			cout << "Enter " << i + 1 << " string." << endl;
			while (arr[sizem - 1]!='\n' or flag==0) {
				flag = 1;
				resize_arr();
				arr[sizem - 1] = cin.get();//Дописываем в только что созданную ячейку массива новый символ из файла

				if (int(arr[sizem - 1]) == SPACE and newline[0] == 0) {//Проверка на 1 слово в первой строке
					cout << "Only 1 word must be included in 1st string!" << endl;
					return -1;
				}
			}
			if (i == 0) {//Первая метка перехода на новую строку
				newline[0] = sizem - 1;
			}
			else if (i == 1)//Вторая метка перехода на новую строку
			{
				newline[1] = sizem - 1;
			}
		}
		cout << "Reading ended!" << endl;
	}
	

	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	//                                                  1 Печать сведений о совпадающих в заданных строках символах                                         //
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	for (int i = newline[0] + 1; i < newline[1]; i++)//Считаем символы в первой строке
	{
		str1[int(arr[i])]++;
	}
	for (int i = newline[1] + 1; i < sizem; i++)//Считаем символы во второй строке
	{
		str2[int(arr[i])]++;
	}
	cout << endl << endl << "The answer for the first issue:" << endl;
	for (int i = 0; i < 255; i++)//Выводим повторы сиволов
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
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	//                                                  2 Выявление строки, в которой заданное слово встречается чаще                                       //
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	int wordlen = newline[0];//Длина слова из первой строки
	char* word = new char[wordlen];//Слово из первой строки
	if (wordlen == 0)
	{
		cout << endl << "No word entered in first string" << endl;
		return 0;
	}
	for (int i = 0; i < wordlen; i++)//Запись первой строки в более удобный для работы вид
	{
		word[i] = arr[i];
	}

	for (int i = newline[0] + 1; i < newline[1]; i++)//Ищем слово в первой строке
	{
		if (arr[i] == word[lenCounter]) {//Проверяем по одной букве на совпадение со словом
			lenCounter++;
		}
		else//Буква не совпала. Обнуляем счётчик
		{
			lenCounter = 0;
		}
		if (lenCounter == wordlen) {//Совпали все буквы из слова. Отмечаем, что нашли слово в строке и обнуляем счётчик 
			wordInFirstStr++;
			lenCounter = 0;
		}
	}
	for (int i = newline[1] + 1; i < sizem; i++)//Ищем слово во второй строке
	{
		if (arr[i] == word[lenCounter]) {//Проверяем по одной букве на совпадение со словом
			lenCounter++;
		}
		else//Буква не совпала. Обнуляем счётчик
		{
			lenCounter = 0;
		}
		if (lenCounter == wordlen) {//Совпали все буквы из слова. Отмечаем, что нашли слово в строке и обнуляем счётчик 
			wordInSecondStr++;
			lenCounter = 0;
		}
	}
	cout << endl << endl << "The answer for the second issue:" << endl;
	cout << "The word is: ";
	for (int i = 0; i < wordlen; i++)
	{
		cout << word[i];
	}
	cout << endl << "It meets " << wordInFirstStr << " times at first string!" << endl;
	cout << "It meets " << wordInSecondStr << " times at second string!" << endl;
	
	if (wordInFirstStr>wordInSecondStr)
	{
		cout << "Word meets more frequent at first string!" << endl;
	}else if (wordInSecondStr > wordInFirstStr)
	{
		cout << "Word meets more frequent at second string!" << endl;
	}
	else
	{
		cout << "Word meets more same times at both strings!" << endl;
	}

}//main


////////////////////////////////////////////Funcs////////////////////////////
void resize_arr() {
	size_t newSize = sizem + 1;
	char* newArr = new char[newSize];
	memcpy(newArr, arr, sizem * sizeof(char));
	sizem = newSize;
	delete[] arr;
	arr = newArr;
}
int get_option() {
	int option;
	cin >> option;
	return option;
}
int read_file(const char* NAME, char* file) {
	//////////////////////////FILE///////////////////////////////////////
	ifstream fin(NAME);//Определяем файл

	/////////EXISTANCE////////////////////////////////////////
	if (!fin)
	{
		fin.close();
		return -1;
	} // end if
	///////////NOT EMPTY//////////////////////////////////
	if (fin.eof()) 	//empty
	{
		fin.close();
		return -2;
	} // end if

	/////////////////////////READ/////////////////////////
	if (fin.good())
	{
		while (!fin.eof()) {
			resize_arr();
			arr[sizem - 1] = fin.get();//Дописываем в только что созданную ячейку массива новый символ из файла
			if (int(arr[sizem - 1]) == ENDL)
			{
				if (newline[0] == 0) {//Первая метка перехода на новую строку
					newline[0] = sizem - 1;
				}
				else if (newline[1] == 0)//Вторая метка перехода на новую строку
				{
					newline[1] = sizem - 1;
				}
				else {//Появился 3й переход на новую строку
					return -3;
				}
			}
			if (int(arr[sizem - 1]) == SPACE and newline[0] == 0) {//Проверка на 1 слово в первой строке
				return -4;
			}
		}
		fin.close();
	}
	return 0;
}
int read_console(char* file) {
	cin.get();
	for (int i = 0; i < 3; i++)
	{
		int flag = 0;
		cout << "Enter " << i + 1 << " string." << endl;
		while (arr[sizem - 1] != '\n' or flag == 0) {
			flag = 1;
			resize_arr();
			arr[sizem - 1] = cin.get();//Дописываем в только что созданную ячейку массива новый символ из файла

			if (int(arr[sizem - 1]) == SPACE and newline[0] == 0) {//Проверка на 1 слово в первой строке
				cout << "Only 1 word must be included in 1st string!" << endl;
				return -1;
			}
		}
		if (i == 0) {//Первая метка перехода на новую строку
			newline[0] = sizem - 1;
		}
		else if (i == 1)//Вторая метка перехода на новую строку
		{
			newline[1] = sizem - 1;
		}
	}
}