#include <iostream>
#include <bitset>
using namespace std;

void pozycjaKrol(int plansza[8][8], int kolor, int pozycja[2]) {	//funkcja szukaj¹ca króla o danym kolorze
	int krol = 5;
	if (kolor == 0) {
		krol = -5;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (plansza[i][j] == krol) {
				pozycja[0] = i;
				pozycja[1] = j;
			}
		}
	}
}

bool czyPrzypieta(int pomocnicza[8][8], int y, int x) {	//funkcja sprawdza czy dana figura jest przypiêta
	if (((pomocnicza[y][x] >> 4) & 1) == 1) {
		return 1;
	}
	return 0;
}

bool czySzachujaca(int pomocnicza[8][8], int y, int x) {	//funkcja sprawdza czy dana figura jest figur¹ szachuj¹c¹
	if (((pomocnicza[y][x] >> 7) & 1) == 1) {
		return 1;
	}
	return 0;
}

bool czySzachowane(int pomocnicza[8][8], int y, int x) {	//funkcja sprawdza czy dane pole jest miêdzy szachowanym królem, a figur¹ szachuj¹c¹
	if (((pomocnicza[y][x] >> 6) & 1) == 1) {
		return 1;
	}
	return 0;
}

bool czyWPrzelocie(int pomocnicza[8][8], int y, int x) {	//funkcja sprawdza czy danego piona mo¿na zbiæ w przelocie
	if (((pomocnicza[y][x] >> 10) & 1) == 1) {
		return 1;
	}
	return 0;
}

bool czyRoszada(int pomocnicza[8][8], int y, int x) {	//funkcja sprawdzaj¹ca czy mo¿na wykonaæ roszadê dla danego pola
	if (((pomocnicza[y][x] >> 11) & 1) == 1) {
		return 1;
	}
	return 0;
}

void usunRoszada(int pomocnicza[8][8], int y, int x) {	//funkcja usuwaj¹ca mo¿liwoœæ wykonaniu roszady (jeœli istnieje) na danym polu uruchamiana po poprawnym ruchu królem lub wie¿¹
	if (pomocnicza[y][x] >= 2048) {
		pomocnicza[y][x] -= 2048;
	}
}

bool czyRuch(int pomocnicza[8][8], int y, int x, int kolor) {	//funkcja sprawdzaj¹ca czy jest mo¿liwoœæ ruchu dla danego gracza na dane pole przydatna do sprawdzenia matu i pata
	if (((pomocnicza[y][x] >> kolor) & 1) == 1 || ((pomocnicza[y][x] >> kolor + 8) & 1) == 1) {
		return 1;
	}
	return 0;
}

bool czyAtakowane(int pomocnicza[8][8], int y, int x, int kolor) {	//sprawdza czy dane pole znajduje siê pod atakiem danego gracza
	if (kolor == 1) {
		kolor = 0;
	}
	else {
		kolor = 1;
	}

	if (((pomocnicza[y][x] >> kolor) & 1) == 1 || ((pomocnicza[y][x] >> kolor + 2) & 1) == 1) {
			return 1;
	}

	return 0;
}

void wpiszPomocnicza(int pomocnicza[8][8], int y, int x, int bit) {	//funkcja wpisuje do danego pola na planszy pomocniczej dany bit
	if (y >= 0 && y < 8 && x >= 0 && x < 8) {
		if (((pomocnicza[y][x] >> bit) & 1) != 1) {
			pomocnicza[y][x] += (int)pow(2, bit);
		}
	}
}

