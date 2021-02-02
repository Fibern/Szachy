#include<iostream>
#include<iomanip>
#include<string>
#include<Windows.h>
//#include<fcntl.h>		//biblioteki służą do wyświetlania figur na planszy więcej info w funkcji wypiszPlansze()
//#include<io.h>
#include<fstream>
#include"pomocnicza.h"
#include"ruchy.h"
#include"gra.h"

using namespace std;

struct plansze	//struktura planszy
{
	int p[8][8]{};
	plansze* kolejna{};
	void wyswietl(); //funkcja wyświetlająca planszę
};
using Plansze = plansze*;

void plansze::wyswietl()
{
	wyswietlPlansze(p);
}

struct ListaPlansz	//struktura z listą plansz
{
	Plansze pierwsza{};
	void dodaj(int a[8][8]);	//funkcja dodająca do listy plansz
	void wyswietlPlansze(int nr);	//funkcja wyświetlająca planszę o danym numerze
	bool porownaj(int plansza[8][8]);	//funkcja porównująca plansze szukająca 3 powtórzeń
};

void ListaPlansz::dodaj(int a[8][8])
{

	Plansze nowa = new plansze;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			nowa->p[i][j] = a[i][j];
		}
	}

	if (pierwsza == nullptr)
	{
		pierwsza = nowa;
	}

	else
	{
		Plansze biezaca = pierwsza;
		while (biezaca->kolejna != nullptr)
			biezaca = biezaca->kolejna;
		biezaca->kolejna = nowa;
	}
}

void ListaPlansz::wyswietlPlansze(int nr)
{

	int i = 0;
	Plansze biezaca = pierwsza;
	while (biezaca != nullptr)
	{
		if (i == nr) {
			biezaca->wyswietl();
		}
		biezaca = biezaca->kolejna;
		i++;
	}
}

bool ListaPlansz::porownaj(int plansza[8][8])
{
	int licznik = 0, licznik2 = 0;
	Plansze biezaca = pierwsza;
	while (biezaca != nullptr)
	{
		licznik = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (biezaca->p[i][j] == plansza[i][j])
					licznik++;
			}
		}
		if (licznik == 64)
			licznik2++;
		biezaca = biezaca->kolejna;
	}
	if (licznik2 >= 3) {
		return 1;
	}
	return 0;
}

void ruchy(string ruch, int plansza[8][8], int pomocnicza[8][8], bool kolor, int licznik50[1], ListaPlansz powtorzenia, string sprawdz[3]);
void przegladanie(ListaPlansz powtorzenia, int licznik, string* gra);

