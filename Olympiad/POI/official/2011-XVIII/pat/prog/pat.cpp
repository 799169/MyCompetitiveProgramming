 /*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe wariant 1                   *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define INF 1000000001

using namespace std;

struct patyczek{
	int dl; //d�ugo��
	int kol; //kolor
}_p;
bool operator<(const patyczek &a, const patyczek &b){
	if(a.dl != b.dl)return a.dl > b.dl;
	return a.kol < b.kol;
}

struct delta{ 
	int d; //r�nica mi�dzy d�ugo�ci� dw�ch kolejnych patyczk�w
	int k1, k2; //kolory tych patyczk�w
	int p; //index pierwszego patyczka (po posortowaniu), drugi to b�dzie p+1
}_d;
bool operator<(const delta &a, const delta &b){
	return a.d < b.d;
}
int kolnach(delta a, delta b){ //ile kolor�w delty maj� wsp�lnych
	int ret = 0;
	if(a.k1 == b.k1 || a.k1 == b.k2)++ret;
	if(a.k2 == b.k1 || a.k2 == b.k2)++ret;
	return ret;
}

vector <patyczek> p; //vector trzymaj�cy patyczki
int n, k, m; //n - ilo�� patyczk�w, k - ilo�� kolor�w, m - ilo�� patyczk�w w kolorze
delta d[3]; //musimy pami�ta� 3 delty, �eby mie� najlepszych kandydat�w dla ka�dego koloru
char ostkol; //ostatni kolor

int main(){
	//Wczytywanie danych
	ios_base::sync_with_stdio(0);
	cin >> k;
	for(int i = 0;i < k; ++i){
		cin >> m;
		n += m;
		_p.kol = i + 1;
		for(int j = 0; j < m; ++j){
			cin >> _p.dl;
			p.push_back(_p);
		}
	}
	sort(p.begin(), p.end()); //sortujemy patyczki po d�ugo�ci
	d[0].d = d[1].d = d[2].d = INF; //inicjalizujemy pocz�tkowe warto�ci dla delt
	d[0].k1 = 1; d[0].k2 = 2;
	d[1].k1 = 1; d[1].k2 = 3;
	d[2].k1 = 2; d[2].k2 = 3;
	ostkol = p[0].kol;
	//Algorytm w�a�ciwy
	for(int i = 1; i < n; ++i){
		//Sprawdzenie, czy mo�na zbudowa� tr�jk�t
		_d.k1 = p[i].kol; //uzupe�niamy kolor w aktualnej delcie
		_d.k2 = -1; //drugi kolor ustawiamy na razie tak, �eby nie przeszkadza�
		for(int j = 0; j < 3; ++j){
			if(kolnach(d[j], _d) == 0 && d[j].d < p[i].dl){ //r�nica by�a mniejsza ni� d� aktualnego i kolory pasuj�
				int ind = d[j].p;
				cout << (int)p[i].kol << " " << p[i].dl << " ";
				cout << (int)p[ind].kol << " " << p[ind].dl << " ";
				++ind;
				cout << (int)p[ind].kol << " " << p[ind].dl << "\n";
				return 0;
			}
		}
		//Poprawianie delt
		if(p[i].kol == ostkol)continue;
		ostkol = p[i].kol; 
		int in = 0;   //ile nachodzi - �eby delty by�y dobrze wybrane musimy zamieni� z tak�, w kt�rej najwi�cej jest wsp�lnych
		int bd = 0; //dalej musimy wybra� tak�, kt�rej d jest jak najwi�ksze, bo je minimalizujemy
		int zd = -1; //a to index wybranej delty do zamiany lub -1, gdy nie op�aca si� zamienia�
		_d.k2 = p[i - 1].kol; //uzupe�niamy pozosta�e pola aktualnej delty
		_d.d = (p[i - 1].dl - p[i].dl);
		_d.p = i - 1;
		for(int j = 0; j < 3; ++j){ //szukamy delty z kt�r� mo�emy i op�aca nam si� zamieni� aktualn� delt�
			if(in < kolnach(d[j], _d)){ //je�li wi�cej kolor�w nachodzi ni� poprzednio, to anulujemy wyb�r
				zd = -1;
				bd = 0;
				in = kolnach(d[j], _d);
			}
			if(in <= kolnach(d[j], _d) && bd <= d[j].d){ //je�li op�aca si� i mo�emy zamieni� z dan� delt�, to j� wybieramy
				in = kolnach(d[j], _d);
				bd = d[j].d;
				zd = j;
			}
		}
		if(zd != -1 && bd > _d.d)d[zd] = _d; //je�li ostatecznie op�aca si� zamieni�, to zamieniamy
	}
	cout << "NIE\n"; //je�li nie zako�czyli�my wcze�niej programu, to znaczy, �e nie mo�na zbudowa� tr�jk�tu
	return 0;
} 
