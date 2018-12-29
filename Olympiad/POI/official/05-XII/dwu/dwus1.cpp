/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: DWU (Dwuszereg)                                *
 *   Plik:                dwus1.cpp                                      *
 *   Autor:               Arkadiusz Paterek                              *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        nie u�ywamy tablic first i second,             *
 *                        koszt ro�nie do O(n^2)                         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define FOR(i,n) for (int i = 0; i < int(n); ++i)

const int MAX_N = 50000;
const int MAX_X = 100000;

vector < pair < int, int > > soldiers;  // dwuszereg - wzrost �o�nierzy
vector < bool > visited;        // visited[i] == pozycja i-ta zosta�a odwiedzona

int find(int x, int j)
{
  int n = soldiers.size();
  FOR(i, n)
      if (i != j)
    if (soldiers[i].first == x || soldiers[i].second == x)
      return i;
  return -1;
}

int main()
{
  int n;
  cin >> n;
  soldiers.resize(n);
  visited.resize(n, false);

  FOR(i, n) {
    int x;
    cin >> x;
    soldiers[i].first = x;
  }

  FOR(i, n) {
    int x;
    cin >> x;
    soldiers[i].second = x;
  }

  int sum = 0;
  FOR(i, n)
      if (!visited[i]) {
    visited[i] = true;
    // specjalny przypadek - dw�ch �o�nierzy tego samego wzrostu w jednej kolumnie
    if (soldiers[i].first == soldiers[i].second)
      continue;

    int count = 0;              // liczba potrzebnych zamian, gdy nie zamieniamy pierwszej pary
    int count_rev = 1;          // liczba potrzebnych zamian, gdy zamieniamy pierwsz� par�

    // odwiedzamy �a�cuch pozycji zale�nych od pierwszego �o�nierza,
    // mamy dwa przypadki: albo wr�cimy do pozycji i-tej, albo nie
    int j = i;
    int x = soldiers[i].first;
    int k;
    while (true) {
      k = find(x, j);
      if (k == -1)
        break;                  // �a�cuch si� ko�czy
      if (k == i)
        break;                  // �a�cuch zamyka si� w cykl

      if (x == soldiers[k].second) {
        ++count_rev;
        x = soldiers[k].first;
      }
      else {
        ++count;
        x = soldiers[k].second;
      }
      visited[k] = true;
      j = k;
    }

    if (k == -1) {              // �a�cuch nie zamkn�� si� w cykl
      // odwiedzamy �a�cuch pozycji zale�nych od drugiego �o�nierza
      int j = i;
      int x = soldiers[i].second;

      while (true) {
        k = find(x, j);
        if (k == -1)
          break;

        if (soldiers[k].first == x) {
          ++count_rev;
          x = soldiers[k].second;
        }
        else {
          ++count;
          x = soldiers[k].first;
        }
        visited[k] = true;
        j = k;
      }
    }

    sum += min(count, count_rev);
  }

  cout << sum << endl;
}