void gra(int tryb, string partia) {		
	//główna funkcja gry w zależności od podanego trybu i nazwy pliku decyduje lub też wpisywanych ruchów w przypadku uruchomienia gry
	//czy uruchomić grę, albo przeglądanie gry oraz czy zakończyć grę
	int plansza[8][8] = { {-1, -2, -3, -4, -5, -3, -2, -1},
					{-6, -6, -6, -6, -6, -6, -6, -6},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{0, 0, 0, 0, 0, 0, 0, 0},
					{6, 6, 6, 6, 6, 6, 6, 6},
					{1, 2, 3, 4, 5, 3, 2, 1} };

	int pomocnicza[8][8]{ {2048, 0, 0, 0, 2048, 0, 0, 2048},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{0, 0, 0, 0, 0, 0, 0, 0},
						{2048, 0, 0, 0, 2048, 0, 0, 2048} };
	// pomocnicza plansza to na niej badany jest stan gry i czy gra powinna być zakończona czy też nie oraz czy można zrobić roszadę lub zbić w przelocie
	wypelnijPomocnicza(plansza, pomocnicza, 1);
	string gra[500];
	ListaPlansz powtorzenia;
	powtorzenia.pierwsza = nullptr;
	powtorzenia.dodaj(plansza);
	int licznik = 0, licznik50[1] = { 0 };
	string sprawdz[3]{};
	string ruch{}, stan{}, info{};
	bool koniecGry = 0, szach = 0, kolor = 1, wyjdz = 0;
	int wartosc{};
	string ruchRemis = "1/2-1/2", ruchBiale = "1-0", ruchCzarne = "0-1";

	if (tryb == 2 || tryb == 3) {
		if (!wczytanie(partia, gra))
			return;
		while (gra[licznik] != "" && !koniecGry) {
			if (gra[licznik] == ruchRemis || gra[licznik] == ruchBiale || gra[licznik] == ruchCzarne) {
				koniecGry = 1;
				continue;
			}
			ruchy(gra[licznik], plansza, pomocnicza, kolor, licznik50, powtorzenia, sprawdz);
			stan = sprawdz[0];
			ruch = sprawdz[1];
			info = sprawdz[2];

			licznik++;
			kolor = !kolor;
			if (stan == "blad") {
				cout << "blad ruch " << (double)licznik / 2 + 0.5 << ruch;
				return;
			}
			else if (stan == "remis" || stan == "pat" || stan == "mat") {
				koniecGry = 1;
			}
		}
	}

	if (tryb == 3) {
		przegladanie(powtorzenia, licznik, gra);
		return;
	}
	ruch = "";
	stan = "";
	info = "";
	while (!wyjdz) {
		//wyswietl(pomocnicza);
		wyswietlRuchy(gra, licznik);
		wyswietlPlansze(plansza);
		if (stan == "blad")
			cout << "ruch: " << ruch << " jest b\210\251dny\n";
		if (koniecGry) {
			cout << "Wpisz: \n1. by wyj\230\206 \n2. by zapisa\206 parti\251 i wyj\230\206:\n";
			cin >> ruch;
			if (ruch == "1") {
				system("cls");
				return;
			}
			else if (ruch == "2") {
				ruch = "zapisz";
			}
			else {
				system("cls");
				continue;
			}
		}
		else {
			cout << "ruch " << ((kolor) ? "bia\210ych: " : "czarnych: ");
			cin >> ruch;
			system("cls");
		}
		if (ruch == "wyjd\253" || ruch == "wyjdz") {
			system("cls");
			koniecGry = 1;
		}
		else if (ruch == "zapisz") {
			bool zapisano = 0;
			while (!zapisano) {
				string plik{};
				cout << "Podaj nazw\251 pliku: ";
				cin >> plik;
				system("cls");
				ruch = "";
				stan = "";
				info = "";
				zapisano = zapiszGre(plik, gra, licznik);
			}
			if (koniecGry) {
				return;
			}
		}
		else if (ruch == "poddaj") {
			koniecGry = !koniecGry;
			if (kolor)
				wpisz(ruchCzarne, gra, licznik);
			else
				wpisz(ruchBiale, gra, licznik);
		}
		else if (ruch == "remis") {
			bool propozycja = 1;
			while (propozycja) {
				string remis{};
				cout << ((kolor) ? "Bia\210e " : "Czarne ") << "proponuja remis czy chcesz przyj\245\206? T/N \n";
				cin >> remis;
				if (remis == "T" || remis == "t") {
					koniecGry = !koniecGry;
					wpisz(ruchRemis, gra, licznik);
					propozycja = !propozycja;
				}
				else if (remis == "N" || remis == "n") {
					propozycja = !propozycja;
				}
				system("cls");
			}
		}
		else {
			ruchy(ruch, plansza, pomocnicza, kolor, licznik50, powtorzenia, sprawdz);
			stan = sprawdz[0];
			ruch = sprawdz[1];
			info = sprawdz[2];

			if (stan == "" || stan == "szach") {
				wpisz(ruch, gra, licznik);
				licznik++;
				kolor = !kolor;						
			}
			else if (stan == "mat") {
				wpisz(ruch, gra, licznik);
				licznik++;
				koniecGry = 1;
				if (kolor)
					wpisz(ruchBiale, gra, licznik + 1);
				else
					wpisz(ruchCzarne, gra, licznik + 1);
			}
			else if (stan == "pat" || stan == "remis") {								
				wpisz(ruch, gra, licznik);
				wpisz(ruchRemis, gra, licznik + 1);
				licznik++;
				koniecGry = 1;
			}

		}
	}

}

void przegladanie(ListaPlansz powtorzenia, int licznik, string* gra) {		//funkcja obsługująca przeglądanie partii
	int numer = 0;
	string wpisz;
	while (true) {
		wyswietlRuchy(numer, gra, licznik);
		powtorzenia.wyswietlPlansze(numer);
		cout << "Wpisz: \n'<' by cofn\245\206 ruch \n'>' by przejs\206 do nast\251nego ruchu\n'wyjdz' by wyj\230\206\n";
		cin >> wpisz;
		system("cls");
		if (wpisz == "wyjdz" || wpisz == "wyjd\253") {
			return;
		}
		else if(wpisz == ">") {
			if(numer < licznik)
				numer += 1;
		}
		else if (wpisz == "<") {
			if(numer > 0)
			numer -= 1;
		}
	}
}

