#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

using namespace std;

int StringLength(const char* str);
char* To_Lower(char* str);
char* To_Upper(char* str);
char* Shrink(char* str);
char* RemoveSymbol(char str[], const char symbol);
bool Is_Palindrome(const char* str);
bool Is_Int_Number(const char* str);
int To_Int_Number(const char* str);
bool Is_Hex_Number(const char* str);
int From_Hex_To_Int_Number(const char* str);
bool Is_Bin_Number(const char* str);
int From_Bin_To_Int_Number(const char* str);
//int From_Hex_To_Int_Number2(const char* str);

void main() {
	setlocale(LC_ALL, "");

	const int SIZE = 256;
	char str[SIZE] = {};

	cout << "Введите строку: " << endl;

	SetConsoleCP(1251);
	
	cin.getline(str, SIZE);

	cout << str << endl;
	cout << StringLength(str) << endl;

	char str1[] = "Хорошо        живет    на   свете      Винни    Пух";

	cout << Shrink(str1) << endl;
	cout << "Строка " << (Is_Palindrome(str) == 1? "" : "НЕ " ) << "является палиндромом!" << endl;

	if (Is_Int_Number(str) == 1) {
		cout << "Строка является целым числом и его значение в десятиричной системе исчисления равно: "
			<< To_Int_Number(str) << endl;
	}
	else cout << "Строка не является десятичным числом" << endl;

	if(Is_Hex_Number(str) == 1){
		cout << "Строка является шестнадцатиричным числом и его значение в десятиричной системе исчисления равно: " 
			<< From_Hex_To_Int_Number(str) << endl;
	}else cout << "Строка не является шестнадцатиричным числом" << endl;

	if(Is_Bin_Number(str) == 1){
		cout << "Строка является двоичным числом и его значение в десятиричной системе исчисления равно: " 
			<< From_Bin_To_Int_Number(str) << endl;
	}else cout << "Строка не является двоичным числом" << endl;

	cout << "Введенная строка приведенная к нижнему регистру:\t" << To_Lower(str) << endl;
	cout << "Введенная строка приведенная к верхнему регистру:\t" << To_Upper(str) << endl;
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
char* Shrink(char* str) {
	for (int i = 0; str[i]; i++){
		while(str[i] == ' ' && str[i + 1] == ' '){
			for(int j = i + 1; str[j]; j++){
				str[j] = str[j + 1];
			}
		}
	}
	while(str[0] == ' '){
		for(int i = 0; str[i]; i++){
			str[i] = str[i + 1];
		}
	}
	return str;
}
char* RemoveSymbol(char str[], const char symbol){
	for (int i = 0; str[i]; i++) {
		while (str[i] == symbol) {
			for (int j = i; str[j]; j++) {
				str[j] = str[j + 1];
			}
		}
	}
	return str;
}
bool Is_Palindrome(const char* str){
	int length = StringLength(str);
	char* buffer = new char[length + 1] {};
	strcpy(buffer, str);
	RemoveSymbol(buffer, ' ');
	To_Lower(buffer);
	length = StringLength(buffer);
	for (int i = 0; buffer[i]; i++) {
		if (buffer[i] != buffer[length - 1 - i]) {
			delete buffer;
			return false;
		}
	}
	delete buffer;
	return true;
}
bool Is_Int_Number(const char* str) {
	for (int i = 0; str[i]; i++) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return true;
}
int To_Int_Number(const char* str) {
	int length = StringLength(str);
	int result = 0;
	if (Is_Int_Number(str)) {
		for (int i = 0, j = 1; i < length; i++) {
			result += (str[length - 1 - i] - '0') * j;
			j *= 10;
		}
	}
	return result;
}bool Is_Hex_Number(const char* str) { 
	int length = StringLength(str);
	char* buffer = new char[length + 1] {};
	strcpy(buffer, str);
	if (buffer[0] == '0' && buffer[1] == 'x') { //Чтобы не было путаницы является ли например число 101 десятичным или
		To_Upper(buffer);						// шестнадцатиричным обяжем писать шестнадцатиричные числа в виде 0x101
		for (int i = 2; buffer[i]; i++) {
			if (buffer[i] < '0' || buffer[i] > 'F') return false;
			if (buffer[i] > 57 && buffer[i] < 65) return false;
		}
	}
	else return false;
	delete[] buffer;
	return true;
}
int Hex_Symbol_To_Integer(const char symbol){
	int result = 0;
	for (char i = '0'; i <= '9'; i++) {
		if (i == symbol) return result;
		result++;
	}
	result = 10;
	for (char i = 'A'; i <= 'F'; i++){
		if (i == symbol) return result;
		result++;
	}
	return 0;
}

int From_Hex_To_Int_Number(const char* str) {
	int length = StringLength(str);
	int result = 0;
	if (Is_Hex_Number(str)) {
		char* buffer = new char[length + 1] {};
		strcpy(buffer, str);
		To_Upper(buffer);
		int i = 0;
		int j = 1;
		while(buffer[length - i - 1] != 'X'){
			result += Hex_Symbol_To_Integer(buffer[length - i - 1])* j;
			j *= 16;
			i++;
		}
		delete[] buffer;
	}
	return result;
}
bool Is_Bin_Number(const char* str){
	int length = StringLength(str);
	if (str[0] == '0' && str[1] == 'b') { //Чтобы не было путаницы является ли например число 101 десятичным или
		for (int i = 2; str[i]; i++) {    // шестнадцатиричным обяжем писать шестнадцатиричные числа в виде 0b101
			if (str[i] < '0' || str[i] > '1') return false;
		}
	}
	else return false;
	return true;
}
int From_Bin_To_Int_Number(const char* str){
	int length = StringLength(str);
	int result = 0;
	if(Is_Bin_Number(str)){
		int i = 0;
		int j = 1;
		while (str[length - i - 1] != 'b') {
			result += (str[length - i - 1] - '0') * j;
			j *= 2;
			i++;
		}
	}
	return result;
}
//int From_Hex_To_Int_Number2(const char* str) {
//	int length = StringLength(str);
//	int result = 0;
//	if (Is_Hex_Number(str)) {
//		char* buffer = new char[length + 1] {};
//		strcpy(buffer, str);
//		To_Upper(buffer);
//		int i = 0;
//		int k = 1;
//		while (buffer[length - i - 1] != 'x') {
//			int number = 0;
//			for (char j = '0'; j <= '9'; j++) {
//				if (buffer[length - i - 1] == j) {
//					result += number * k;
//					k *= 16;
//				}else number++;
//			}
//			number = 10;
//			for (char j = 'A'; j <= 'F'; j++) {
//				if (buffer[length - i - 1] == j) {
//					result += number * k;
//					k *= 16;
//				}else number++;
//			}
//			i++;
//		}
//		delete[] buffer;
//	}
//	return result;
//}