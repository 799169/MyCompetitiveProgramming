(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                skab2.pas                                      *
 *   Autor:               Pawe� Wolff                                    *
 *   Opis:                Rozwi�zanie niepoprawne zadania SKARBONKI      *
 *                                                                       *
 *************************************************************************)

program Skarbonki_b2;


const
  MAX_N = 1000000;


var
  n: longint;
  klucz: array [1..MAX_N] of longint;
    { klucz[i] = numer skarbonki, w kt�rej znajduje si� i-ty klucz;
      tablica ta definiuje graf skierowany: wierzcho�kami s� klucze
      o numerach 1, 2, ..., n, a kraw�dzie prowadz� od wierzcho�ka 
      o numerze i do wierzcho�ka o numerze klucz[i] (dla wszystkich
      i = 1, 2, ..., n); zatem jest to graf, w kt�rym stopie� wyj�ciowy
      ka�dego wierzcho�ka jest r�wny 1 }


procedure WczytajDane;
var
  i: longint;

begin
  Readln(n);
  
  for i := 1 to n do
    Readln(klucz[i]);
end;


function IleCykli: longint;
{ Liczymy liczb� cykli w grafie zdefiniowanym przez tablic� klucz.
  Mo�emy to zrobi� (niepoprawnie) w nast�puj�cy spos�b.
  B�dziemy odwiedza� wierzcho�ki grafu, poruszaj�c si� wzd�u� kraw�dzi.
  Po przej�ciu dan� kraw�dzi�, b�dziemy j� usuwa�.
  (Zauwa�my zatem, �e w ka�dym momencie dzia�ania algorytmu stopie�
  wyj�ciowy ka�dego wierzcho�ka wynosi 0 lub 1.)
  Z ka�dego wierzcho�ka (powiedzmy o numerze i), z kt�rego wychodzi
  kraw�d�, rozpoczynamy odwiedzanie nast�pnych wierzcho�k�w
  (poruszaj�c si� wzd�u� kraw�dzi i przy tym usuwaj�c je).
  Takie odwiedzanie ko�czy si�, gdy znajdziemy si� w wierzcho�ku, z kt�rego
  nie wychodzi �adna kraw�d�. 
  W�wczas, je�li numer tego wierzcho�ka
  - jest r�wny i, to znaczy, �e znale�li�my nowy cykl,
  - jest r�ny od i, to znaczy, �e dotarli�my do wierzcho�ka, kt�ry
    znajduje si� na cyklu ju� wcze�niej znalezionym bad� te� z kt�rego
    wcze�niej dotarli�my do takowego cyklu. }
var
  i, j, pom, lCykli: longint;

begin
  lCykli := 0;

  for i := 1 to n do
    if klucz[i] <> 0 then begin
      j := i;
      repeat
        pom := klucz[j];
        klucz[j] := 0;
        j := pom;
      until klucz[j] = 0;
      
      if j = i then
        Inc(lCykli);
    end;

  IleCykli := lCykli;
end;


begin
  WczytajDane;
  Writeln(IleCykli);
end.
