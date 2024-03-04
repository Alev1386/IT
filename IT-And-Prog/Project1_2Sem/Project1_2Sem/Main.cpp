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





//////////////////////////////MAIN/////////////////////////////////////////////
int main() {
	for (int i = 0; i < 255; i++)//Зануляем все элементы массивов
	{
		str1[i] = 0;
		str2[i] = 0;
	}
	//////////////////////////FILE///////////////////////////////////////
	ifstream fin(FNAME);//Определяем файл

	/////////EXISTANCE////////////////////////////////////////
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
					cout << "Too many strings! Only 3 must be included!" << endl;
					return 0;
				}
			}
			if (int(arr[sizem - 1]) == SPACE and newline[0] == 0) {//Проверка на 1 слово в первой строке
				cout << "Only 1 word must be included in 1st string!" << endl;
				return 0;
			}
		}
		cout << "Reading ended!" << endl;
		fin.close();
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
	const int wordlen = newline[0];//Длина слова из первой строки
	char* word = new char[wordlen];//Слово из первой строки

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