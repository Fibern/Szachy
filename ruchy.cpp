#include<string>
#include<iostream>
#include"pomocnicza.h"

using namespace std;

int literaNaKolumne(int a) { //zamienia wartoœæ dziesiêtn¹ kodu ASCII na numer kolumny
	a -= 97;
	return a;
}

int cyfraNaRzad(int a) {	//zamienia wartoœæ dziesiêtn¹ kodu ASCII na numer rzêdu
	a -= 47;
	a = 8 - a;
	return a;
}

int zamien(int xBijace, int yBijace, int xBite, int yBite, int plansza[8][8], int pomocnicza[8][8]) {	//funkcja wykonujê ruch na planszy

		int zbita = plansza[yBite][xBite];
		plansza[yBite][xBite] = plansza[yBijace][xBijace];
		plansza[yBijace][xBijace] = 0;
		return zbita;

}

void wieza(string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]) {
	//funkcja sprawdza czy jest mo¿liwoœæ wykonania danego ruchu wie¿¹
	int dlugosc = ruch.length();
	int licznik = 0;
	int figura{};
	if (kolor)
		figura = 1;
	else
		figura = -1;

	if (ruch[dlugosc - 1] == '#' || ruch[dlugosc - 1] == '+') {
		dlugosc -= 1;
	}

	int x = literaNaKolumne(ruch[dlugosc - 2]);
	int y = cyfraNaRzad(ruch[dlugosc - 1] - 1);
	int kolumna{}, rzad{};
	zwrot[0] = 10;
	zwrot[1] = 10;
	zwrot[2] = 10;
	zwrot[3] = 10;
	zwrot[4] = 10;
	zwrot[5] = 10;
	zwrot[6] = 10;
	zwrot[7] = 10;

	if (figura * plansza[y][x] > 0) {
		return;
	}

	if (dlugosc == 3 || (dlugosc == 4 && (ruch[1] == 'x' || ruch[1] == 'X'))) {
		for (int i = y + 1; i < 8; i++) {
			if (plansza[i][x] == figura) {
				kolumna = x;
				rzad = i;
				licznik++;
				break;
			}
			else if (plansza[i][x] * figura != 0) {
				break;
			}
		}
		for (int i = y - 1; i >= 0; i--) {
			if (plansza[i][x] == figura) {
				kolumna = x;
				rzad = i;
				licznik++;
				break;
			}
			else if (plansza[i][x] * figura != 0) {
				break;
			}
		}
		for (int i = x + 1; i < 8; i++) {
			if (plansza[y][i] == figura) {
				kolumna = i;
				rzad = y;
				licznik++;
				break;
			}
			else if (plansza[y][i] * figura != 0) {
				break;
			}
		}
		for (int i = x - 1; i >= 0; i--) {
			if (plansza[y][i] == figura) {
				kolumna = i;
				rzad = y;
				licznik++;
				break;
			}
			else if (plansza[y][i] * figura != 0) {
				break;
			}
		}
	}
	else if (dlugosc == 4 || (dlugosc == 5 && (ruch[2] == 'x' || ruch[2] == 'X'))) {

		if (ruch[1] > 96 && ruch[1] < 105) {
			kolumna = literaNaKolumne(ruch[1]);
			if (kolumna != x) {
				if (kolumna < x) {
					for (int i = x - 1; i >= kolumna; i--) {
						if (i == kolumna && plansza[y][i] == figura) {
							rzad = y;
							licznik++;
							break;
						}
						else if (plansza[y][i] * figura != 0) {
							break;
						}
					}
				}
				else {
					for (int i = x + 1; i <= kolumna; i++) {
						if (i == kolumna && plansza[y][i] == figura) {
							rzad = y;
							licznik++;
							break;
						}
						else if (plansza[y][i] * figura != 0) {
							break;
						}
					}
				}
			}
			else {
				for (int i = y + 1; i < 8; i++) {
					if (plansza[i][x] == figura) {
						rzad = i;
						licznik++;
						break;
					}
					else if (plansza[i][x] * figura != 0) {
						break;
					}
				}
				for (int i = y - 1; i >= 0; i--) {
					if (plansza[i][x] == figura) {
						rzad = i;
						licznik++;
						break;
					}
					else if (plansza[i][x] * figura != 0) {
						break;
					}
				}
			}
		}
		else if (ruch[1] > 48 && ruch[1] < 57) {
			rzad = cyfraNaRzad(ruch[1] - 1);
			if (rzad != y) {
				if (rzad < y) {
					for (int i = y - 1; i >= rzad; i--) {
						if (i == rzad && plansza[i][x] == figura) {
							kolumna = x;
							licznik++;
							break;
						}
						else if (plansza[i][x] * figura != 0) {
							break;
						}
					}
				}
				else {
					for (int i = y + 1; i <= rzad; i++) {
						if (i == rzad && plansza[i][x] == figura) {
							kolumna = x;
							licznik++;
							break;
						}
						else if (plansza[i][x] * figura != 0) {
							break;
						}
					}
				}
			}
			else {
				for (int i = x + 1; i < 8; i++) {
					if (plansza[y][i] == figura) {
						kolumna = i;
						rzad = y;
						licznik++;
						break;
					}
					else if (plansza[y][i] * figura != 0) {
						break;
					}
				}
				for (int i = x - 1; i >= 0; i--) {
					if (plansza[y][i] == figura) {
						kolumna = i;
						rzad = y;
						licznik++;
						break;
					}
					else if (plansza[y][i] * figura != 0) {
						break;
					}
				}
			}
		}
	}
	else if (dlugosc == 5 || (dlugosc == 6 && (ruch[3] == 'x' || ruch[3] == 'X'))) {
		kolumna = literaNaKolumne(ruch[1]);
		rzad = cyfraNaRzad(ruch[2] - 1);
		if (kolumna != x) {
			if (kolumna < x) {
				for (int i = x - 1; i >= kolumna; i--) {
					if (i == kolumna && plansza[y][i] == figura) {
						licznik++;
						break;
					}
					else if (plansza[y][i] * figura != 0) {
						break;
					}
				}
			}
			else {
				for (int i = x + 1; i <= kolumna; i++) {
					if (i == kolumna && plansza[y][i] == figura) {
						licznik++;
						break;
					}
					else if (plansza[y][i] * figura != 0) {
						break;
					}
				}
			}
		}else if (rzad != y) {
			if (rzad < y) {
				for (int i = y - 1; i >= rzad; i--) {
					if (i == rzad && plansza[i][x] == figura) {
						licznik++;
						break;
					}
					else if (plansza[i][x] * figura != 0) {
						break;
					}
				}
			}
			else {
				for (int i = y + 1; i <= rzad; i++) {
					if (i == rzad && plansza[i][x] == figura) {
						licznik++;
						break;
					}
					else if (plansza[i][x] * figura != 0) {
						break;
					}
				}
			}
		}
	}



	if (licznik == 1) {
		zwrot[0] = kolumna;
		zwrot[1] = rzad;
		zwrot[2] = x;
		zwrot[3] = y;
	}
}

