{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi�zanie zadania: Przeprawa                                      *
 *   Plik:                prz.pas                                        *
 *   Autor:               Pawe� Wolff                                    *
 *   Data:                2003.10.29                                     * 
 *************************************************************************}

program Przeprawa;

const
  MAX_N = 16;
  MAX_T = 50;
  DWA_DO_MAX_N = 65536;


type
  TBajtolaz =
    record
      t: integer;
      w: integer;
    end;
    
  TTabBajtolazow = array [1..MAX_N] of TBajtolaz;
  
  TTabZnacznikow = array [1..MAX_N] of boolean;
  

var
  n: integer; { liczba Bajto�az�w }
  b: TTabBajtolazow; { opis Bajto�az�w }
  
  w: integer; { maksymalne dopuszczalne obci��enie mostu }
  
  obliczonyCzas: array [0..DWA_DO_MAX_N - 1] of integer;
    { tu zapami�tujemy obliczone ju� czasy przeprawy podzbior�w zbioru
      wszystkich Bajto�az�w }
  

procedure WczytajDane(var z: TTabZnacznikow);
var
  i: integer;
begin
  Readln(w, n);
  for i := 1 to n do begin
    with b[i] do
      Readln(t, w);
    z[i] := true;
  end;
end;


function NajwolniejszyBajtolaz(var z: TTabZnacznikow): integer;
{ zwraca indeks najwolniejszego nieprzeprawionego Bajto�aza; je�eli takiego
  nie ma, to zwraca 0 }
var
  i: integer;
  maxT: integer;  
begin
  maxT := 0;
  NajwolniejszyBajtolaz := 0;
  
  for i := 1 to n do
    if z[i] and (b[i].t > maxT) then begin
      NajwolniejszyBajtolaz := i;
      maxT := b[i].t;
    end;
end;


function Indeks(var z: TTabZnacznikow): longint;
{ przekszta�ca tablic� znacznik�w z na indeks w tablicy obliczonyCzas }
var
  ind: longint;
  i: integer;

begin
  ind := 0;
  for i := 1 to n do begin
    ind := 2 * ind;
    if z[i] then
      Inc(ind);
  end;

  Indeks := ind;
end;

function ZapamietanyWynik(var z: TTabZnacznikow): integer;
{ zwraca zapami�tany czas przeprawy podzbioru Bajto�az�w okre�lony w tablicy z }
begin
  ZapamietanyWynik := obliczonyCzas[Indeks(z)];
end;

procedure ZapamietajWynik(var z: TTabZnacznikow; wynik: integer);
{ zapisuje (w tablicy obliczonyCzas) minimalny czas (okre�lony w zmiennej
  wynik) przeprawy podzbioru Bajto�az�w okre�lonego w tablicy z }
begin
  obliczonyCzas[Indeks(z)] := wynik;
end;


function ObliczWynik(var z: TTabZnacznikow): integer;
{ zwraca minimalny czas przeprawy podzbioru Bajto�az�w okre�lonego w tablicy z }

  procedure WydzielGrupe(var z: TTabZnacznikow; var wynik, wagaGrupy: integer;
                         ostatniWGrupie: integer);
  { powi�ksza grup� Bajto�az�w (zainicjowan� w funkcji ObliczWynik)
    o Bajto�az�w z podzbioru okre�lonego przez tablic� z i o indeksach
    wi�kszych ni� ostatniWGrupie; robi to na wszystkie takie sposoby,
    kt�re prowadz� do tego, �e wynikowa grupa (o inicjalnej sumarycznej wadze
    wagaGrupy) jest mo�liwie jak najwi�ksza (�ci�le rzecz bior�c - maksymalna
    w sensie inkluzji) oraz �e jej waga nie przekracza w (dopuszczalnego
    obci��enia mostu);
    dla wszystkich tak powi�kszonych grupy oblicza minimalny czas takiej
    przeprawy Bajto�az�w (z podzbioru okre�lonego przez tablic� z), �e
    najpierw przeprawiani s� Bajto�azi z grupy, a nast�pnie pozostali;
    przez parametr wynik przekazuje najkr�tszy czas przeprawy wykonanej
    wg powy�szego schematu }
  var
    i, wynikPom: integer;
    
  begin
    i := ostatniWGrupie + 1;
    while i <= n do begin

      { szukamy nast�pnego Bajto�aza w podzbiorze okre�lonym przez z }
      while (i <= n) and not z[i] do
        Inc(i);
      
      if i <= n then begin { je�li jeszcze kogo� (i-tego Bajto�aza) mo�na doda�
                             do grupy... }
        if wagaGrupy + b[i].w <= w then begin { i na dodatek powi�kszona
	                     o niego grupa nie przeci��a mostu, to... }
          { dodajemy i-tego Bajto�aza do przeprawianej grupy }
          z[i] := false;
          Inc(wagaGrupy, b[i].w);
	  
	  WydzielGrupe(z, wynik, wagaGrupy, i);

          { usuwamy i-tego Bajto�aza z przeprawianej grupy }
	  z[i] := true;
          Dec(wagaGrupy, b[i].w);
        end;
        Inc(i); { rozpatrujemy nast�pnego Bajto�aza }
      end
    end;

    { sprawdzamy, czy grupa jest maksymalna... }
    i := 1;
    while (i <= n) and not (z[i] and (wagaGrupy + b[i].w <= w)) do
      Inc(i);

    if i > n then begin
      { grupa jest maksymalna... }
      wynikPom := ObliczWynik(z); { wi�c liczymy minimalny czas przeprawy
                                    reszty Bajto�az�w }
      ZapamietajWynik(z, wynikPom);
      if wynikPom < wynik then
        wynik := wynikPom;
    end;
  end;

var
  i, wynik, wagaGrupy: integer;

begin
  wynik := ZapamietanyWynik(z); { mo�e ju� dla takiego podzbioru Bajto�az�w
                                  mamy policzony wynik? }
  if wynik <> 0 then { tak, ju� go policzyli�my }
    ObliczWynik := wynik
  else begin
    { nie, teraz b�dziemy go liczy� }
    i := NajwolniejszyBajtolaz(z);
    if i = 0 then begin { wszyscy s� przeprawieni (z definiuje zbi�r pusty) }
      ZapamietajWynik(z, 0);
      ObliczWynik := 0
    end
    else begin
      wynik := MAX_N * MAX_T; { d�u�ej ju� przeprawa trwa� nie mo�e }

      wagaGrupy := b[i].w;
      z[i] := false;
      { inicjalnie grupa sk�ada si� z najwolniejszego Bajto�aza, kt�ry
        nie zosta� jeszcze przeprawiony }
      WydzielGrupe(z, wynik, wagaGrupy, 0);
      z[i] := true;

      ObliczWynik := b[i].t + wynik;
    end;
  end;
end;



var
  doPrzeprawienia: TTabZnacznikow; { okre�la, kt�ry z Bajto�az�w jest jeszcze
                                     nieprzeprawiony }
  i: longint;
  dwaDoN: longint;

begin
  WczytajDane(doPrzeprawienia);

  { zerujemy tablice obliczonyWynik }
  dwaDoN := 1;
  for i := 1 to n do
    dwaDoN := 2 * dwaDoN;
  for i := 0 to dwaDoN - 1 do
    obliczonyCzas[i] := 0;

  { obliczamy i zapisujemy wynik }
  Writeln(ObliczWynik(doPrzeprawienia));
end.
