#include<iostream>
#include<Windows.h>
#include<string>
#include"gra.h"
using namespace std;

int main() {	//funkcja z menu i obs³ug¹ menu

	SetConsoleTitle(L"\u265F Szachy");
	string wybor{};
	while (true) {
		cout << "Szachy\n";
		cout << "1. Rozpocznij gr\251\n";
		cout << "2. Wczytaj gr\251\n";
		cout << "3. Przegl\245daj gr\251\n";
		cout << "4. Pomoc\n";
		cout << "5. Wyjd\253\n";
		cout << "Wybierz cyfr\251 z zakresu od 1 do 5: ";
		cin >> wybor;
		system("cls");
		if (wybor == "1") {
			gra(1, "");
		}
		else if (wybor == "2") {
			string plik;
			cout << "Wpisz nazw\251 pliku: ";
			cin >> plik;
			system("cls");
			gra(2, plik);
		}
		else if (wybor == "3") {
			string plik;
			cout << "Wpisz nazw\251 pliku: ";
			cin >> plik;
			system("cls");
			gra(3, plik);
		}
		else if (wybor == "4") {
			pomoc();
			system("cls");
		}
		else if (wybor == "5") {
			return 0;
		}
	}
}