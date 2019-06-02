/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi�zanie zadania: Liczby Przesmyk�w                              *
 *   Plik:                lic.cpp                                        *
 *   Autor:               Krzysztof Onak                                 *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class DuzaLiczba {
// klasa du�ych dodatnich liczb ca�kowitych
public:

  DuzaLiczba(int malaLiczba = 0) : cyfry(0)
  // konstruktor, inicjacja zwyk�� liczb� ca�kowit�
  {
    // dodajemy kolejne cyfry naszej liczby
    while (malaLiczba != 0) {
      cyfry.push_back(malaLiczba % PODSTAWA);
      malaLiczba /= PODSTAWA;
    }
  }
  
  const DuzaLiczba& operator+=(const DuzaLiczba &skladnik)
  // zwi�kszenie liczby o podan� warto��
  {
    int przeniesienie = 0;
    int stop = max(cyfry.size(), skladnik.cyfry.size()); // wi�ksza z d�ugo�ci
    // zwyk�e dodawanie kolejnych cyfr w p�tli
    for (int i = 0; i < stop; ++i) {
      przeniesienie += cyfra(i) + skladnik.cyfra(i);
      zmienCyfre(i, przeniesienie % PODSTAWA);
      przeniesienie /= PODSTAWA;
    }
    // sprawdzenie czy nie nast�pi�o przepe�nienie
    if (przeniesienie != 0) zmienCyfre(stop, przeniesienie);
    return *this;
  }

  const DuzaLiczba& operator-=(const DuzaLiczba &odjemnik)
  // zmiejszenie liczby o podan� warto��;
  // zak�adamy, �e wynik odejmowania jest nieujemny
  {
    int przeniesienie = 0, stop = cyfry.size();
    // w p�tli odejmujemy kolejne cyfry
    for (int i = 0; i < stop; ++i) {
      int roznica = przeniesienie + cyfra(i) - odjemnik.cyfra(i);
      if (roznica < 0) {
        przeniesienie = -1;
	roznica += PODSTAWA;
      } else {
        przeniesienie = 0;
      }
      zmienCyfre(i, roznica);
    }
    // je�li jakie� pocz�tkowe cyfry si� wyzerowa�y,
    // to je usuwamy
    while (!cyfry.empty() && cyfry.back() == 0)
      cyfry.pop_back();
    return *this;
  }
  
  bool operator<(const DuzaLiczba& druga) const
  // por�wnanie dw�ch du�ych liczb
  {
    // je�li druga liczba jest d�u�sza, to na pewno jest wi�ksza
    if (druga.cyfry.size() > cyfry.size()) return true;
    // w p�tli por�wnujemy kolejne cyfry
    for (int i = cyfry.size() - 1; i >= 0; --i) {
      int a = cyfra(i), b = druga.cyfra(i);
      if (a < b) return true;
      if (a > b) return false;
    }
    // liczby s� r�wne
    return false;
  }
  
private:

  // podstawa systemu, w kt�rym wykonujemy dzia�ania
  static const int PODSTAWA = 1024*1024*1024; // = 2^30
  
  // kolejne cyfry liczby w systemie o podstawie PODSTAWA;
  // zak�adamy, �e najbardziej znacz�ca cyfra (o ile istnieje)
  // jest r�na od zera
  vector<int> cyfry;
  
  int cyfra(int pos) const
  // zwraca podan� cyfr� z reprezentacji lub zero,
  // je�li cyfra wykracza poza reprezentacj�
  {
    return (pos < (int)cyfry.size()) ? cyfry[pos] : 0;
  }

  void zmienCyfre(int pos, int wart)
  // je�li istnieje cyfra o numerze pos w reprezentacji,
  // to jest ona zamieniana na wart,
  // wpp. zak�adamy, �e powstaje nowa cyfra
  // rozszerzaj�ca dotychczasow� reprezentacj�
  {
    if (pos < (int)cyfry.size())
      cyfry[pos] = wart;
    else
      cyfry.push_back(wart);
  }

};

// przydatne sta�e
const DuzaLiczba ZERO(0);
const DuzaLiczba JEDEN(1);