bool wczytanie(string partia, string gra[500]) {	//funkcja wczytująca ruchy z pliku
	ifstream plik(partia);
	string ruch;
	int licznikPlik = 0;
	int licznik = 0;
	if(plik.is_open()) {
		string ruchRemis = "1/2-1/2", ruchBiale = "1-0", ruchCzarne = "0-1";
		while (!plik.eof()) {
			plik >> ruch; 
				if (licznikPlik % 3 != 0 || (ruch == ruchRemis || ruch == ruchBiale || ruch == ruchCzarne)) {
				wpisz(ruch, gra, licznik);
				licznik++;
			}
			licznikPlik++;
		}
		plik.close();
		return 1;
	}
	else {
		cout << "Nie mozna otworzy\206 pliku." << endl;
		return 0;
	}

}

void sprawdzCzyWPrzelocie(int plansza[8][8], int pomocnicza[8][8], int kolor) {  //funkcja usuwająca możliwość bicia w przelocie danego pola po poprawnym ruch przeciwnika
	
	for (int i = 0; i < 8; i++) {
		if (czyWPrzelocie(pomocnicza, 4 - kolor, i)) {
			pomocnicza[4 - kolor][i] -= 1024;
		}
	}
}

bool sprawdzPat(int pomocnicza[8][8], int kolor) {	//funkcja sprawdzająca czy jest pat
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (czyRuch(pomocnicza, i, j, kolor)) {
				return 0;
			}
		}
	}
	return 1;
}

void wyswietl(int pomocnicza[8][8]) {	//funkcja pomocnicza na etapie pisania programu
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << pomocnicza[i][j] << " ";
		}
		cout << endl;
	}
}

bool czyKrolSprawdz(int pomocnicza[8][8], int plansza[8][8], int krolY, int krolX, int y, int x) {	//funkcja sprawdzająca czy król może udać się na dane pole czy dane pole jest pod atakiem 
	int Y = krolY + (krolY - y);
	int X = krolX + (krolX - x);
	if (Y < 0 || Y > 7 || X < 0 || X > 7)
		return 1;
	if (X != 0 && Y != 0 && abs(plansza[Y][X]) == 6)
		return 1;
	if (czySzachowane(pomocnicza, Y, X))
		return 0;
	if (czySzachujaca(pomocnicza, Y, X))
		return 0;
	return 1;
}

bool czyKrol(int plansza[8][8], int pomocnicza[8][8], int kolor) {	//funkcja sprawdzająca czy król może udać się na jakiekolwiek pole
	int pozycja[2];
	pozycjaKrol(plansza, kolor, pozycja);
	int y = pozycja[0];
	int x = pozycja[1];
	for (int i = max(0, y - 1); i <= min(y + 1, 7); i++) {
		for (int j = max(0, x - 1); j <= min(x + 1, 7); j++) {
			if (!czyAtakowane(pomocnicza, i, j, kolor) && (plansza[i][j] * (2 * kolor - 1) <= 0)) {
				if (czyKrolSprawdz(pomocnicza, plansza, y, x, i, j)) {
					return 1;
				}
			}
		}
	}
	return 0;
}

bool czyZaslona(int pomocnicza[8][8], bool kolor) {	
	//funkcja sprawdzająca czy król w przypadku szacha może zostać osłonięty przed szachem przez jedną z figur
	// lub też czy figura szachująca może zostać zbita
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((czySzachowane(pomocnicza, i, j) || czySzachujaca(pomocnicza, i, j)) && czyRuch(pomocnicza, i, j, kolor)) {
				return 1;
			}
		}
	}
	return 0;
}

