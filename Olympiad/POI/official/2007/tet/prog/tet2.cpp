/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tet2.cpp                                                   *}
{*   Autor:   Tomasz Walen                                               *}
{*   Opis:    Rozwiazanie autorskie.                                     *}
{*                                                                       *}
{*************************************************************************/
#include<algorithm>
#include<list>
#include <cstdio>

#define REP(a,n) for (int a=0; a<(n); ++a)

using namespace std;

//////////////////////////////////////

#define SIZE (2*50000)

int dol[SIZE+1]; // cz�� stosu poni�ej bie��cej pozycji
int iledol; // rozmiar dolnej cz�ci stosu

int gora[SIZE+1]; // cz�� stosu powy�ej bie��cej pozycji
int goraod, gorakoniec; // gorna cz�� stosu znajduje si� w tablicy gora na
                        // pozycjach od goraod do gorakoniec-1

int jest[SIZE]; // czy w dolnej cz�ci stosu wyst�puje dana liczba
int N; // ile jest liczb

int wynik[1000000]; // spamietane ruchy
int ilew = 0; // ile jest inwersji (ile potrzeba ruch�w)

void licz()
{
    bzero(&jest,sizeof(jest));
    bzero(&dol,sizeof(dol));
    
    list<int> s;
    for(int i=2*N-1;i>=0;i--) s.push_back(gora[i]);
    
    iledol=0;
    while(!s.empty()) {
      int x=s.back();s.pop_back();
      if (jest[x]) {
        int j=iledol;
        int y=dol[iledol-1];iledol--;jest[y]=0;
        if (x!=y) {
          wynik[ilew++]=j;
          s.push_back(y);
          s.push_back(x);
        }
      } else {
        jest[x]=1;
        dol[iledol]=x;
        iledol++;
      }
    }
}

int main()
{
  scanf("%d", &N);
  REP(a, 2*N)
  {
    scanf("%d", &gora[a]);
    --gora[a]; // u nas liczby b�d� od 0 do N-1
  }
  licz();
  printf("%d\n", ilew);
  REP(a, ilew)
    printf("%d\n", wynik[a]); 
}