void skoczek(string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]) {
	//funkcja sprawdza czy jest mo¿liwoœæ wykonania danego ruchu skoczkiem
	int dlugosc = ruch.length();
	int licznik = 0;
	int figura{};
	if (kolor)
		figura = 2;
	else
		figura = -2;

	if (ruch[dlugosc - 1] == '#' || ruch[dlugosc - 1] == '+') {
		dlugosc -= 1;
	}

	int x = literaNaKolumne(ruch[dlugosc - 2]);
	int y = cyfraNaRzad(ruch[dlugosc - 1]-1);
	int kolumna{}, rzad{};
	zwrot[0] = 10;
	zwrot[1] = 10;
	zwrot[2] = 10;
	zwrot[3] = 10;
	zwrot[4] = 10;
	zwrot[5] = 10;
	zwrot[6] = 10;
	zwrot[7] = 10;

	if (figura * plansza[y][x] > 0) {
		return;
	}

	if (dlugosc == 3 || (dlugosc == 4 && (ruch[1] == 'x' || ruch[1] == 'X'))) {
		if (plansza[y - 2][x - 1] == figura && y - 2 >= 0 && x - 1 >= 0 && y - 2< 8 && x - 1 < 8) {
			rzad = y - 2;
			kolumna = x - 1;
			licznik++;
		}
		if (plansza[y - 2][x + 1] == figura && y - 2 >= 0 && x + 1 < 8 && y - 2< 8 && x + 1>= 0) {
			rzad = y - 2;
			kolumna = x + 1;
			licznik++;
		}
		if (plansza[y - 1][x - 2] == figura && y - 1 >= 0 && x - 2 >= 0 && y - 1< 8 && x - 2 < 8) {
			rzad = y - 1;
			kolumna = x - 2;
			licznik++;
		}
		if (plansza[y - 1][x + 2] == figura && y - 1 >= 0 && x + 2 < 8 && y - 1 < 8 && x + 2 >= 0) {
			rzad = y - 1;
			kolumna = x + 2;
			licznik++;
		}
		if (plansza[y + 1][x - 2] == figura && y + 1 < 8 && x - 2 >= 0 && y + 1 >= 0 && x - 2 < 8) {
			rzad = y + 1;
			kolumna = x - 2;
			licznik++;
		}
		if (plansza[y + 1][x + 2] == figura && y + 1 < 8 && x + 2 < 8 && y + 1 >= 0 && x + 2 >= 0) {
			rzad = y + 1;
			kolumna = x + 2;
			licznik++;
		}
		if (plansza[y + 2][x - 1] == figura && y + 2 < 8 && x - 1 >= 0 && y + 2>= 0 && x - 1 < 8) {
			rzad = y + 2;
			kolumna = x - 1;
			licznik++;
		}
		if (plansza[y + 2][x + 1] == figura && y + 2 < 8 && x + 1 < 8 && y + 2 >= 0 && x + 1 >= 0) {
			rzad = y + 2;
			kolumna = x + 1;
			licznik++;
		}

	}
	else if (dlugosc == 4 || (dlugosc == 5 && (ruch[2] == 'x' || ruch[2] == 'X'))) {

		if (ruch[1] > 96 && ruch[1] < 105) {
			kolumna = literaNaKolumne(ruch[1]);
			if (abs(kolumna - x) == 2) {
				if (plansza[y + 1][kolumna] == figura && y + 1 < 8) {
					rzad = y + 1;
					licznik++;
				}if (plansza[y - 1][kolumna] == figura && y - 1 >= 0) {
					rzad = y - 1;
					licznik++;
				}
			}
			else if (abs(kolumna - x) == 1) {
				if (plansza[y + 2][kolumna] == figura && y + 2 < 8) {
					rzad = y + 2;
					licznik++;
				}if (plansza[y - 2][kolumna] == figura && y - 2 >= 0) {
					rzad = y - 2;
					licznik++;
				}
			}
		}
		else if (ruch[1] > 48 && ruch[1] < 57) {
			rzad = cyfraNaRzad(ruch[1]-1);
			if (abs(rzad - y) == 2) {
				if (plansza[rzad][x + 1] == figura && x + 1 < 8) {
					kolumna = x + 1;
					licznik++;
				}if (plansza[rzad][x - 1] == figura && x - 1 >= 0) {
					kolumna = x - 1;
					licznik++;
				}
			}
			else if (abs(rzad - y) == 1) {
				if (plansza[rzad][x + 2] == figura && x + 2 < 8) {
					kolumna = x + 2;
					licznik++;
				}if (plansza[rzad][x - 2] == figura && x - 2 >= 0) {
					kolumna = x - 2;
					licznik++;
				}
			}
		}


	}
	else if (dlugosc == 5 || (dlugosc == 6 && (ruch[3] == 'x' || ruch[3] == 'X'))) {
		kolumna = literaNaKolumne(ruch[1]);
		rzad = cyfraNaRzad(ruch[2]-1);
		if (plansza[rzad][kolumna] == figura && ((abs(kolumna - x) == 2 && abs(rzad - y) == 2) || (abs(kolumna - x) == 1 && abs(rzad - y) == 2))) {
			licznik++;
		}
	}



	if (licznik == 1) {
		zwrot[0] = kolumna;
		zwrot[1] = rzad;
		zwrot[2] = x;
		zwrot[3] = y;
	}

	return;

}

