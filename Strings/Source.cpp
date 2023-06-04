#include <iostream>
#include <Windows.h>

int StringLength(const char* str);
char* To_Lower(char* str);
char* To_Upper(char* str);
int SizeWithoutSpaces(char* str);
int SizeWithoutExcessSpaces(char* str);
char* Shrink(char* str);
char* Del_Spaces(char* str);
bool Is_Palindrome(char* str);
bool Is_Int_Number(char* str);
int To_Int_Number(char* str);
using namespace std;
void main() {
	setlocale(LC_ALL, "");

	/*char str[] = "Hello";
	cout << str << endl;*/

	const int SIZE = 256;
	char str[SIZE] = {};

	cout << "Введите строку: " << endl;

	SetConsoleCP(1251);
	
	cin.getline(str, SIZE);

	cout << str << endl;
	cout << StringLength(str) << endl;
	cout << To_Lower(str) << endl;
	cout << To_Upper(str) << endl;

	char str1[] = "Хорошо        живет    на   свете      Винни    Пух";

	cout << Shrink(str1) << endl;
	cout << Is_Palindrome(str) << endl;
	cout << Is_Int_Number(str) << endl;

	int result = To_Int_Number(str);

	cout << result << endl;
	
}
int StringLength(const char* str) {
	int i = 0;
	while (str[i]) {
		i++;
	}
	return i;
	
}
char* To_Lower(char* str){
	for(int i = 0; str[i]; i++){
		if (*(str + i) >= 'A' && *(str + i) <= 'Z') {
			*(str + i) += 32;
		}
		if(*(str + i) >= 'А' && *(str + i) <= 'Я'){
			*(str + i) += 32;
		}
		if (*(str + i) == 'Ё') {
			*(str + i) += 16;
		}
	}
	return str;
}
char* To_Upper(char* str) {
	for (int i = 0; str[i]; i++) {
		if (*(str + i) >= 'a' && *(str + i) <= 'z') {
			*(str + i) -= 32;
		}
		if (*(str + i) >= 'а' && *(str + i) <= 'я') {
			*(str + i) -= 32;
		}
		if (*(str + i) == 'ё') {
			*(str + i) -= 16;
		}
	}
	return str;
}
int SizeWithoutSpaces(char* str) {
	int count = 0;
	int length = StringLength(str);
	for (int i = 0; str[i]; i++) {
		if (*(str + i) == ' ') {
			count++;
		}
	}
	int size = length - count;
	return size;
}
int SizeWithoutExcessSpaces(char* str){
	int count = 0;
	int length = StringLength(str);
	for (int i = 0; str[i]; i++) {
		if (*(str + i - 1) == ' ' && *(str + i) == ' ') {
			count++;
		}
	}
	int size = length - count;
	return size;
}
char* Shrink(char* str) {
	int size = SizeWithoutExcessSpaces(str);
	char* buffer = new char[size];
	for (int i = 0, j = 0; j <= size; i++) {
		if (*(str + i - 1) != ' '|| *(str + i) != ' ') {
			buffer[j] = str[i];
			j++;
		}
	}
	return buffer;
}
char* Del_Spaces(char* str) {
	int size = SizeWithoutSpaces(str);
	char* buffer = new char[size];
	for (int i = 0, j = 0; j <= size; i++) {
		if (*(str + i) != ' ') {
			buffer[j] = str[i];
			j++;
		}
	}
	return buffer;
}
bool Is_Palindrome(char* str){
	str = To_Lower(str);
	str = Del_Spaces(str);
	int length = StringLength(str);
	for (int i = 0; str[i]; i++) {
		if (str[i] != str[length - 1 - i]) {
			return false;
		}
	}
	return true;
}
bool Is_Int_Number(char* str) {
	str = Del_Spaces(str);
	for (int i = 0; str[i]; i++) {
		if (str[i] < 48 || str[i] > 57) {
			return false;
		}
	}
	return true;
}
int To_Int_Number(char* str) {
	str = Del_Spaces(str);
	int length = StringLength(str);
	int result = 0;
	if (Is_Int_Number(str)) {
		for (int i = 0, j = 1; i < length; i++) {
			result += (str[length - 1 - i] - '0') * j;
			j *= 10;
		}
	}
	else cout << "Строка не является числом функция вернет: 0" << endl;
	return result;
}