class LiczbyCiagow {
// podaje liczby ci�g�w o zadanej d�ugo�ci przy ustalonej
// warto�ci m (maksymalna liczba minus�w pod rz�d)
public:

  // inicjacja warto�ci� m
  LiczbyCiagow(int mm) : m(mm) {liczby.push_back(JEDEN);}
  
  const DuzaLiczba& operator[](int indeks) const
  // zwraca liczb� ci�g�w o d�ugo�ci indeks
  {
    // warto�ci wynikaj�ce z umowy
    if (indeks < -1) return ZERO;
    if (indeks == -1) return JEDEN;
    // ewentualne doliczenie brakuj�cych warto�ci
    for (int i = liczby.size(); i <= indeks; ++i) {
      liczby.push_back(liczby[i - 1]);
      liczby[i] += liczby[i - 1];
      liczby[i] -= (*this)[i - m - 2];
    }
    return liczby[indeks];
  }
  
  // zwraca warto�� m
  int podajM() const {return m;}
  
private:
  // liczba m - ograniczenie na liczb� minus�w pod rz�d
  int m;
  // wektor dotychczas obliczonych warto�ci
  mutable vector<DuzaLiczba> liczby;
};

void odkoduj(const string &zakodowana, DuzaLiczba &odkodowana,
             const LiczbyCiagow &L)
// odkodowuje ci�g plus�w i minus�w zakodowana,
// wynik zapisuje w odkodowana,
// korzysta ze struktury podaj�cej liczby ci�g�w L
{
  int rozmiar = zakodowana.size(), m = L.podajM();
  odkodowana = ZERO;
  // uwzgl�dniamy kr�tsze ci�gi
  for (int i = 1; i < rozmiar; ++i)
    odkodowana += L[i];
  for (int i = 0; i < rozmiar; ++i) {
    // niezmiennik: wynik = odkodowana + (numer ci�gu zakodowana[i..rozmiar-1]
    //                                    w�r�d ci�g�w tej samej d�ugo�ci)
    int rozmiarPodciagu = rozmiar - i;
    odkodowana -= L[rozmiarPodciagu - m - 2];
    if (zakodowana[i] == '+') odkodowana += L[rozmiarPodciagu - 1];
  }
}

void wypiszZakodowana(const DuzaLiczba &odkodowana, ostream &strumien,
                      const LiczbyCiagow &L)
// koduje liczbe odkodowana,
// wynik zapisuje bezpo�rednio w strumieniu strumien,
// korzysta ze struktury podaj�cej liczby ci�g�w L
{
  DuzaLiczba liczba = odkodowana;
  int m = L.podajM();
  int rozmiar;
  // ustalamy d�ugo�� ci�gu
  for (rozmiar = 1; !(liczba < L[rozmiar]); ++rozmiar)
    liczba -= L[rozmiar];
  // wypisujemy kolejne cyfry
  for (int i = rozmiar; i > 0; --i) {
    // w tej chwili pozostaje wypisa� ci�g d�ugo�ci i
    // o numerze liczba w�r�d ci�g�w tej d�ugo�ci
    liczba += L[i - m - 2]; // kr�tsze ci�gi psute przez pocz�tkowy minus
    // decyzja '+' czy '-'
    if (liczba < L[i - 1]) {
      strumien << '-';
    } else {
      strumien << '+';
      liczba -= L[i - 1];
    }
  }
}

int main()
// g��wny program
{
  int m1, m2, n;
  cin >> m1 >> m2 >> n;
  LiczbyCiagow ciagiWejsciowe(m1), ciagiWyjsciowe(m2);
  // w p�tli przetwarzamy kolejne ci�gi wej�ciowe
  for (int i = 0; i < n; ++i) {
    string staraLiczba;
    // wczytanie ci�gu
    cin >> staraLiczba;
    DuzaLiczba odkodowana;
    // odkodowanie
    odkoduj(staraLiczba, odkodowana, ciagiWejsciowe);
    // zakodowanie i zapisanie
    wypiszZakodowana(odkodowana, cout, ciagiWyjsciowe);
    cout << '\n';
  }
}
