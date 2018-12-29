(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi.pas                                        *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z�o�ono�� obliczeniowa jak i pami�ciowa jest   *
 *                        liniowa. Przeszukiwanie grafu (DFS) jest       *
 *                        zrealizowane na wlasnym stosie (z powodu       *
 *                        potencjalnie du�ej g��boko�ci rekursji).       *
 *                                                                       *
 *************************************************************************)

program dziuple;

const MAXN = 1000000; {maksymalna liczba wierzcholkow}
type tab = array [1..MAXN] of longint;

var 
  {tablice, w ktorych trzymane sa krawedzie grafu}
  next, last, edge : array [1..2*MAXN] of longint; 
  deg, parent : tab; {stopnie oraz ojcowie wierzcho�k�w
                      w drzewie przeszukiwania w g��b}
  stack : tab; {stos}
  k, r : int64; 
  n, m : longint; {liczba wierzcholkow oraz liczba krawedzi}

(*procedura ta dodaje kraw�d� (a,b) do grafu, zapisuj�c
 j� na i-tym miejscu w tablicy*)
procedure dodaj(a, b, i: longint);
begin
  inc(deg[a]);
  edge[i] := b;
  next[i] := last[a];
  last[a] := i;
end;

{wczytywanie danych}
procedure czytaj;
var 
  i, a, b: longint;
begin
  readln(n, m, k);
  if (m < n) then
  begin
    for i:=1 to n do
    begin
      last[i] := 0;
      deg[i] := 0;
    end;
    
    for i:=1 to m do
    begin
      readln(a, b);
      dodaj(a, b, 2*i-1);
      dodaj(b, a, 2*i);
    end;
  end; 
end;

{przeszukiwanie grafu w g��b, zrealizowane na w��snym stosie}
procedure dfs(x : longint);
var 
  ile : longint; {liczba wierzcholkow na stosie}
  u, v, i, j, wezly, liscie : longint;
begin
  stack[1] := x; 
  parent[x] := x; {x jest jedynym elementem stosu}
  ile := 1;
  wezly := 0; {liczba wierzcho�k�w tej sp�jnej sk�adowej o stopniu >=2}
  while (ile > 0) do
  begin
    v := stack[ile]; {zdejmujemy wierzcho�ek ze stosu}
    dec(ile);
    if (deg[v] >= 2) then
      inc(wezly);
    liscie := 0;
    j := 0;
    i := last[v];
    while (i>0) do
    begin
      u := edge[i];
      if (parent[u] = 0) then
      begin
        {zaznaczamy wierzcho�ek jako odwiedzony i wrzucamy na stos}
        parent[u] := v;
        inc(ile);
        stack[ile] := u;
      end else
        if (u <> parent[v]) then
          r := 0; {skladowa nie jest drzewem}
      if (deg[u] = 1) then
        inc(liscie)
      else 
        inc(j);
      i := next[i];
    end;
    if (j > 2) then r := 0; {graf nie jest pladzielny}
    for i := 2 to liscie do {permutowanie wierzcho�k�w stopnia 1}
      r := (r * i) mod k;
  end;
  if (wezly>=2) then {symetria wzgledem prostej poziomej} 
    r := (r * 2) mod k;
end;

{g��wna procedura progamu, procedura ta zlicza liczb� rozstawie� ptaszk�w}
procedure licz;
var
  i, j, izolowane : longint;
begin
  for i := 1 to n do 
    parent[i] := 0; {wierzcho�ki nie s� odwiedzone}
  j := 0; {liczba sp�jnych sk�adowych}
  izolowane := 0;
  if (m < n) then
    r := 1
  else
    r := 0;
  for i := 1 to n do
    if (parent[i] = 0) then
      if (deg[i] > 0) then 
      begin
        inc(j);
        r := (r * (2 * j)) mod k;
        dfs(i);
      end 
      else inc(izolowane);
    
  {trzeba uwzgl�dni� dowolne rozstawienie wierzcho�k�w izolowanych}
  for i:=n+1 downto n + 2 - izolowane do
    r := (r * i) mod k;
  writeln(r);
end;
  
begin
  czytaj;
  licz;
end.