void goniec(string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]) {
	//funkcja sprawdza czy jest mo¿liwoœæ wykonania danego ruchu goñcem
	int dlugosc = ruch.length();
	int licznik = 0;
	int figura{};
	if (kolor)
		figura = 3;
	else
		figura = -3;

	if (ruch[dlugosc - 1] == '#' || ruch[dlugosc - 1] == '+') {
		dlugosc -= 1;
	}

	int x = literaNaKolumne(ruch[dlugosc - 2]);
	int y = cyfraNaRzad(ruch[dlugosc - 1] - 1);
	int kolumna{}, rzad{};
	zwrot[0] = 10;
	zwrot[1] = 10;
	zwrot[2] = 10;
	zwrot[3] = 10;
	zwrot[4] = 10;
	zwrot[5] = 10;
	zwrot[6] = 10;
	zwrot[7] = 10;

	if (figura * plansza[y][x] > 0) {
		return;
	}

	if (dlugosc == 3 || (dlugosc == 4 && (ruch[1] == 'x' || ruch[1] == 'X'))) {
		for (int i = 1; x + i < 8 && y + i < 8; i++) {
			if (plansza[y + i][x + i] == figura) {
				kolumna = x + i;
				rzad = y + i;
				licznik++;
				break;
			}
			else if (plansza[y + i][x + i] != 0) {
				break;
			}
		}
		for (int i = 1; x + i < 8 && y - i >= 0; i++) {
			if (plansza[y - i][x + i] == figura) {
				kolumna = x + i;
				rzad = y - i;
				licznik++;
				break;
			}
			else if (plansza[y - i][x + i] != 0) {
				break;
			}
		}
		for (int i = 1; x - i >= 0 && y + i < 8; i++) {
			if (plansza[y + i][x - i] == figura) {
				kolumna = x - i;
				rzad = y + i;
				licznik++;
				break;
			}
			else if (plansza[y + i][x - i] != 0) {
				break;
			}
		}
		for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
			if (plansza[y - i][x - i] == figura) {
				kolumna = x - i;
				rzad = y - i;
				licznik++;
				break;
			}
			else if (plansza[y - i][x - i] != 0) {
				break;
			}
		}
	}
	else if (dlugosc == 4 || (dlugosc == 5 && (ruch[2] == 'x' || ruch[2] == 'X'))) {

		if (ruch[1] > 96 && ruch[1] < 105) {
			kolumna = literaNaKolumne(ruch[1]);
			if (kolumna < x) {
				for (int i = 1; x - i >= kolumna && y + i < 8; i++) {
					if (x - i == kolumna && plansza[y + i][x - i] == figura) {
						rzad = y + i;
						licznik++;
						break;
					}
					else if (plansza[y + i][x - i] != 0) {
						break;
					}
				}
				for (int i = 1; x - i >= kolumna && y - i >= 0; i++) {
					if (x - i == kolumna && plansza[y - i][x - i] == figura) {
						rzad = y - i;
						licznik++;
						break;
					}
					else if (plansza[y - i][x - i] != 0) {
						break;
					}
				}
			}
			else {
				for (int i = 1; x + i <= kolumna && y + i < 8; i++) {
					if (x + i == kolumna && plansza[y + i][x + i] == figura) {
						rzad = y + i;
						licznik++;
						break;
					}
					else if (plansza[y + i][x + i] != 0) {
						break;
					}
				}
				for (int i = 1; x + i <= kolumna && y - i >= 0; i++) {
					if (x + i == kolumna && plansza[y - i][x + i] == figura) {
						rzad = y - i;
						licznik++;
						break;
					}
					else if (plansza[y - i][x + i] != 0) {
						break;
					}
				}
			}
		}
		else if (ruch[1] > 48 && ruch[1] < 57) {
			rzad = cyfraNaRzad(ruch[1] - 1);
			if (rzad < y) {
				for (int i = 1; x + i < 8 && y - i >= rzad; i++) {
					if (y - i == rzad && plansza[y - i][x + i] == figura) {
						kolumna = x + i;
						licznik++;
						break;
					}
					else if (plansza[y - i][x + i] != 0) {
						break;
					}
				}
				for (int i = 1; x - i >= 0 && y - i >= rzad; i++) {
					if (y - i == rzad && plansza[y - i][x - i] == figura) {
						kolumna = x - i;
						licznik++;
						break;
					}
					else if (plansza[y - i][x - i] != 0) {
						break;
					}
				}

			}
			else {
				for (int i = 1; x + i < 8 && y + i <= rzad; i++) {
					if (y + i == rzad && plansza[y + i][x + i] == figura) {
						kolumna = x + i;
						licznik++;
						break;
					}
					else if (plansza[y + i][x + i] != 0) {
						break;
					}
				}
				for (int i = 1; x - i >= 0 && y + i <= rzad; i++) {
					if (y + i == rzad && plansza[y + i][x - i] == figura) {
						kolumna = x - i;
						licznik++;
						break;
					}
					else if (plansza[y + i][x - i] != 0) {
						break;
					}
				}
			}
		}


	}
	else if (dlugosc == 5 || (dlugosc == 6 && (ruch[3] == 'x' || ruch[3] == 'X'))) {
		kolumna = literaNaKolumne(ruch[1]);
		rzad = cyfraNaRzad(ruch[2] - 1);
		if (rzad < y && kolumna < x) 
		{
			for (int i = 1; x - i >= kolumna && y - i >= rzad; i++) {
				if (y - i == rzad && x - i == kolumna && plansza[y - i][x - i] == figura) {
					licznik++;
					break;
				}
				else if (plansza[y - i][x - i] != 0) {
					break;
				}
			}
		}
		else if (rzad < y && kolumna > x)
		{
			for (int i = 1; x + i <= kolumna && y - i >= rzad; i++) {
				if (y - i == rzad && x + i == kolumna && plansza[y - i][x + i] == figura) {
					licznik++;
					break;
				}
				else if (plansza[y - i][x + i] != 0) {
					break;
				}
			}
		}
		else if (rzad > y && kolumna < x)
		{
			for (int i = 1; x - i >= kolumna && y + i <= rzad; i++) {
				if (y + i == rzad && x - i == kolumna && plansza[y + i][x - i] == figura) {
					licznik++;
					break;
				}
				else if (plansza[y + i][x - i] != 0) {
					break;
				}
			}
		}
		else
		{
			for (int i = 1; x + i <= kolumna && y + i <= rzad; i++) {
				if (y + i == rzad && x + i == kolumna && plansza[y + i][x + i] == figura) {
					licznik++;
					break;
				}
				else if (plansza[y + i][x + i] != 0) {
					break;
				}
			}
		}
	}

	


	if (licznik == 1) {
		zwrot[0] = kolumna;
		zwrot[1] = rzad;
		zwrot[2] = x;
		zwrot[3] = y;
	}
	return;

}