void sprawdzKrol(int plansza[8][8], int pomocnicza[8][8], int kolor, int x ,int y) {
	//funkcja sprawdzaj¹ca czy król jest szachowany jak tak to z jakiego pola oraz szukaj¹ca przypiêtych do króla figur

	int licznik = 0;
	int przypietaY = -1, przypietaX = -1;
	if (kolor == 0)
		kolor--;
	for (int i = y + 1; i < 8; i++) {

		if (plansza[i][x] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = i;
			przypietaX = x;
		}
		else if (plansza[i][x] * kolor > 0 && licznik == 1 || plansza[i][x] * kolor < 0 && licznik == 0) {
			if ((plansza[i][x] == -kolor * 1 || plansza[i][x] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, i, x, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[i][x] == -kolor * 1 || plansza[i][x] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}
	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = x + 1; i < 8; i++) {
		if (plansza[y][i] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = y;
			przypietaX = i;
		}
		else if (plansza[y][i] * kolor > 0 && licznik == 1 || plansza[y][i] * kolor < 0 && licznik == 0) {
			if ((plansza[y][i] == -kolor * 1 || plansza[y][i] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, y, i, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[y][i] == -kolor * 1 || plansza[y][i] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}
	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = y - 1; i >= 0; i--) {
		if (plansza[i][x] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = i;
			przypietaX = x;
		}
		else if (plansza[i][x] * kolor > 0 && licznik == 1 || plansza[i][x] * kolor < 0 && licznik == 0) {
			if ((plansza[i][x] == -kolor * 1 || plansza[i][x] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, i, x, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[i][x] == -kolor * 1 || plansza[i][x] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}
	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = x - 1; i >= 0; i--) {
		if (plansza[y][i] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = y;
			przypietaX = i;
		}
		else if (plansza[y][i] * kolor > 0 && licznik == 1 || plansza[y][i] * kolor < 0 && licznik == 0) {
			if ((plansza[y][i] == -kolor * 1 || plansza[y][i] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, y, i, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[y][i] == -kolor * 1 || plansza[y][i] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}
	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
		if (plansza[y - i][x - i] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = y - i;
			przypietaX = x - i;
		}
		else if (plansza[y - i][x - i] * kolor > 0 && licznik == 1 || plansza[y - i][x - i] * kolor < 0 && licznik == 0) {
			if ((plansza[y - i][x - i] == -kolor * 3 || plansza[y - i][x - i] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, y - i, x - i, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[y - i][x - i] == -kolor * 3 || plansza[y - i][x - i] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}
	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = 1; x + i <= 7 && y - i >= 0; i++) {
		if (plansza[y - i][x + i] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = y - i;
			przypietaX = x + i;
		}
		else if (plansza[y - i][x + i] * kolor > 0 && licznik == 1 || plansza[y - i][x + i] * kolor < 0 && licznik == 0) {
			if ((plansza[y - i][x + i] == -kolor * 3 || plansza[y - i][x + i] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, y - i, x + i, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[y - i][x + i] == -kolor * 3 || plansza[y - i][x + i] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}

	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = 1; x - i >= 0 && y + i <= 7; i++) {
		if (plansza[y + i][x - i] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = y + i;
			przypietaX = x - i;
		}
		else if (plansza[y + i][x - i] * kolor > 0 && licznik == 1 || plansza[y + i][x - i] * kolor < 0 && licznik == 0) {
			if ((plansza[y + i][x - i] == -kolor * 3 || plansza[y + i][x - i] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, y + i, x - i, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[y + i][x - i] == -kolor * 3 || plansza[y + i][x - i] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}

	}
	przypietaY = -1;
	przypietaX = -1;
	licznik = 0;
	for (int i = 1; x + i <= 7 && y + i <= 7; i++) {
		if (plansza[y + i][x + i] * kolor > 0 && licznik == 0) {
			licznik++;
			przypietaY = y + i;
			przypietaX = x + i;
		}
		else if (plansza[y + i][x + i] * kolor > 0 && licznik == 1 || plansza[y + i][x + i] * kolor < 0 && licznik == 0) {
			if ((plansza[y + i][x + i] == -kolor * 3 || plansza[y + i][x + i] == -kolor * 4) && licznik == 0) {
				wpiszPomocnicza(pomocnicza, y + i, x + i, 7);
				wpiszPomocnicza(pomocnicza, y, x, 5);
			}
			break;
		}
		else if ((plansza[y + i][x + i] == -kolor * 3 || plansza[y + i][x + i] == -kolor * 4) && licznik == 1) {
			wpiszPomocnicza(pomocnicza, przypietaY, przypietaX, 4);
			break;
		}

	}
	if (plansza[y - 2][x - 1] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y - 2, x - 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y - 2][x + 1] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y - 2, x + 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y - 1][x - 2] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y - 1, x - 2, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y - 1][x + 2] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y - 1, x + 2, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y + 1][x - 2] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y + 1, x - 2, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y + 1][x + 2] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y + 1, x + 2, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y + 2][x - 1] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y + 2, x - 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}
	if (plansza[y + 2][x + 1] * kolor == -2){
		wpiszPomocnicza(pomocnicza, y + 2, x + 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}

	if (plansza[y + 1][x - 1] == 6 && kolor == -1) {
		wpiszPomocnicza(pomocnicza, y + 1, x - 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}	
	if (plansza[y + 1][x + 1] == 6 && kolor == -1) {
		wpiszPomocnicza(pomocnicza, y + 1, x + 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}	
	if (plansza[y - 1][x - 1] == -6 && kolor == 1) {
		wpiszPomocnicza(pomocnicza, y - 1, x - 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}	
	if (plansza[y - 1][x + 1] == -6 && kolor == 1) {
		wpiszPomocnicza(pomocnicza, y - 1, x + 1, 7);
		wpiszPomocnicza(pomocnicza, y, x, 5);
	}

}

void gdzieWieza(int plansza[8][8], int pomocnicza[8][8], int bierka, int y, int x) {
	//funkcja sprawdza wszystkie pola atakowane przez dan¹ wie¿e i wpisuje odpowiedni¹ wartoœæ do pomocniczej planszy
	int kolor = 0;
	if (bierka > 0)
		kolor = 1;
	int pozycja[2]{}, pozycjaNasz[2]{};
	bool przypieta = czyPrzypieta(pomocnicza, y, x);
	bool szachujaca = czySzachujaca(pomocnicza, y, x);
	pozycjaKrol(plansza, 1 - kolor, pozycja);
	pozycjaKrol(plansza, kolor, pozycjaNasz);
	int krolY = pozycja[0];
	int krolX = pozycja[1];
	int krolNaszY = pozycjaNasz[0];
	int krolNaszX = pozycjaNasz[1];

	for (int i = x + 1; i < 8; i++) {

		if ((przypieta && krolNaszY != y) || bierka * plansza[y][i] > 0) {
			wpiszPomocnicza(pomocnicza, y, i, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, y, i, kolor);
		}
		if (szachujaca && krolX > i && krolY == y)
			wpiszPomocnicza(pomocnicza, y, i, 6);
		if (bierka * plansza[y][i] != 0)
			break;
	}
	for (int i = x - 1; i >= 0 ; i--) {

		if ((przypieta && krolNaszY != y) || bierka * plansza[y][i] > 0) {
			wpiszPomocnicza(pomocnicza, y, i, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, y, i, kolor);
		}
		if (szachujaca && krolX < i && krolY == y)
			wpiszPomocnicza(pomocnicza, y, i, 6);
		if (bierka * plansza[y][i] != 0)
			break;
	}
	for (int i = y + 1; i < 8; i++) {

		if ((przypieta && krolNaszX != x) || bierka * plansza[i][x] > 0) {
			wpiszPomocnicza(pomocnicza, i, x, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, i, x, kolor);
		}
		if (szachujaca && krolY > i && krolX == x)
			wpiszPomocnicza(pomocnicza, i, x, 6);
		if (bierka * plansza[i][x] != 0)
			break;
	}
	for (int i = y - 1; i >= 0; i--) {

		if ((przypieta && krolNaszX != x) || bierka * plansza[i][x] > 0) {
			wpiszPomocnicza(pomocnicza, i, x, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, i, x, kolor);
		}
		if (szachujaca && krolY < i && krolX == x)
			wpiszPomocnicza(pomocnicza, i, x, 6);
		if (bierka * plansza[i][x] != 0)
			break;
	}
	
}

void gdzieSkoczek(int plansza[8][8], int pomocnicza[8][8], int bierka, int y, int x) {
	//funkcja sprawdza wszystkie pola atakowane przez danego skoczka i wpisuje odpowiedni¹ wartoœæ do pomocniczej planszy
	bool przypieta = czyPrzypieta(pomocnicza, y, x);
	int kolor = 0;
	if (bierka > 0)
		kolor = 1;
	int pozycja[2]{};
	
	if (plansza[y - 2][x - 1] * bierka > 0 || przypieta) 
		wpiszPomocnicza(pomocnicza, y - 2, x - 1, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y - 2, x - 1, kolor);

	if (plansza[y - 2][x + 1] * bierka > 0 || przypieta)
		wpiszPomocnicza(pomocnicza, y - 2, x + 1, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y - 2, x + 1, kolor);

	if (plansza[y - 1][x - 2] * bierka > 0 || przypieta)
		wpiszPomocnicza(pomocnicza, y - 1, x - 2, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y - 1, x - 2, kolor);

	if (plansza[y - 1][x + 2] * bierka > 0 || przypieta) 
		wpiszPomocnicza(pomocnicza, y - 1, x + 2, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y - 1, x + 2, kolor);

	if (plansza[y + 1][x - 2] * bierka > 0 || przypieta) 
		wpiszPomocnicza(pomocnicza, y + 1, x - 2, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y + 1, x - 2, kolor);

	if (plansza[y + 1][x + 2] * bierka > 0 || przypieta) 
		wpiszPomocnicza(pomocnicza, y + 1, x + 2, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y + 1, x + 2, kolor);

	if (plansza[y + 2][x - 1] * bierka > 0 || przypieta) 
		wpiszPomocnicza(pomocnicza, y + 2, x - 1, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y + 2, x - 1, kolor);

	if (plansza[y + 2][x + 1] * bierka > 0 || przypieta) 
		wpiszPomocnicza(pomocnicza, y + 2, x + 1, kolor + 2);
	else
		wpiszPomocnicza(pomocnicza, y + 2, x + 1, kolor);
		
}

void gdzieGoniec(int plansza[8][8], int pomocnicza[8][8], int bierka, int y, int x) {
	//funkcja sprawdza wszystkie pola atakowane przez danego goñca i wpisuje odpowiedni¹ wartoœæ do pomocniczej planszy
	int kolor = 0;
	if (bierka > 0)
		kolor = 1;
	int pozycja[2]{}, pozycjaNasz[2]{};
	bool przypieta = czyPrzypieta(pomocnicza, y, x);
	bool szachujaca = czySzachujaca(pomocnicza, y, x);
	pozycjaKrol(plansza, 1 - kolor, pozycja);
	pozycjaKrol(plansza, kolor, pozycjaNasz);
	int krolY = pozycja[0];
	int krolX = pozycja[1];
	int krolNaszY = pozycjaNasz[0];
	int krolNaszX = pozycjaNasz[1];

	for (int i = 1; x + i < 8 && y + i < 8; i++) {
		if (plansza[y + i][x + i] * bierka > 0 || (przypieta && ((krolNaszX < x && krolNaszY > y) || (krolNaszX > x && krolNaszY < y)))) {
			wpiszPomocnicza(pomocnicza, y + i, x + i, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, y + i, x + i, kolor);
		}
		if (szachujaca && krolY > y + i && krolX > x + i )
			wpiszPomocnicza(pomocnicza, y + i, x + i, 6);
		if (plansza[y + i][x + i] != 0) {
			break;
		}
	}

	for (int i = 1; x + i < 8 && y - i >= 0; i++) {
		if (plansza[y - i][x + i] * bierka > 0 || (przypieta && ((krolNaszX < x && krolNaszY < y) || (krolNaszX > x && krolNaszY > y)))) {
			wpiszPomocnicza(pomocnicza, y - i, x + i, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, y - i, x + i, kolor);
		}
		if (szachujaca && krolY < y - i && krolX > x + i)
			wpiszPomocnicza(pomocnicza, y - i, x + i, 6);
		if (plansza[y - i][x + i] != 0) {
			break;
		}
	}

	for (int i = 1; x - i >= 0 && y + i < 8; i++) {
		if (plansza[y + i][x - i] * bierka > 0 || (przypieta && ((krolNaszX < x && krolNaszY < y) || (krolNaszX > x && krolNaszY > y)))) {
			wpiszPomocnicza(pomocnicza, y + i, x - i, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, y + i, x - i, kolor);
		}
		if (szachujaca && krolY > y + i && krolX < x - i)
			wpiszPomocnicza(pomocnicza, y + i, x - i, 6);
		if (plansza[y + i][x - i] != 0) {
			break;
		}
	}

	for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
		if (plansza[y - i][x - i] * bierka > 0 || (przypieta && ((krolNaszX < x && krolNaszY > y) || (krolNaszX > x && krolNaszY < y)))) {
			wpiszPomocnicza(pomocnicza, y - i, x - i, kolor + 2);
		}
		else {
			wpiszPomocnicza(pomocnicza, y - i, x - i, kolor);
		}
		if (szachujaca && krolY < y - i && krolX < x - i)
			wpiszPomocnicza(pomocnicza, y - i, x - i, 6);
		if (plansza[y - i][x - i] != 0) {
			break;
		}
	}
}

void gdzieHetman(int plansza[8][8], int pomocnicza[8][8], int bierka, int y, int x) {
	//funkcja sprawdza wszystkie pola atakowane przez danego hetmana i wpisuje odpowiedni¹ wartoœæ do pomocniczej planszy
	//funkcja jest po³¹czeniem analogicznych funkcji goñca i wie¿y gdy¿ hetman jest po³¹czeniem tych dwóch figur
	gdzieWieza(plansza, pomocnicza, bierka, y, x);
	gdzieGoniec(plansza, pomocnicza, bierka, y, x);
}

void gdzieKrol(int plansza[8][8], int pomocnicza[8][8], int bierka, int y, int x, bool pierwsze) {
	//funkcja sprawdza wszystkie pola atakowane przez danego króla i wpisuje odpowiedni¹ wartoœæ do pomocniczej planszy
	int kolor = 0;
	if (bierka > 0)
		kolor = 1;
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 1; j <= x + 1; j++) {
			if (czyAtakowane(pomocnicza, i, j, kolor) || plansza[i][j] * bierka > 0 || pierwsze) {
				wpiszPomocnicza(pomocnicza, i, j, kolor + 2);
			}
			else {
				wpiszPomocnicza(pomocnicza, i, j, kolor);
			}
		}
	}
}

bool sprawdzWPrzelocie(int plansza[8][8], int krolY, int krolX, int bitaX, int bitaY, int kolor) {
	//funkcja pomocnicza do funkcji gdziePion sprawdzac czy zbicie w przelocie nie ods³ania króla
	bool sprawdz = 0;
	krolY = 8;
	if (kolor == 0)
		kolor--;
	if (krolY == bitaY) {
		if (krolX < bitaX) {
			for (int i = krolX + 1; i < 8; i++) {
				if (plansza[krolY][i] == 0) {
					continue;
				}
				else if (!sprawdz && i >= 6) {
					return 1;
				}
				else if (!sprawdz && ((plansza[krolY][i] == 6 && plansza[krolY][i + 1] == -6) || (plansza[krolY][i] == -6 && plansza[krolY][i + 1] == 6))) {
					i++;
					sprawdz = 1;
				}
				else if (sprawdz && (plansza[krolY][i] != kolor * 1 || plansza[krolY][i] != kolor * 4)) {
					return 1;
				}
				else {
					return 0;
				}
			}
		}
		else {
			for (int i = krolX - 1; i >= 0; i--) {
				if (plansza[krolY][i] == 0) {
					continue;
				}
				else if (!sprawdz && i <= 1) {
					return 1;
				}
				else if (!sprawdz && ((plansza[krolY][i] == 6 && plansza[krolY][i - 1] == -6) || (plansza[krolY][i] == -6 && plansza[krolY][i - 1] == 6))) {
					i++;
					sprawdz = 1;
				}
				else if (sprawdz && (plansza[krolY][i] == kolor * -1 || plansza[krolY][i] == kolor * -4)) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
	}
	else if (krolY - bitaY == krolX - bitaX) {
		if (krolY < bitaY) {
			if (krolX < bitaX) {
				for (int i = 1; krolX + i < 8 && krolY + i < 8; i++) {
					if (plansza[krolY + i][krolX + i] == 0) {
						continue;
					}
					else if(!sprawdz && plansza[krolY + i][krolX + i] == -6 * kolor){
						sprawdz = 1;
					}
					else if (sprawdz && (plansza[krolY + i][krolX + i] == -3 * kolor || plansza[krolY + i][krolX + i] == -4 * kolor)) {
						return 0;
					}
					else {
						return 1;
					}
				}
			}
			else {
				for (int i = 1; krolX - i >= 0 && krolY + i < 8; i++) {
					if (plansza[krolY + i][krolX - i] == 0) {
						continue;
					}
					else if (!sprawdz && plansza[krolY + i][krolX - i] == -6 * kolor) {
						sprawdz = 1;
					}
					else if (sprawdz && (plansza[krolY + i][krolX - i] == -3 * kolor || plansza[krolY + i][krolX - i] == -4 * kolor)) {
						return 0;
					}
					else {
						return 1;
					}
				}
			}
		}
		else {
			if (krolX < bitaX) {
				for (int i = 1; krolX + i < 8 && krolY - i >= 0; i++) {
					if (plansza[krolY - i][krolX + i] == 0) {
						continue;
					}
					else if (!sprawdz && plansza[krolY - i][krolX + i] == -6 * kolor) {
						sprawdz = 1;
					}
					else if (sprawdz && (plansza[krolY - i][krolX + i] == -3 * kolor || plansza[krolY - i][krolX + i] == -4 * kolor)) {
						return 0;
					}
					else {
						return 1;
					}
				}
			}
			else {
				for (int i = 1; krolX - i >= 0 && krolY - i >= 0; i++) {
					if (plansza[krolY - i][krolX - i] == 0) {
						continue;
					}
					else if (!sprawdz && plansza[krolY - i][krolX - i] == -6 * kolor) {
						sprawdz = 1;
					}
					else if (sprawdz && (plansza[krolY - i][krolX - i] == -3 * kolor || plansza[krolY - i][krolX - i] == -4 * kolor)) {
						return 0;
					}
					else {
						return 1;
					}
				}
			}
		}
	}
	return 1;
}

void gdziePion(int plansza[8][8], int pomocnicza[8][8], int bierka, int y, int x) {
	//funkcja sprawdza wszystkie pola atakowane przez danego piona i wpisuje odpowiedni¹ wartoœæ do pomocniczej planszy
	bool przypieta = czyPrzypieta(pomocnicza, y, x);
	int kolor = 0;
	if (bierka > 0)
		kolor = 1;
	int pozycjaNasz[2]{};
	pozycjaKrol(plansza, 1 - kolor, pozycjaNasz);
	int krolNaszY = pozycjaNasz[0];
	int krolNaszX = pozycjaNasz[1];
		
	if (bierka < 0) {
		if (plansza[y + 1][x - 1] > 0 && !przypieta) {	
			wpiszPomocnicza(pomocnicza, y + 1, x - 1, 0);
		}
		else {
			wpiszPomocnicza(pomocnicza, y + 1, x - 1, 2);
		}

		if (y == 4) {	
			if (czyWPrzelocie(pomocnicza, y, x + 1) && !przypieta && sprawdzWPrzelocie(plansza, krolNaszY, krolNaszX, x + 1, y, kolor)) {
				wpiszPomocnicza(pomocnicza, y + 1, x + 1, 1);
			}
			else if (czyWPrzelocie(pomocnicza, y, x - 1) && !przypieta && sprawdzWPrzelocie(plansza, krolNaszY, krolNaszX, x - 1, y, kolor)) {
				wpiszPomocnicza(pomocnicza, y + 1, x - 1, 1);
			}
		}

		if (plansza[y + 1][x] == 0 && (!przypieta || (przypieta && krolNaszY == y))) {
			if (y == 1 && plansza[y + 2][x] == 0) {
				wpiszPomocnicza(pomocnicza, y + 2, x, 8);
			}
			wpiszPomocnicza(pomocnicza, y + 1, x, 8);
		}

		if (plansza[y + 1][x + 1] > 0 && !przypieta) { 
			wpiszPomocnicza(pomocnicza, y + 1, x + 1, 0);
		}
		else {
			wpiszPomocnicza(pomocnicza, y + 1, x + 1, 2);
		}
	}
	else {
		if (plansza[y - 1][x - 1] < 0 && !przypieta) {
			wpiszPomocnicza(pomocnicza, y - 1, x - 1, 1);
		}
		else {
			wpiszPomocnicza(pomocnicza, y - 1, x - 1, 3);
		}
		
		if (y == 3) {
			if (czyWPrzelocie(pomocnicza, y, x + 1) && !przypieta) {
				wpiszPomocnicza(pomocnicza, y - 1, x + 1, 1 && sprawdzWPrzelocie(plansza, krolNaszY, krolNaszX, x + 1, y, kolor));
			}
			else if (czyWPrzelocie(pomocnicza, y, x - 1) && !przypieta && sprawdzWPrzelocie(plansza, krolNaszY, krolNaszX, x + 1, y, kolor)) {
				wpiszPomocnicza(pomocnicza, y - 1, x - 1, 1);
			}
		}

		if (plansza[y - 1][x] == 0 && (!przypieta || (przypieta && krolNaszY == y))) {
			if (y == 6 && plansza[y - 2][x] == 0) {
				wpiszPomocnicza(pomocnicza, y - 2, x, 9);
			}
			wpiszPomocnicza(pomocnicza, y - 1, x, 9);
		}

		if (plansza[y - 1][x + 1] < 0 && !przypieta) {
			wpiszPomocnicza(pomocnicza, y - 1, x + 1, 1);
		}
		else {
			wpiszPomocnicza(pomocnicza, y - 1, x + 1, 3);
		}
	}
}

bool czySzach(int plansza[8][8], int pomocnicza[8][8], int kolor) {
	//funkcja sprawdza czy król znajduje siê pod szachem
	int pozycja[2]{};
	pozycjaKrol(plansza, kolor, pozycja);
	int y = pozycja[0];
	int x = pozycja[1];
	return czyAtakowane(pomocnicza, y, x, kolor);
}

void wypelnijPomocnicza(int plansza[8][8], int pomocnicza[8][8], bool kolor) {
	//trzecia najwa¿niejsza funkcja w programie aktualizuje wartoœci na planszy pomocniczej po ka¿dym ruchu
	int bierka{};

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (czyWPrzelocie(pomocnicza, i, j)) {
					pomocnicza[i][j] = 1024;
			}
			else if (czyRoszada(pomocnicza, i, j)) {
				pomocnicza[i][j] = 2048;
			}
			else 
				pomocnicza[i][j] = 0;
		}
	}

	int pozycjaBialy[2]{}, pozycjaCzarny[2]{};
	pozycjaKrol(plansza, 1, pozycjaBialy);
	pozycjaKrol(plansza, 0, pozycjaCzarny);
	int yBialy = pozycjaBialy[0];
	int xBialy = pozycjaBialy[1];
	int yCzarny = pozycjaCzarny[0];
	int xCzarny = pozycjaCzarny[1];

	sprawdzKrol(plansza, pomocnicza, 0, xCzarny, yCzarny);
	sprawdzKrol(plansza, pomocnicza, 1, xBialy, yBialy);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bierka = plansza[i][j];
			switch (abs(bierka)) {
				case 0:
					break;
				case 1:
					gdzieWieza(plansza,pomocnicza,bierka, i, j);
					break;
				case 2:
					gdzieSkoczek(plansza, pomocnicza, bierka, i, j);
					break;
				case 3:
					gdzieGoniec(plansza, pomocnicza, bierka, i, j);
					break;
				case 4:
					gdzieHetman(plansza, pomocnicza, bierka, i, j);
					break;
				case 5:
					gdzieKrol(plansza, pomocnicza, bierka, i, j, 1);
					break;
				case 6:
					gdziePion(plansza, pomocnicza, bierka, i, j);
					break;
			}
		}
	}

	gdzieKrol(plansza, pomocnicza, 5, yBialy, xBialy, 0);
	gdzieKrol(plansza, pomocnicza, -5, yCzarny, xCzarny, 0);

}