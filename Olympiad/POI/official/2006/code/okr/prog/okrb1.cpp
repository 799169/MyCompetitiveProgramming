/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s��w)                              *
 *   Plik:                okrb1.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie niepoprawne, bo w zly sposob       *
 *                        korzysta z tablicy P:                          *
 *                          prefiks dlugosci n % (n-P[n]) jest           *
 *                          jednoczesnie sufiksem, ale nie ma gwarancji, *
 *                          ze najkrotszym, np. "abcabdabcab" ---        *
 *                          najkrotszy sufikso-prefix ma dlugosc 2, ale  *
 *                          n % (n-P[n]) = 11 % (11-5) = 5               *
 *                        Zlozonosc obliczeniowa O(n)                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

void LiczP (char tekst[], int P[], int n) {
     P[0] = P[1] = 0;
     int t=0;
     for (int i=2; i <= n; ++i) {
         while ((t != 0) && (tekst[i] != tekst[t+1])) t=P[t];
         if (tekst[i] == tekst[t+1]) ++t;
         P[i]=t;
     }
}

int main (void) {
    int n;
    long long odp=0;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    scanf("%s", tekst);

    int *P = new int[n+1];
    /* cofamy, zeby, jak w podrecznikowych algorytmach,
    indeksowac litery slowa od 1, a nie od 0 */
    --tekst;

    LiczP(tekst, P, n);
    /* Blad --- to nie prawda, ze najkrotszy prefikso-sufiks ma dlugosc
       n % (n-P[n]), choc faktycznie n-P[n] jest dlugoscia najkrotszego okresu */
    for (int i=1; i<=n; ++i) {
        if (!P[i]) continue;
        if (i % (i-P[i]))
           odp += i - (i % (i-P[i]));
        else
            odp += P[i];
    }
    printf("%lld\n", odp);

    return 0;
}