void hetman(string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]) {
	//funkcja sprawdza czy jest mo¿liwoœæ wykonania danego ruchu hetmanem 
	//jest po³¹czeniem funkcji wieza i goniec
	int dlugosc = ruch.length();
	int licznik = 0;
	int figura{};
	zwrot[0] = 10;
	zwrot[1] = 10;
	zwrot[2] = 10;
	zwrot[3] = 10;
	zwrot[4] = 10;
	zwrot[5] = 10;
	zwrot[6] = 10;
	zwrot[7] = 10;
	if (kolor)
		figura = 4;
	else
		figura = -4;

	if (ruch[dlugosc - 1] == '#' || ruch[dlugosc - 1] == '+') {
		dlugosc -= 1;
	}

	int x = literaNaKolumne(ruch[dlugosc - 2]);
	int y = cyfraNaRzad(ruch[dlugosc - 1] - 1);
	int kolumna{}, rzad{};

	if (figura * plansza[y][x] > 0) {
		return;
	}


	if (dlugosc == 3 || (dlugosc == 4 && (ruch[1] == 'x' || ruch[1] == 'X'))) {
		for (int i = y + 1; i < 8; i++) {
			if (plansza[i][x] == figura) {
				kolumna = x;
				rzad = i;
				licznik++;
				break;
			}
			else if (plansza[i][x] * figura != 0) {
				break;
			}
		}
		for (int i = y - 1; i >= 0; i--) {
			if (plansza[i][x] == figura) {
				kolumna = x;
				rzad = i;
				licznik++;
				break;
			}
			else if (plansza[i][x] * figura != 0) {
				break;
			}
		}
		for (int i = x + 1; i < 8; i++) {
			if (plansza[y][i] == figura) {
				kolumna = i;
				rzad = y;
				licznik++;
				break;
			}
			else if (plansza[y][i] * figura != 0) {
				break;
			}
		}
		for (int i = x - 1; i >= 0; i--) {
			if (plansza[y][i] == figura) {
				kolumna = i;
				rzad = y;
				licznik++;
				break;
			}
			else if (plansza[y][i] * figura != 0) {
				break;
			}
		}
		for (int i = 1; x + i < 8 && y + i < 8; i++) {
			if (plansza[y + i][x + i] == figura) {
				kolumna = x + i;
				rzad = y + i;
				licznik++;
				break;
			}
			else if (plansza[y + i][x + i] != 0) {
				break;
			}
		}
		for (int i = 1; x + i < 8 && y - i >= 0; i++) {
			if (plansza[y - i][x + i] == figura) {
				kolumna = x + i;
				rzad = y - i;
				licznik++;
				break;
			}
			else if (plansza[y - i][x + i] != 0) {
				break;
			}
		}
		for (int i = 1; x - i >= 0 && y + i < 8; i++) {
			if (plansza[y + i][x - i] == figura) {
				kolumna = x - i;
				rzad = y + i;
				licznik++;
				break;
			}
			else if (plansza[y + i][x - i] != 0) {
				break;
			}
		}
		for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
			if (plansza[y - i][x - i] == figura) {
				kolumna = x - i;
				rzad = y - i;
				licznik++;
				break;
			}
			else if (plansza[y - i][x - i] != 0) {
				break;
			}
		}
	}
	else if (dlugosc == 4 || (dlugosc == 5 && (ruch[2] == 'x' || ruch[2] == 'X'))) {

		if (ruch[1] > 96 && ruch[1] < 105) {
			kolumna = literaNaKolumne(ruch[1]);
			if (kolumna != x) {
				if (kolumna < x) {
					for (int i = x - 1; i >= kolumna; i--) {
						if (i == kolumna && plansza[y][i] == figura) {
							rzad = y;
							licznik++;
							break;
						}
						else if (plansza[y][i] * figura != 0) {
							break;
						}
					}
					for (int i = 1; x - i >= kolumna && y + i < 8; i++) {
						if (x - i == kolumna && plansza[y + i][x - i] == figura) {
							rzad = y + i;
							licznik++;
							break;
						}
						else if (plansza[y + i][x - i] != 0) {
							break;
						}
					}
					for (int i = 1; x - i >= kolumna && y - i >= 0; i++) {
						if (x - i == kolumna && plansza[y - i][x - i] == figura) {
							rzad = y - i;
							licznik++;
							break;
						}
						else if (plansza[y - i][x - i] != 0) {
							break;
						}
					}
				}
				else {
					for (int i = x + 1; i <= kolumna; i++) {
						if (i == kolumna && plansza[y][i] == figura) {
							rzad = y;
							licznik++;
							break;
						}
						else if (plansza[y][i] * figura != 0) {
							break;
						}
					}
					for (int i = 1; x + i <= kolumna && y + i < 8; i++) {
						if (x + i == kolumna && plansza[y + i][x + i] == figura) {
							rzad = y + i;
							licznik++;
							break;
						}
						else if (plansza[y + i][x + i] != 0) {
							break;
						}
					}
					for (int i = 1; x + i <= kolumna && y - i >= 0; i++) {
						if (x + i == kolumna && plansza[y - i][x + i] == figura) {
							rzad = y - i;
							licznik++;
							break;
						}
						else if (plansza[y - i][x + i] != 0) {
							break;
						}
					}
				}
			}
			else {
				for (int i = y + 1; i < 8; i++) {
					if (plansza[i][x] == figura) {
						rzad = i;
						licznik++;
						break;
					}
					else if (plansza[i][x] * figura != 0) {
						break;
					}
				}
				for (int i = y - 1; i >= 0; i--) {
					if (plansza[i][x] == figura) {
						rzad = i;
						licznik++;
						break;
					}
					else if (plansza[i][x] * figura != 0) {
						break;
					}
				}
			}
		}
		else if (ruch[1] > 48 && ruch[1] < 57) {
			rzad = cyfraNaRzad(ruch[1] - 1);
			if (rzad != y) {
				if (rzad < y) {
					for (int i = y - 1; i >= rzad; i--) {
						if (i == rzad && plansza[i][x] == figura) {
							kolumna = x;
							licznik++;
							break;
						}
						else if (plansza[i][x] * figura != 0) {
							break;
						}
					}
					for (int i = 1; x + i < 8 && y - i >= rzad; i++) {
						if (y - i == rzad && plansza[y - i][x + i] == figura) {
							kolumna = x + i;
							licznik++;
							break;
						}
						else if (plansza[y - i][x + i] != 0) {
							break;
						}
					}
					for (int i = 1; x - i >= 0 && y - i >= rzad; i++) {
						if (y - i == rzad && plansza[y - i][x - i] == figura) {
							kolumna = x - i;
							licznik++;
							break;
						}
						else if (plansza[y - i][x - i] != 0) {
							break;
						}
					}
				}
				else {
					for (int i = y + 1; i <= rzad; i++) {
						if (i == rzad && plansza[i][x] == figura) {
							kolumna = x;
							licznik++;
							break;
						}
						else if (plansza[i][x] * figura != 0) {
							break;
						}
					}
					for (int i = 1; x + i < 8 && y + i <= rzad; i++) {
						if (y + i == rzad && plansza[y + i][x + i] == figura) {
							kolumna = x + i;
							licznik++;
							break;
						}
						else if (plansza[y + i][x + i] != 0) {
							break;
						}
					}
					for (int i = 1; x - i >= 0 && y + i <= rzad; i++) {
						if (y + i == rzad && plansza[y + i][x - i] == figura) {
							kolumna = x - i;
							licznik++;
							break;
						}
						else if (plansza[y + i][x - i] != 0) {
							break;
						}
					}
				}
			}
			else {
				for (int i = x + 1; i < 8; i++) {
					if (plansza[y][i] == figura) {
						kolumna = i;
						rzad = y;
						licznik++;
						break;
					}
					else if (plansza[y][i] * figura != 0) {
						break;
					}
				}
				for (int i = x - 1; i >= 0; i--) {
					if (plansza[y][i] == figura) {
						kolumna = i;
						rzad = y;
						licznik++;
						break;
					}
					else if (plansza[y][i] * figura != 0) {
						break;
					}
				}
			}
		}		

	}
	else if (dlugosc == 5 || (dlugosc == 6 && (ruch[3] == 'x' || ruch[3] == 'X'))) {
		kolumna = literaNaKolumne(ruch[1]);
		rzad = cyfraNaRzad(ruch[2] - 1);
		if (rzad == y || kolumna == x) {
			if (kolumna != x) {
				if (kolumna < x) {
					for (int i = x - 1; i >= kolumna; i--) {
						if (i == kolumna && plansza[y][i] == figura) {
							licznik++;
							break;
						}
						else if (plansza[y][i] * figura != 0) {
							break;
						}
					}
				}
				else {
					for (int i = x + 1; i <= kolumna; i++) {
						if (i == kolumna && plansza[y][i] == figura) {
							licznik++;
							break;
						}
						else if (plansza[y][i] * figura != 0) {
							break;
						}
					}
				}
			}
			else if (rzad != y) {
				if (rzad < y) {
					for (int i = y - 1; i >= rzad; i--) {
						if (i == rzad && plansza[i][x] == figura) {
							licznik++;
							break;
						}
						else if (plansza[i][x] * figura != 0) {
							break;
						}
					}
				}
				else {
					for (int i = y + 1; i <= rzad; i++) {
						if (i == rzad && plansza[i][x] == figura) {
							licznik++;
							break;
						}
						else if (plansza[i][x] * figura != 0) {
							break;
						}
					}
				}
			}
		}
		else {
			if (rzad < y && kolumna < x)
			{
				for (int i = 1; x - i >= kolumna && y - i >= rzad; i++) {
					if (y - i == rzad && x - i == kolumna && plansza[y - i][x - i] == figura) {
						licznik++;
						break;
					}
					else if (plansza[y - i][x - i] != 0) {
						break;
					}
				}
			}
			else if (rzad < y && kolumna > x)
			{
				for (int i = 1; x + i <= kolumna && y - i >= rzad; i++) {
					if (y - i == rzad && x + i == kolumna && plansza[y - i][x + i] == figura) {
						licznik++;
						break;
					}
					else if (plansza[y - i][x + i] != 0) {
						break;
					}
				}
			}
			else if (rzad > y && kolumna < x)
			{
				for (int i = 1; x - i >= kolumna && y + i <= rzad; i++) {
					if (y + i == rzad && x - i == kolumna && plansza[y + i][x - i] == figura) {
						licznik++;
						break;
					}
					else if (plansza[y + i][x - i] != 0) {
						break;
					}
				}
			}
			else
			{
				for (int i = 1; x + i <= kolumna && y + i <= rzad; i++) {
					if (y + i == rzad && x + i == kolumna && plansza[y + i][x + i] == figura) {
						licznik++;
						break;
					}
					else if (plansza[y + i][x + i] != 0) {
						break;
					}
				}
			}
		}
	}


	if (licznik == 1) {
		zwrot[0] = kolumna;
		zwrot[1] = rzad;
		zwrot[2] = x;
		zwrot[3] = y;
	}
}

