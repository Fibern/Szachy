#pragma once

void gra(int tryb, std::string partia);
void wyswietlPlansze(int plansza[8][8]);
void wyswietlRuchy(std::string* gra, int licznik);
void wyswietlRuchy(int numer, std::string* gra, int licznik);
void wpisz(std::string ruch, std::string* gra, int licznik);
void wyswietl(int pomocnicza[8][8]);
void sprawdzCzyWPrzelocie(int plansza[8][8], int pomocnicza[8][8], int kolor);
bool sprawdzPat(int pomocnicza[8][8], int kolor);
bool czyKrolSprawdz(int pomocnicza[8][8], int plansza[8][8], int krolY, int krolX, int y, int x);
bool czyKrol(int plansza[8][8], int pomocnicza[8][8], int kolor);
bool czyZaslona(int pomocnicza[8][8], bool kolor);
int ileSzachuj¹cych(int pomocnicza[8][8]);
bool zapiszGre(std::string plik, std::string gra[500], int licznik);
bool wczytanie(std::string partia, std::string gra[500]);
void pomoc();