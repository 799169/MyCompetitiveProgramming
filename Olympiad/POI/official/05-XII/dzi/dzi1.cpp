/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi1.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z�o�ono�� obliczeniowa jak i pami�ciowa jest   *
 *                        liniowa. Przeszukiwanie grafu (DFS) jest       *
 *                        zrealizowane na wlasnym stosie (z powodu       *
 *                        potencjalnie du�ej g��boko�ci rekursji).       *
 *                        Wykorzystywane sa struktury danych z STL.      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 1000000;       //maksymalna liczba wierzcholkow

vector < int >kraw[MAXN];       //graf reprezentowany przez "listy sasiedztwa"
int deg[MAXN], parent[MAXN];    /*stopnie oraz ojcowie wierzcho�k�w
                                   w drzewie przeszukiwania w g��b */
stack < int >stos;
long long k, r;
int n, m;                       //liczba wierzcholkow oraz liczba krawedzi

//wczytywanie danych
void czytaj()
{
  scanf("%d %d %lld", &n, &m, &k);
  if (m < n) {
    for (int i = 0; i < m; ++i) {
      int a, b;
      scanf("%d %d", &a, &b);
      //dodajemy krawedz do grafu
      kraw[--a].push_back(--b);
      kraw[b].push_back(a);
      deg[a]++;
      deg[b]++;
    }
  }
}

/*przeszukiwanie grafu w g��b, zrealizowane na w��snym stosie*/
void dfs(int x)
{
  stos.push(x);                 //wierzcho�ek x jest jedynym elementem stosu
  parent[x] = x;
  int wezly = 0;                //liczba wierzcho�k�w tej sp�jnej sk�adowej o stopniu >=2
  while (!stos.empty()) {
    int v = stos.top();
    stos.pop();                 //zdejmujemy wierzcho�ek ze stosu
    wezly += (deg[v] >= 2);
    int liscie = 0, j = 0;

    for (int i = 0; i < (int) kraw[v].size(); ++i) {
      int u = kraw[v][i];
      if (parent[u] == -1) {
        //zaznaczamy wierzcho�ek jako odwiedzony i wrzucamy na stos
        parent[u] = v;
        stos.push(u);
      }
      else if (u != parent[v])
        r = 0;                  //skladowa nie jest drzewem

      if (deg[u] == 1)
        liscie++;
      else
        j++;
    }

    if (j > 2)
      r = 0;                    //graf nie jest pladzielny

    for (int i = 2; i <= liscie; ++i) //permutowanie wierzcho�k�w stopnia 1
      r = (r * i) % k;
  }
  if (wezly >= 2)               //symetria wzgledem prostej poziomej
    r = (r * 2) % k;
}

//g��wna procedura progamu, procedura ta zlicza liczb� rozstawie� ptaszk�w
void licz()
{
  for (int i = 0; i < n; ++i)
    parent[i] = -1;             //wierzcho�ki nie s� odwiedzone
  int skladowe = 0;             //liczba sp�jnych sk�adowych
  int izolowane = 0;            //liczba wierzcho�k�w izolowanych
  r = (m < n);
  for (int i = 0; i < n; ++i)
    if (parent[i] == -1)
      if (deg[i] > 0) {
        r = (r * (2 * (++skladowe))) % k;
        dfs(i);
      }
      else
        izolowane++;

  //trzeba uwzgl�dni� dowolne rozstawienie wierzcho�k�w izolowanych
  for (int i = n + 1; i >= n + 2 - izolowane; --i)
    r = (r * i) % k;
  printf("%lld\n", r);
}

int main()
{
  czytaj();
  licz();
  return 0;
}