bool czyZero(int plansza[8][8], int y, int x1,  int x2) {
	//funkcja sprawdza czy na danym polu nie ma figur przydatna do roszady
	for (int i = x1; i <= x2; i++) {
		if (plansza[y][i] != 0) {
			return 0;
		}
	}
	return 1;
}

bool czyRoszada(int pomocnicza[8][8], int plansza[8][8], int kolor, string ruch) {
	//funkcja sprawdza czy dana roszada jest mo¿liwa
	int wiersz{};

	if (kolor > 0)
		wiersz = 7;
	else
		wiersz = 0;



	if (ruch.length() == 3 || ruch.length() == 4) {

		if (pomocnicza[wiersz][7] >= 2048 && pomocnicza[wiersz][4] >= 2048) {
			if (!czyAtakowane(pomocnicza,wiersz,4,kolor) && !czyAtakowane(pomocnicza, wiersz, 5, kolor) && !czyAtakowane(pomocnicza, wiersz, 6, kolor) && czyZero(plansza,wiersz,5,6)) {
				
				return 1;
			}
		}
	}
	else {
		if (pomocnicza[wiersz][0] >= 2048 && pomocnicza[wiersz][4] >= 2048) {
			if (!czyAtakowane(pomocnicza, wiersz, 4, kolor) && !czyAtakowane(pomocnicza, wiersz, 3, kolor) && !czyAtakowane(pomocnicza, wiersz, 2, kolor) && czyZero(plansza, wiersz, 1, 3)) {
				return 1;
			}
		}
	}
	return 0;
}

