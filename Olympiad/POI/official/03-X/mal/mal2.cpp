/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi�zanie zadania: Ma�pki                                         *
 *   Plik:                mal2.cpp                                       *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <iostream>
using namespace std;

// ograniczenia
const int MAXN = 200000;
const int MAXM = 2 * MAXN;

// oznacza, �e ma�pka nic nie trzyma w danej r�ce
const int PUSZCZONA = -1;

// ma�pka na drzewie, nigdy nie spad�a
const int NIGDY = -1;
// ma�pka le�y na ziemi
const int ZIEMIA = -2;

int n, m;
int lapki[MAXN][2];  // opisuje, kogo trzymaj� lapki ma�pki
int uchwyt[MAXM][2]; // opisuje kto kogo pu�ci� w danej chwili czasu

void wczytaj()
{
  cin >> n >> m;
  // wczytujemy stan �apek ma�pek
  for(int i = 0; i < n; ++i) {
    int l, p;
    cin >> l >> p;
    lapki[i][0] = l == -1 ? PUSZCZONA : l - 1;
    lapki[i][1] = p == -1 ? PUSZCZONA : p - 1;
  }
  // wczytujemy kto kogo pu�ci� i uaktualniamy odpowiednio stan �apek
  for(int i = 0; i < m; ++i) {
    int malpa, lapka;
    cin >> malpa >> lapka;
    uchwyt[i][0] = lapki[--malpa][--lapka];
    uchwyt[i][1] = malpa;
    lapki[malpa][lapka] = PUSZCZONA;
  }
}

/************ wzbogacone zbiory roz��czne *******************/
struct {
  int ojciec;
  int pozycja;
  int czas;
} zbiory[MAXN];

// znajdujemy reprezentanta
int reprezentant(int v) {
  int ojciec = zbiory[v].ojciec;
  if (ojciec != v) {
    int r = reprezentant(ojciec);
    if (zbiory[v].czas == ZIEMIA)
      zbiory[v].czas = zbiory[ojciec].czas;
    zbiory[v].ojciec = r;
  }
  return zbiory[v].ojciec;
}

// ��czymy reprezentant�w
void polacz(int v, int w) {
  if (v == w) return;
  if (zbiory[v].pozycja > zbiory[w].pozycja) {
    zbiory[w].ojciec = v;
  } else {
    zbiory[v].ojciec = w;
    if (zbiory[v].pozycja == zbiory[w].pozycja)
      ++zbiory[w].pozycja;
  }
}

// przygotowujemy zbiory rozlaczne
void przygotujZbiory()
{
  for(int i = 0; i < n; ++i) {
    zbiory[i].ojciec = i;
    zbiory[i].pozycja = 0;
    zbiory[i].czas = ZIEMIA;
  }
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < 2; ++j)
      if (lapki[i][j] != PUSZCZONA)
        polacz(reprezentant(i),reprezentant(lapki[i][j]));
}
/*********************************************************/


void przetworz()
{
  // ma�pki, kt�re w og�le nie spad�y
  zbiory[reprezentant(0)].czas = NIGDY;
  // dodajemy kolejne uchwyty
  for(int i = m - 1; i >= 0; --i) {
    int v = reprezentant(uchwyt[i][0]), w = reprezentant(uchwyt[i][1]);
    int drzewo = reprezentant(0);
    // by� mo�e kto� przyczepi� si� do drzewa
    if (v == drzewo && v != w) {
      zbiory[w].czas = i;
    } else if (w == drzewo && v != w) {
      zbiory[v].czas = i;
    }
    polacz(v, w);
  }
}

void wypisz()
{
  for(int i = 0; i < n; ++i) {
    reprezentant(i);  // uzyskujemy dobry czas ma�pki w zbiory[i]
    cout << zbiory[i].czas << '\n';
  }
}

int main()
{
  wczytaj();
  przygotujZbiory();
  przetworz();
  wypisz();
}
