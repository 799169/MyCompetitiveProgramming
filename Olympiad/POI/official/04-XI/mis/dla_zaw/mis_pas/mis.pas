{W tym pliku nalezy umiescic swoje rozwiazanie}
unit mis;

interface

procedure poczatek (m, p, mpo : LongInt);
procedure ruch_bolka (m, p : LongInt; var bm, bp : LongInt);

implementation

procedure poczatek (m, p, mpo : LongInt);
begin
  {Ta funkcja zostanie wywolana tylko raz, na poczatku rozgrywki.
   Tu mozesz zainicjalizowa� zmienne lub struktury danych potrzebne podczas
   rozgrywki}
end;


procedure ruch_bolka (m, p : LongInt; var bm, bp : LongInt);
begin
  {tu wpisz kod, ktory oblicza ruch Bolka w sytuacji gdy w puli jest m misi�w i
   p patysi�w. Wyznaczona liczbe misiow i patysiow, kt�re Bolek zabiera z puli 
   gry przypisz na zmienne bm i bp, odpowiednio.}
end;

end.