void wyswietlPlansze(int plansza[8][8]) {		
	//funkcja wyświetla plansze zakomentowana część kodu służy do wyświetlania figur zamiast liter
	//by ją uruchomić należy usunąć komentarze w funkcji oraz biblioteki na górze kodu oraz zakomentować aktualnie nie zakomentowanego switcha
	//by widzieć figury należy zmienić czcionke w konsoli na najlepiej MS Ghotic, który jest domyślnie w Windowsie
	//po takiej zamianie program czasami może wyrzucić błąd
	HANDLE abc = GetStdHandle(STD_OUTPUT_HANDLE);
	// int wartosc;
	for (int i = 0; i < 8; i++) {
		if (i == 0) {
			cout << setw(2) << " " << setw(2) << " " << setw(2) << left << "a" << setw(2) << left << "b" << setw(2) << left << "c" << setw(2) << left << "d" << setw(2) << left << "e" << setw(2) << left << "f" << setw(2) << left << "g" << setw(2) << left << "h" << endl << endl;
		}
		for (int j = 0; j < 8; j++) {
			if (j == 0) {
				cout << setw(2) << 8 - i << setw(2) << " ";
			}
			if ((i + j) % 2 != 0) {											
				if (plansza[i][j] == 0)										
					SetConsoleTextAttribute(abc, 0x88);
				else if (plansza[i][j] > 0)									
					SetConsoleTextAttribute(abc, 0x8F);
				else														
					SetConsoleTextAttribute(abc, 0x80);
			}
			else {															
				if (plansza[i][j] == 0)										
					SetConsoleTextAttribute(abc, 0x77);
				else if (plansza[i][j] < 0)									
					SetConsoleTextAttribute(abc, 0x70);
				else														
					SetConsoleTextAttribute(abc, 0x7F);
			}
			cout << setw(2) << left;
			//wartosc = _setmode(_fileno(stdout), _O_WTEXT);
			//wcout << setw(2) << left;
			/*switch (plansza[i][j]) {
			case -6:
				wcout << L'\u265F';
				break;
			case -5:
				wcout << L'\u265A';
				break;
			case -4:
				wcout << L'\u265B';
				break;
			case -3:
				wcout << L'\u265D';
				break;
			case -2:
				wcout << L'\u265E';
				break;
			case -1:
				wcout << L'\u265C';
				break;
			case 0:
				wcout << "0";
				break;
			case 1:
				wcout << L'\u2656';
				break;
			case 2:
				wcout << L'\u2658';
				break;
			case 3:
				wcout << L'\u2657';
				break;
			case 4:
				wcout << L'\u2655';
				break;
			case 5:
				wcout << L'\u2654';
				break;
			case 6:
				wcout << L'\u2659';
				break;
			}*/
			switch (plansza[i][j]) {
			case -6:
				cout << "P" ;
				break;
			case -5:
				cout << "K";
				break;
			case -4:
				cout << "Q";
				break;
			case -3:
				cout << "B";
				break;
			case -2:
				cout << "N";
				break;
			case -1:
				cout << "R";
				break;
			case 0:
				cout << "0";
				break;
			case 1:
				cout << "R";
				break;
			case 2:
				cout << "N";
				break;
			case 3:
				cout << "B";
				break;
			case 4:
				cout << "Q";
				break;
			case 5:
				cout << "K";
				break;
			case 6:
				cout << "P";
				break;
			}
			//wartosc = _setmode(_fileno(stdout), _O_TEXT);
			if (j == 7) {
				SetConsoleTextAttribute(abc, 0x00);
				cout << 0;
			}
		}
		SetConsoleTextAttribute(abc, 15);
		cout << endl;
	}

}

bool zapiszGre(string nazwapliku, string gra[500], int licznik) {		//funkcja zapisująca ruchy gry do pliku
	ofstream plik(nazwapliku);
	if (plik.is_open()) {
		string ruchRemis = "1/2-1/2", ruchBiale = "1-0", ruchCzarne = "0-1";
		for (int i = 0; i < licznik; i++) {
			if (i % 2 == 0) {
				plik  << " " << to_string((i + 2) / 2) + ".";
			}
			plik << " " << gra[i];
		}
		if (gra[licznik] == ruchRemis || gra[licznik] == ruchBiale || gra[licznik] == ruchCzarne)
			plik << " " << gra[licznik];
		else if (gra[licznik + 1] == ruchRemis || gra[licznik + 1] == ruchBiale || gra[licznik + 1] == ruchCzarne)
			plik << " " << gra[licznik + 1];
		plik.close();
		return 1;
	}
	else {
		cout << "Nie uda\210o si\251 zapisa\206 spr\242buj ponownie." << endl;
		return 0;
	}
}