void roszada(int plansza[8][8], int pomocnicza[8][8], bool krotka, int kolor, int zwrot[8]) {
	//funkcja zapisuje odpowiednie wartoœci jeœli roszada okaza³a siê byæ mo¿liwa
	int wiersz{};
	
	if (kolor)
		wiersz = 7;
	else
		wiersz = 0;

	if (krotka) {
		zwrot[0] = 4;
		zwrot[1] = wiersz;
		zwrot[2] = 6;
		zwrot[3] = wiersz;
		zwrot[4] = 7;
		zwrot[5] = wiersz;
		zwrot[6] = 5;
		zwrot[7] = wiersz;
		return;
	}
	else {
		zwrot[0] = 4;
		zwrot[1] = wiersz;
		zwrot[2] = 2;
		zwrot[3] = wiersz;
		zwrot[4] = 0;
		zwrot[5] = wiersz;
		zwrot[6] = 3;
		zwrot[7] = wiersz;
		return;
	}
}

void krol(string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]) {
	//funkcja sprawdza czy jest mo¿liwoœæ wykonania danego ruchu królem
	int figura{}, wiersz{};
	int dlugosc = ruch.length();
	if (ruch[dlugosc - 1] == '#' || ruch[dlugosc - 1] == '+') {
		dlugosc -= 1;
	}
	zwrot[0] = 10;
	zwrot[1] = 10;
	zwrot[2] = 10;
	zwrot[3] = 10;
	zwrot[4] = 10;
	zwrot[5] = 10;
	zwrot[6] = 10;
	zwrot[7] = 10;

	if (ruch[0] == 'O' || ruch[0] == '0') {
		if (ruch[1] == '-' && (ruch[2] == 'O' || ruch[2] == '0')) {
			if (dlugosc == 3 || (dlugosc == 4 && (ruch[3] == '#' || ruch[3] == '+'))) {
				if (czyRoszada(pomocnicza, plansza, kolor, ruch)) {
					roszada(plansza, pomocnicza, 1, kolor, zwrot);
					return;
				}
			}
			else if ((ruch[3] == '-' && (ruch[4] == 'O' || ruch[4] == '0')) && (dlugosc == 5 || dlugosc == 6 && (ruch[5] == '#' || ruch[5] == '+'))) {
				if (czyRoszada(pomocnicza, plansza, kolor, ruch)) {
					roszada(plansza, pomocnicza, 0, kolor, zwrot);
					return;
				}
			}
		}
	}

	int x = literaNaKolumne(ruch[dlugosc - 2]);
	int y = cyfraNaRzad(ruch[dlugosc - 1] - 1);
	if (kolor) {
		figura = 5;
		wiersz = 7;
	}
	else {
		figura = -5;
		wiersz = 0;
	}
	if (figura * plansza[y][x] > 0) {
		return;
	}


	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 1; j <= x + 1; j++) {
			if (i >= 0 && i < 8 && j >= 0 && j < 8) {
				if (plansza[i][j] == figura) {
					zwrot[0] = j;
					zwrot[1] = i;
					zwrot[2] = x;
					zwrot[3] = y;
					return;
					
				}
			}
		}
	}
	return;

}

