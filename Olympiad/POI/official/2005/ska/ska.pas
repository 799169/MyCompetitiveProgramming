(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                ska.pas                                        *
 *   Autor:               Pawe� Wolff                                    *
 *   Opis:                Rozwi�zanie wzorcowe zadania SKARBONKI         *
 *                                                                       *
 *************************************************************************)

program Skarbonki;


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

  numer: array [1..MAX_N] of longint;
    { ta tablica b�dzie potrzebna w funkcji IleCykli;
      numer[j] = 0: j-ty wierzcho�ek jest "nieodwiedzony"
      numer[j] = i: j-ty wierzcho�ek zosta� "odwiedzony z wierzcho�ka i" }


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
  Dzi�ki temu, �e stopie� wyj�ciowy ka�dego wierzcho�ka grafu wynosi 1,
  mo�emy to zrobi� w nast�puj�cy spos�b.
  Pocz�tkowo wszystkie wierzcho�ki oznaczamy jako "nieodwiedzone".
  Nast�pnie z ka�dego wierzcho�ka (powiedzmy o numerze i) odwiedzamy
  "nieodwiedzone" od tej pory wierzcho�ki (z ka�dego kolejnego wychodz�c
  jedyn� kraw�dzi�), zaznaczaj�c, �e zosta�y "odwiedzone z wierzcho�ka i".
  Je�eli napotkamy wierzcho�ek, kt�ry zosta� ju�
  "odwiedzony z wierzcho�ka j", to znaczy, �e:
  - znale�li�my nowy cykl, o ile i = j,
  - w przeciwnym razie dotarli�my do wierzcho�ka, kt�ry znajduje si�
    na cyklu ju� wcze�niej znalezionym bad� te� z kt�rego wcze�niej
    dotarli�my do takowego cyklu. }
var
  i, j, lCykli: longint;

begin
  lCykli := 0;

  for i := 1 to n do
    numer[i] := 0;

  for i := 1 to n do begin
    j := i;
    while numer[j] = 0 do begin
      numer[j] := i;
      j := klucz[j];
    end;
    
    if numer[j] = i then
      Inc(lCykli);
  end;

  IleCykli := lCykli;
end;



begin
  WczytajDane;
  Writeln(IleCykli);
end.