void wyswietlRuchy(string* gra, int licznik) {		//funkcja wyświetlająca ruchy
	string ruchRemis = "1/2-1/2", ruchBiale = "1-0", ruchCzarne = "0-1";
	if (gra[0] == "")
		return;
	int i = 0;
	cout << "Ruchy:";
	for (int i = 0; i < licznik; i++) {
		if (i % 6 == 0) {
			cout << endl;
		}
		if (i % 2 == 0) {
			cout << setw(4) << left << to_string((i + 2) / 2) + ".";
		}
		cout << setw(8) << left << gra[i];
	}
	if (gra[licznik] == ruchRemis)
		cout << endl << ruchRemis << " remis";
	else if (gra[licznik] == ruchBiale)
		cout << endl << ruchBiale << " wygrana bia\210ych";
	else if (gra[licznik] == ruchCzarne)
		cout << endl << ruchCzarne << " wygrana czarnych";
	if (gra[licznik + 1] == ruchRemis)
		cout << endl << ruchRemis << " remis";
	else if (gra[licznik + 1] == ruchBiale)
		cout << endl << ruchBiale << " wygrana bia\210ych";
	else if (gra[licznik + 1] == ruchCzarne)
		cout << endl << ruchCzarne << " wygrana czarnych";

	cout << endl << endl << endl;
}

void wyswietlRuchy(int numer, string* gra, int licznik) {	//funkcja wyświetlająca ruchy podczas przeglądania zaznacza ruch, w którym aktualnie znajduje się obserwator
	HANDLE abc = GetStdHandle(STD_OUTPUT_HANDLE);
	string ruchRemis = "1/2-1/2", ruchBiale = "1-0", ruchCzarne = "0-1";
	if (gra[0] == "")
		return;
	int i = 0;
	cout << "Ruchy:";
	for (int i = 0; i < licznik; i++) {
		if (i % 6 == 0) {
			cout << endl;
		}
		if (i % 2 == 0) {
			cout << setw(4) << left << to_string((i + 2) / 2) + ".";
		}
		if (i == numer - 1) {
			SetConsoleTextAttribute(abc, 0x9F);
			cout << setw(8) << left << gra[i];			
			SetConsoleTextAttribute(abc, 15);
		}else
		cout << setw(8) << left << gra[i];
	}
	if (gra[licznik] == ruchRemis)
		cout << endl << ruchRemis << " remis";
	else if (gra[licznik] == ruchBiale)
		cout << endl << ruchBiale << " wygrana bia\210ych";
	else if (gra[licznik] == ruchCzarne)
		cout << endl << ruchCzarne << " wygrana czarnych";
	cout << endl << endl << endl;
}

int ileSzachujących(int pomocnicza[8][8]) {	//funkcja sprawdzająca ile bierek w danym momencie szachuje króla
	int liczba = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(czySzachujaca(pomocnicza, i, j))
				liczba++;
		}
	}
	return liczba;
}

