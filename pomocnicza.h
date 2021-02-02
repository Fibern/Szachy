#pragma once

bool czyAtakowane(int pomocnicza[8][8], int y, int x, int kolor);
bool czyRuch(int pomocnicza[8][8], int y, int x, int kolor);
bool czyPrzypieta(int pomocnicza[8][8], int y, int x);
bool czyRoszada(int pomocnicza[8][8], int y, int x);
bool czySzachowane(int pomocnicza[8][8], int y, int x);
bool czySzachujaca(int pomocnicza[8][8], int y, int x);
bool czyWPrzelocie(int pomocnicza[8][8], int y, int x);
void gdzieGoniec(int plansza[8][8], int pomocznicza[8][8], int bierka, int y, int x);
void gdzieHetman(int plansza[8][8], int pomocznicza[8][8], int bierka, int y, int x);
void gdzieKrol(int plansza[8][8], int pomocznicza[8][8], int bierka, int y, int x, bool pierwsza);
void gdziePion(int plansza[8][8], int pomocznicza[8][8], int bierka, int y, int x);
void gdzieSkoczek(int plansza[8][8], int pomocznicza[8][8], int bierka, int y, int x);
void gdzieWieza(int plansza[8][8], int pomocznicza[8][8], int bierka, int y, int x);
void pozycjaKrol(int plansza[8][8], int kolor, int pozycja [2]);
void sprawdzKrol(int plansza[8][8], int pomocznicza[8][8], int kolor, int x, int y);
bool sprawdzWPrzelocie(int plansza[8][8], int krolY, int krolX, int bitaX, int bitaY, int kolor);
void usunRoszada(int pomocnicza[8][8], int y, int x);
void wpiszPomocnicza(int pomocnicza[8][8], int y, int x, int bit);
void wypelnijPomocnicza(int plansza[8][8], int pomocznicza[8][8], bool kolor);
bool czySzach(int pomocnicza[8][8], int plansza[8][8], int kolor);