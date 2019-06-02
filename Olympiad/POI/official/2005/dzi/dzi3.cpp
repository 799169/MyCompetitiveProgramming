/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi3.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Rozwi�zanie poprawne o zlozonosci O(n log * n).*
 *                        Z�o�ono�� pami�ciowa jest liniowa. Program ten *
 *                        nie przechowuje w pami�ci kraw�dzi grafu,      *
 *                        wykorzystuje reprezentacj� zbior�w roz��cznych *
 *                        Find & Union w celu wykrywania cykli.          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;       //maksymalna liczba wierzcho�k�w

int deg[MAXN];                  //tablica w kt�rej utrzymywane s� stopnie wierzcho�k�w
int fu[MAXN];                   //tablica w kt�rej pami�tana jest struktura Find & Union
//tablice pomocnicze do sprawdzania pladzielnosci i symetrii
int wezly[MAXN], liscie[MAXN], sasiad[MAXN];
long long k, r;
int n, m;                       //liczba wierzcho�k�w oraz liczba kraw�dzi

/*funkcja ta zwraca numer sk�adowej do kt�rej nale�y
 w danej chwili wierzcho�ek*/
int fufind(int x)
{
  if (fu[x] < 0)
    return x;
  //kompresja scie�ki
  fu[x] = fufind(fu[x]);
  return fu[x];
}

/*procedura uaktualnia informacje w tablicach pomocniczych
po dodaniu do grafu kraw�dzi (a,b)*/
void dodaj(int a, int b)
{
  deg[a]++;
  if (deg[a] == 1)
    sasiad[a] = b;
  else {
    wezly[b]++;
    if (deg[a] == 2)
      wezly[sasiad[a]]++;
  }
}

/*funkcja ta wczytuje kraw�dzie i sprawdza czy graf jest lasem*/
bool cykl()
{
  for (int i = 1; i <= m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    dodaj(a, b);
    dodaj(b, a);

    a = fufind(a);
    b = fufind(b);
    if (a == b)
      /*wierzcho�ki nale�a do tej samej
         sp�jnej sk�adowej, zatem powstaje cykl */
      return true;

    if (fu[a] < fu[b])          //��czenie wed�ug rangi
      swap(a, b);

    fu[b] += fu[a];
    fu[a] = b;

  }
  return false;
}

//funkcja ta sprawdza, czy graf jest pladzielny
bool pladzielny()
{
  for (int i = 1; i <= n; ++i)
    if (wezly[i] > 2)
      return false;
    else
      wezly[i] = 0;
  return true;
}

void inicjuj()
{
  for (int i = 1; i <= n; ++i) {
    deg[i] = 0;
    fu[i] = -1;                 //ka�dy wierzcho�ek nale�y do innego zbioru
    liscie[i] = 0;
    wezly[i] = 0;
  }
}

//g��wna procedura programu, zlicza wszystkie konfiguracje
void licz()
{
  r = 1;
  scanf("%d %d %lld", &n, &m, &k);
  inicjuj();

  if (cykl() || (!pladzielny())) {
    printf("0\n");
    return;
  }

  int izolowane = 0;
  //zliczam liczbe wierzcho�k�w o poszczeg�lnych stopniach
  for (int i = 1; i <= n; ++i)
    if (deg[i] == 0)
      izolowane++;
    else if (deg[i] == 1)
      r = (r * (++liscie[sasiad[i]])) % k;
    else
      wezly[fufind(i)]++;

  int skladowe = 0;
  for (int i = 1; i <= n; ++i)
    if (fu[i] < -1)
      //wierzcho�ek i jest korzeniem sk�adowej o liczbie wierzcholkow > 1
    {
      r = (r * (2 * (++skladowe))) % k;
      if (wezly[i] >= 2)        //sk�adowa nie jest symetryczna
        r = (r * 2) % k;
    }

  //trzeba jeszcze doliczy� rozstawienia wierzcho�k�w izolowanych
  for (int i = n + 1; i >= n + 2 - izolowane; --i)
    r = (r * i) % k;
  printf("%lld\n", r);
}

int main()
{
  licz();
  return 0;
}