void pion(string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]) {
	//funkcja sprawdza czy jest mo¿liwoœæ wykonania danego ruchu pionem
	int dlugosc = ruch.length();


	if (ruch[dlugosc - 1] == '#' || ruch[dlugosc - 1] == '+') {
		dlugosc -= 1;
	}
	if (ruch[dlugosc - 2] == '=') {
		dlugosc -= 2;
	}

	int rzad = 10;
	
	int x = literaNaKolumne(ruch[dlugosc - 2]);
	int y = cyfraNaRzad(ruch[dlugosc - 1] - 1);
	int kolumna = literaNaKolumne(ruch[0]);
	zwrot[0] = 10;
	zwrot[1] = 10;
	zwrot[2] = 10;
	zwrot[3] = 10;
	zwrot[4] = 10;
	zwrot[5] = 10;
	zwrot[6] = 10;
	zwrot[7] = 10;

	if (ruch[dlugosc] == '=' && y > 0 && y < 7) {
		return;
	}
	if ((y == 0 || y == 7) && ruch[dlugosc] != '=') {
		return;
	}
	if (ruch[dlugosc] == '=' && ruch[dlugosc + 1] != 'n' && ruch[dlugosc + 1] != 'N' && ruch[dlugosc + 1] != 'q' && ruch[dlugosc + 1] != 'Q'&& ruch[dlugosc + 1] != 'r' && ruch[dlugosc + 1] != 'R' && ruch[dlugosc + 1] != 'b' && ruch[dlugosc + 1] != 'B') {
		return;
	}

	int promowana = 0;

	if (ruch[dlugosc] == '=') {
		if (ruch[dlugosc + 1] == 'q' || ruch[dlugosc + 1] == 'Q')
			promowana = 4 * ((2 * kolor) - 1) ;
		if (ruch[dlugosc + 1] == 'r' || ruch[dlugosc + 1] == 'R')
			promowana = 1 * ((2 * kolor) - 1);
		if (ruch[dlugosc + 1] == 'b' || ruch[dlugosc + 1] == 'B')
			promowana = 3 * ((2 * kolor) - 1);
		if (ruch[dlugosc + 1] == 'n' || ruch[dlugosc + 1] == 'N')
			promowana = 2 * ((2 * kolor) - 1);
	}

	if (dlugosc == 2) {						
		if (kolor) {								
			if (y == 4 && plansza[y + 2][x] == 6 && plansza[y + 1][x] != 6) {

				if (plansza[y + 1][x] == 0 && plansza[y][x] == 0) {
					rzad = y + 2;
					wpiszPomocnicza(pomocnicza, y, x, 10);
				}
			}
			else {
				if (plansza[y + 1][x] == 6 && plansza[y][x] == 0) {
					rzad = y + 1;
				}
			}
		}
		else {										
			if (y == 3 && plansza[y - 2][x] == -6 && plansza[y - 1][x] != -6) {

				if (plansza[y - 1][x] == 0 && plansza[y][x] == 0) {
					rzad = y - 2;
					wpiszPomocnicza(pomocnicza, y, x, 10);
				}
			}
			else {
				if (plansza[y - 1][x] == -6 && plansza[y][x] == 0) {
					rzad = y - 1;
				}
			}

		}
	}
	else if(dlugosc == 3 || (dlugosc == 4 && (ruch[1] == 'x' || ruch[1] == 'X'))) {											
		if (kolor) {								
			if (abs(kolumna - x) == 1) {
				if (plansza[y][x] < 0 && plansza[y + 1][kolumna] == 6) {
					rzad = y + 1;
				}
				else if (plansza[y + 1][x] == -6 && czyWPrzelocie(pomocnicza, y + 1, x) && plansza[y + 1][kolumna] == 6) {
					zwrot[0] = kolumna;
					zwrot[1] = y + 1;
					zwrot[2] = x;
					zwrot[3] = y;
					zwrot[4] = y + 1;
					zwrot[5] = x;
					return;
				}
			}
		}
		else {										
			if (abs(kolumna - x) == 1) {
				if (plansza[y][x] > 0 && plansza[y - 1][kolumna] == -6) {
					rzad = y - 1;
				}
				else if (plansza[y - 1][x] == 6 && czyWPrzelocie(pomocnicza, y - 1, x) && plansza[y - 1][kolumna] == -6) {
					zwrot[0] = kolumna;
					zwrot[1] = y - 1;
					zwrot[2] = x;
					zwrot[3] = y;
					zwrot[4] = y - 1;
					zwrot[5] = x;
					return;
				}
			}
		}
	}
	

	if (rzad == 10) {
		return;
	}
	zwrot[0] = kolumna;
	zwrot[1] = rzad;
	zwrot[2] = x;
	zwrot[3] = y;
	zwrot[4] = promowana;
	return;
}