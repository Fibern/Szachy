#pragma once

int literaNaKolumne(int a);
int cyfraNaRzad(int a);
int zamien(int xBijace, int yBijace, int xBite, int yBite, int plansza[8][8], int pomocnicza[8][8]);
void wieza(std::string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]);
void skoczek(std::string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]);
void goniec(std::string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]);
void hetman(std::string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]);
void krol(std::string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]);
void pion(std::string ruch, int plansza[8][8], int pomocnicza[8][8], int kolor, int zwrot[8]);