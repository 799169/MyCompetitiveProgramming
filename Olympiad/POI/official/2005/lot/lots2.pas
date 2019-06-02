(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: LOT (Lot na Marsa)                             *
 *   Plik:                lots2.cpp                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie alternatywne (nieoptymalne)        *
 *                        Algorytm dziala w czasie O(nlog n)             *
 *                        i pamieci O(n), sprawdza dla kazdego miasta    *
 *                        czy da si� z niego objecha� przy u�yciu        *
 *                        kolejki priorytetowej                          *
 *                                                                       *
 *************************************************************************)
program Lot_s1;

const MAX = 1000000 + 10;
type moja = record                {prosta struktura do przechowywania sumy cz�sciowej}
              d, num : LongInt;    {wraz z informacj�, do kt�rego wierzcho�ka ona nale�y}
            end;
var 
  i, n, calk, przejscie, size, minpo: LongInt;
  odl, zap, delta   : Array[0..MAX] of LongInt;     {tablice: odleg�o�ci, ilo�ci_paliw, i sum cz�ciowycH}
  res, uzyte        : Array[0..MAX] of Boolean;     {rezultat - czy mo�na l�dowa�, i u�yte - czy ju� przetworzyli�my}
  kopiec            : Array[0..MAX] of moja;        {tablica do obs�ugi kopca}


{Standardowa funkcja do ob�ugi stogu zaczerpni�ta z Cormena
 przepisana na iteracje - aby mog�o sie to zmie�ci� w stosie
 ze wzgl�du na rozmiar danych 1,000,000} 
procedure heapify(p:LongInt); {O(h)=O(lgn)}
var l,r,min: LongInt;
    temp:moja;
begin
 while p<size do begin
  l:= p shl 1;
  r:= l+1;
  if (l<=size) and (kopiec[l].d < kopiec[p].d)
    then min:=l
    else min:=p;
  if (r<=size) and (kopiec[r].d < kopiec[min].d)
    then min:=r;
  if min = p then break;
  temp:= kopiec[min];
  kopiec[min]:=kopiec[p];
  kopiec[p]:=temp;
  p:=min;
 end;
end;

{funckja do zdejmowania wierzcho�ka z czubka stogu}
procedure pop;
begin
    if size > 0 then
     begin
        kopiec[1]:=kopiec[size];
        Dec(size);
        if size>0 then heapify(1);
     end;
end;

{funckja dodaj�ca wierzcho�ek do stogu}
procedure push(m:moja); 
var j:LongInt;
begin
 inc(size);
 j:=size;
 while (j>1) and (kopiec[j shr 1].d > m.d) do begin
  kopiec[j]:=kopiec[j shr 1];
  j:=j shr 1;
 end;
 kopiec[j]:=m;
end;

{fukcja obliczaj�ca sumy cz�ciowe przy przechodzeniu
  zgodnie z kierunkiem wskaz�wek zegara, oraz inicjuj�ca
  inne potrzebne zmienn - ca�kowity bilans paliwa,
  ustawiaj�ca wierzcho�ki na nieodwiedzone, i dodaj�ca
  je do stogu}
procedure Preprocess1;
var
  i: LongInt;
  m: moja;
begin
  delta[0]:= 0;
  size:=0;
  for i:= 1 to n do
    begin
        delta[i]:= delta[i-1] + zap[i-1] - odl[i-1];       { obliczanie sum cz�ciowych}
        uzyte[i]:= false;
        m.d:= delta[i]; m.num:= i;
        push(m);
    end;
  minpo:=0;
  calk:= delta[n] + zap[n] - odl[n];                        { ca�kowity bilans paliwa }
end;

{funkcja obliczaj�ca sumy cz�sciowe przy przechodzeniu
  przeciwnie do ruchu wskaz�wek zegara}
procedure Preprocess2;
var
  i: LongInt;
  m: moja;
begin
  delta[n]:= 0;
  size:=0;
  for i:=n-1 downto 0 do
    begin
        delta[i]:= delta[i+1] + zap[i+1] - odl[i];      {obliczanie sum cz�cioowch}
        uzyte[i]:= false;
        m.d:= delta[i]; m.num:= i;
        push(m);
    end;
  minpo:=0;
end;


{funkcja zwracaj�ca aktualne minimum z pomini�ciem element�w
  ju� przetworzonych - usuwanie jest z op�nieniem, aby nie
    musie� pami�ta� i utrzymywa� tablicy z "adresami" element�w}
function min : LongInt;
begin
    while uzyte[kopiec[1].num] do pop;
    min:= kopiec[1].d;
end;

{g��wna funkcja sprawdzaj�ca czy dla danego wierzcho�ka wszystkie
  sumy cz�ciowe s� nieujemne}
function sprawdz(i:LongInt): Boolean;
begin
    sprawdz:= (minpo + przejscie >=0) and (min - delta[i] >=0); 
end;

begin
  ReadLn(n); Dec(n);
  for i:=0 to n do ReadLn(zap[i],odl[i]);

  if n=0 then 
    res[0]:= (zap[0] >= odl[0]) {przypadek 1-wierzcholkowy , juz usuniety z tresci zadania}
  else begin
{Przechodzenie stacji zgodnie z ruche wskaz�wek zegara}
    Preprocess1;
    for i:=0 to n do begin   
       if delta[i]< minpo then minpo:= delta[i];    {aktualicacja minimuw w�ro wierzcho�k�w przetworzonych}
       przejscie:= calk - delta[i];             {aktualizacja modyfikatora dla wierzcho�k�w przetworzonych}
       res[i]:= sprawdz(i);                     {przypisanie rezultatu proby przejscia}
       uzyte[i]:= true;
     end;
{przechodzenie stacji przeciwnie do ruchu wskaz�wek zegara }
    Preprocess2;
    for i:=n downto 0 do begin
      if delta[i]< minpo then minpo:= delta[i];
      przejscie:= calk - delta[i];
      res[i]:= res[i] or sprawdz(i);
      uzyte[i]:= true;
     end;
  end;
  for i:=0 to n do if res[i] then WriteLn('TAK') else WriteLn('NIE');
end.