void ruchy(string ruch, int plansza[8][8], int pomocnicza[8][8], bool kolor, int licznik50[1], ListaPlansz powtorzenia, string sprawdz[3]) {
	//druga zaraz po grze najważniejsza funkcja w całym programie
	//funkcja sterująca wpisanym przez gracza ruchem decyduje gdzie ruch dalej podać oraz w przpadku, gdy funkcja pomocnicza
	//sprawdzi, że wpisany ruch jest możliwy sprawdza czy ruch nie odsłoni, króla przed szachem i w zależności od wyniku cofa
	//lub zostawia dany ruch w przypadku poprawnego ruchu sprawdza czy nie ma pata, u oraz zasadę 50 ruchów i 3 powórzeń
	string stan{};
	string info{};
	int zwrot[8];
	int kolumna{}, rzad{}, x{}, y{}, kolumna2{}, rzad2{}, x2{}, y2{}, promowana{}, zbita{}, zmieniona{};
	bool czyPromocja = 0, bicieWPrzelocie = 0, czyRoszada = 0, ruchWieza = 0, ruchKrolem = 0, bicie = 0, ruchPionem = 0;
	sprawdz[0] = "";
	sprawdz[1] = "";
	sprawdz[2] = "";

	if (ruch.length() < 2) {
		sprawdz[0] = "blad";
		sprawdz[1] = ruch;
		return;
	}

	if (ruch[0] > 96 && ruch[0] < 105) {
		pion(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else if (zwrot[4] == 0 && zwrot[5] == 10) { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
			ruchPionem = 1;
		}
		else if (zwrot[5] == 10) { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
			promowana = zwrot[4];
			czyPromocja = 1;
			ruchPionem = 1;
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
			x2 = zwrot[4];
			y2 = zwrot[5];
			bicieWPrzelocie = 1;
			ruchPionem = 1;
		}
	}
	else if (ruch[0] == 'B') {
		goniec(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
		}
	}
	else if (ruch[0] == 'N') {
		skoczek(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
		}
	}
	else if (ruch[0] == 'R') {
		wieza(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
			ruchWieza = 1;
		}
	}
	else if (ruch[0] == 'Q') {
		hetman(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
		}
	}
	else if (ruch[0] == 'K') {
		krol(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
			ruchKrolem = 1;
		}
	}
	else if (ruch[0] == 'O' || ruch[0] == '0') {
		krol(ruch, plansza, pomocnicza, kolor, zwrot);
		if (zwrot[0] == 10) { 
			stan = "blad";
		}
		else { 
			kolumna = zwrot[0];
			rzad = zwrot[1];
			x = zwrot[2];
			y = zwrot[3];
			kolumna2 = zwrot[4];
			rzad2 = zwrot[5];
			x2 = zwrot[6];
			y2 = zwrot[7];
			czyRoszada = 1;
			ruchKrolem = 1;
		}
	}
	else {
		stan = "blad";
	}


	if (stan == "blad") {
		sprawdz[0] = "blad";
		sprawdz[1] = ruch;
		return;
	}

	zbita = zamien(kolumna, rzad, x, y, plansza, pomocnicza);
	if (zbita != 0) {
		bicie = 1;
	}

	if (czyRoszada) {
		zamien(kolumna2, rzad2, x2, y2, plansza, pomocnicza);
	}
	else if (czyPromocja) {
		zmieniona = plansza[y][x];
		plansza[y][x] = promowana;
	}
	else if (bicieWPrzelocie) {
		zmieniona = plansza[x2][y2];
		plansza[x2][y2] = 0;
	}

	wypelnijPomocnicza(plansza, pomocnicza, kolor);


	if (czySzach(plansza, pomocnicza, kolor)) {

		zamien(x, y, kolumna, rzad, plansza, pomocnicza);
		plansza[y][x] = zbita;
		stan = "blad";

		if (czyRoszada) {
			zamien(x2, y2, kolumna2, rzad2, plansza, pomocnicza);
		}
		else if (czyPromocja) {
			plansza[rzad][kolumna] = zmieniona;
		}
		else if (bicieWPrzelocie) {
			plansza[x2][y2] = zmieniona;
		}

		if (czyWPrzelocie(pomocnicza, y, x)) {
			pomocnicza[y][x] -= 1024;
		}

		wypelnijPomocnicza(plansza, pomocnicza, kolor);

	}
	else {
		sprawdzCzyWPrzelocie(plansza, pomocnicza, kolor);

		if (ruchWieza) {
			usunRoszada(pomocnicza, rzad, kolumna);
		}
		else if (ruchKrolem) {
			usunRoszada(pomocnicza, kolor * 7, 0);
			usunRoszada(pomocnicza, kolor * 7, 4);
			usunRoszada(pomocnicza, kolor * 7, 7);
		}
		if (czySzach(plansza, pomocnicza, !kolor)) {
			stan = "szach";
			if (!czyKrol(plansza, pomocnicza, !kolor)) {

				if (ileSzachujących(pomocnicza) == 1) {
					if (!czyZaslona(pomocnicza, !kolor)) {
						stan = "mat";
					}
				}
				else {
					stan = "mat";
				}
			}
		}
		else if (sprawdzPat(pomocnicza, !kolor)) {
			stan = "pat";
		}

		powtorzenia.dodaj(plansza);

	}

	if (stan == "" || stan == "szach") {
		licznik50[0]++;
		if (bicie || ruchPionem)
			licznik50[0] = 0;
		if (powtorzenia.porownaj(plansza))
			stan = "remis";
	}

	if (stan != "blad") {
		if (licznik50[0] == 100 && (stan == "" || stan == "szach")) {
			stan = "remis";
		}
		if (stan == "szach" && ruch[ruch.length() - 1] != '+') {
			if (ruch[ruch.length() - 1] == '#')
				ruch.replace(ruch.length() - 1, 1, "+");
			else
				ruch.append("+");
		}
		if (stan == "mat" && ruch[ruch.length() - 1] != '#') {
			if (ruch[ruch.length() - 1] == '+')
				ruch.replace(ruch.length() - 1, 1, "#");
			else
				ruch.append("#");
		}
		if (stan != "mat" && stan != "szach" && (ruch[ruch.length() - 1] == '#' || ruch[ruch.length() - 1] == '+')) {
			ruch.replace(ruch.length() - 1, 1, "");
		}
		int x = ruch.length();
		if (bicie) {
			int licznik = 0;
			for (int i = 0; i < x; i++) {
				if (ruch[i] == 'x')
					licznik++;
			}
			if (licznik == 0) {
				if (ruchPionem) {
					ruch.insert(1, "x");
				}
				else if (ruch.length() == 3 || (ruch.length() == 4 && (ruch[3] == '+' || ruch[3] == '#'))) {
					ruch.insert(1, "x");
				}
				else if (ruch.length() == 4 || (ruch.length() == 5 && (ruch[4] == '+' || ruch[4] == '#'))) {
					ruch.insert(2, "x");
				}
				else if (ruch.length() == 5 || (ruch.length() == 6 && (ruch[5] == '+' || ruch[5] == '#'))) {
					ruch.insert(3, "x");
				}
			}
		}
		else {
				int numer = 0;
				for (int i = 0; i < x; i++) {
					if (ruch[i] == 'x') {
						numer = i;
						break;
					}
				}
				if (numer != 0) {
					ruch.replace(numer, 1, "");
				}
		}

	}
	sprawdz[0] = stan;
	sprawdz[1] = ruch;
	sprawdz[2] = info;
	return;
}

void pomoc() { //funkcja wyświetla instrukcje
	cout << "Podczas rozgrywki mo\276na u\276y\206 nast\251puj\245cych komend:\n";
	cout << "- wyjdz - pyta o to czy zapisa\206 gr\251 i wychodzi do menu\n";
	cout << "- zapisz - zapisuje gr\251 do podanego pliku\n";
	cout << "- pomoc - wchodzi w pomoc\n";
	cout << "- poddaj - poddaje partie\n";
	cout << "- remis - proponuje remis przeciwnikowi\n\n";
	cout << "Ruchy nale\276 wpisywa\206 zgodnie ze skr\242con\245 notacj\245 algebraiczn\245:\n";
	cout << "- ruch pionem:\nw przypadku ruchu nale\276y wpisa\206 docelow\245 kolumn\251 i rz\245d piona np.a4\n";
	cout << "w przypadku bicia pionem kolumn\251 z kt\242rej pion bije,\na nast\251pnie docelow\245 kolumn\251 i rz\245d piona np.ab4\n\n";
	cout << "- ruch figur\245:\n";
	cout << "w przypadku ruchu lub bicia figur\245 nale\276y wpisa\206 liter\251 przypisan\245 figurze,\na nast\251pnie docelow\245 kolumn\251 i rz\245d figury np.Ra4,\n";
	cout << "gdy wi\251cej ni\276 jedna figura tego samego typu mo\276e\ndosta\206 si\251 na dane pole docelow\245 kolumn\251\nnale\276y poprzedzi\206 odpowiednio pocz\245tkow\245 kolumn\245 i/lub rz\251dem np.Ra1a4\n\n";
	cout << "Oznaczenia figur:\n";
	cout << "K - kr\242l\nQ - hetman\nR - wie\276a\nB - goniec\nN - skoczek\n";
	cout << "O-O-O - d\210uga roszada\nO-O - kr\242tka roszada\n\n";
	cout << "Oznaczenia opcjonalne:\n";
	cout << "- x - oznaczenie bicia tylko w przypadku bicia przed kolumn\245 docelow\245 np.Rxa4\n";
	cout << "- + - oznaczenie szacha na samym ko\344cu ruchu np.Ra4+\n";
	cout << "- # - oznaczenie matu na samym ko\344cu ruchu np.Ra4#\n\n";
	system("pause");
}

void wpisz(string ruch, string* gra, int licznik) { //funkcja wpisująca ruch do tablicy z ruchami
	gra[licznik] = ruch;
}