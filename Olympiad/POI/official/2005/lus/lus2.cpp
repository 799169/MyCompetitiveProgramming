/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: LUS (Lustrzana pu�apka)                        *
 *   Plik:                lus2.cpp                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Implementacja rozwi�zania wzorcowego w C++,    *
 *                        na podstawie lus2.pas                          *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
using namespace std;

#define MAX_ROZM 1000           // maksymalna d�ugo�� boku skrzynki


short int licznik, ilosc;
char rzedy[MAX_ROZM + 1];       // tablica warto�ci ord
int x, y, z;                    // rozmiary skrzynki
int wyn_a, wyn_b, wyn_c;        // najlepsze skierowanie lasera
long long wyn_odl;              // d�ugo�� drogi dla najlepszego skierowania lasera
bool koniec;                    // koniec=true oznacza, �e znale�li�my rozwi�zanie
int odl;                        // odleg�o�� rozwa�anych punkt�w skierowania lasera
         // od rogu skrzynki
int max_czas;                   // maksymalny czas lotu promienia, r�wny 2*NWW(x,y,z)
long long droga;                // d�ugo�� drogi lasera aktualnie rozwa�anego skierowania
int a1, b1;                     // zmienne pomocnicze w p�tlach


/* POMOCNICZE FUNKCJE ARYTMETYCZNE */

/* Najwi�kszy wsp�lny dzielnik */
int NWD(int a, int b)
{
  if (!b)
    return a;
  else
    return NWD(b, a % b);
}                               //NWD

/* Najmniejsza wsp�lna wielokrotno�� */
int NWW(int a, int b)
{
  int d = NWD(a, b);
  if (!d)                       // na pewno co najmniej jedna z liczb jest zerem
    return 0;
  else
    return int (((long long) (a) * (long long) (b)) / d);
}                               //NWW

/* Funkcja oblicza ord(x). */
char rzad(int x)
{
  char wynik = 0;
  int pom = x;
  while (!(pom % 2)) {
    pom /= 2;
    wynik++;
  }                             //while
  return wynik;
}                               //rzad

/* KONIEC FUNKCJI ARYTMETYCZNYCH */


/* Funkcja dla danego skierowania lasera oblicza pierwszy czas
powrotu promienia lasera do �r�d�a. */
int licz_czas(int a, int b, int c)
{
  int a1, b1, c1;
  if (!a)
    a1 = 1;
  else
    a1 = NWW(2 * x, a) / a;

  if (!b)
    b1 = 1;
  else
    b1 = NWW(2 * y, b) / b;

  if (!c)
    c1 = 1;
  else
    c1 = NWW(2 * z, c) / c;
  return NWW(NWW(a1, b1), c1);
}                               //licz_czas

/* Funkcja dla danego skierowania lasera oblicza drog�, jak� przeb�dzie
promie� lasera, zanim trafi spowrotem do �r�d�a. */
long long licz_droge(int a, int b, int c)
{
  return (long long) (licz_czas(a, b, c)) * (long long) (a + b + c);
}                               //licz_droge


/* Procedura oblicza wszystkie potencjalnie potrzebne rz�dy i je zapami�tuje
w tablicy rzedy. */
void licz_rzedy()
{
  for (short int i = 1; i <= MAX_ROZM; ++i)
    rzedy[i] = rzad(i);
}                               //licz_rzedy


/* Funkcja sprawdza dla danego skierowania lasera, czy laser
uderzy w jak�kolwiek kraw�d� skrzynki. */
bool trafi(int a, int b, int c)
{
  return rzedy[a] - rzedy[b] == rzedy[x] - rzedy[y] ||
      rzedy[b] - rzedy[c] == rzedy[y] - rzedy[z] ||
      rzedy[a] - rzedy[c] == rzedy[x] - rzedy[z];
}                               //trafi



/* Inicjacja zmiennych. */
void inicjuj()
{
  koniec = false;
  max_czas = licz_czas(1, 1, 1);
  wyn_odl = 0;
}                               //inicjuj

/* Procedura analizuj�ca dane skierowanie strza�u. */
void sprawdz(int a, int b, int c)
{
  if (NWD(NWD(a, b), c) == 1 && // rozwa�amy tylko tr�jki "wzgl�dnie pierwsze"
      !trafi(a, b, c))          // strza� nie trafia w kraw�d�
  {
    droga = licz_droge(a, b, c);
    if (droga > wyn_odl)        // uzyskali�my najd�u�sz� z dotychczasowych drog�
    {
      wyn_odl = droga;
      wyn_a = a;
      wyn_b = b;
      wyn_c = c;
    }                           //if
    if (wyn_odl == (long long) (max_czas) * (long long) (a + b + c))
      /* uzyskali�my najd�u�sz� mo�liw� drog� */
      koniec = true;
  }                             //if
}                               //sprawdz


int main()
{
  licz_rzedy();
  scanf("%d\n", &ilosc);
  for (licznik = 1; licznik <= ilosc; ++licznik) {
    scanf("%d %d %d\n", &x, &y, &z);
    inicjuj();
    odl = 1;
    /* p�tla po kolejnych odleg�o�ciach od rogu skrzynki */
    while (!koniec && odl < x + y + z) {
      for (a1 = 0; a1 <= min(odl, x - 1); ++a1)
        if (!koniec)
          for (b1 = 0; b1 <= min(odl - a1, y - 1); ++b1)
            if (odl - a1 - b1 < z && !koniec)
              sprawdz(x - a1, y - b1, z - (odl - a1 - b1));
      odl++;
    }                           //while
    printf("%d %d %d\n", wyn_a, wyn_b, wyn_c);
  }                             //for
  return 0;
}                               //main
