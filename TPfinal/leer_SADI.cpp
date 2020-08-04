#include <bits/stdc++.h>
using namespace std;
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);

typedef long long ll;
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define forr(i, a, b) for(int i = (a); i < (int) (b); i++)
#define forn(i, n) forr(i, 0, n)
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define DBG(x) cerr << #x << " = " << (x) << endl
#define DBGV(v,n) forn(i,n) cout << v[i] << " "; cout << endl
#define esta(x,c) ((c).find(x) != (c).end())
#define RAYA cerr << "===============================" << endl

struct BARRA
{
	string id, name, Pgen, PL; 
};

void leer_SADI(vector <string> &SADI)
{
	forn(i,20000)
	{
		string aux;
		getline(cin,aux);
		SADI.pb(aux);
	}
	//for(string u : SADI) cout << u << "\n";
}

void leer_barras(vector <string> &SADI, set <string> &set_barras, vector <BARRA> &barras,
				map <string,int> &id_to_pos)
{
	int pos = 0;
	string aux = "0 / END OF SYSTEM-WIDE DATA, BEGIN BUS DATA";
	string start = "     0.000";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0')
	{
		string copia = SADI[pos].substr(34,5);
		if(copia == "   4,")
		{
			string b = SADI[pos].substr(0,6);
			set_barras.insert(b);
			string c = SADI[pos].substr(8,12);
			id_to_pos[b] = (int)(barras.size());
			barras.pb({b,c,start,start});
		}
		pos++;
	}
	
	/*
	for(BARRA u : barras)
	{
		cout << u.id << " " << u.name << "\n";
	}*/
}

void leer_cargas(vector <string> &SADI, set <string> &set_barras, vector <BARRA> &barras,
				map <string,int> &id_to_pos)
{
	int pos = 0;
	string aux = "0 / END OF BUS DATA, BEGIN LOAD DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0')
	{
		string b = SADI[pos].substr(0,6);
		if(esta(b,set_barras))
		{
			string c = SADI[pos].substr(27,10);
			int index = id_to_pos[b];
			barras[index].PL = c;
		}
		
		pos++;
	}
	/*
	for(BARRA u : barras)
	{
		cout << u.id << " " << u.name << " " << u.PL << "\n";
	}*/
}

void leer_gen(vector <string> &SADI, set <string> &set_barras, vector <BARRA> &barras,
				map <string,int> &id_to_pos)
{
	int pos = 0;
	string aux = "0 / END OF FIXED SHUNT DATA, BEGIN GENERATOR DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0')
	{
		string b = SADI[pos].substr(0,6);
		if(esta(b,set_barras))
		{
			string c = SADI[pos].substr(12,10);
			int index = id_to_pos[b];
			barras[index].Pgen = c;
		}
		
		pos++;
	}
	/*
	for(BARRA u : barras)
	{
		cout << u.id << " " << u.name << " " << u.PL << " " << u.Pgen << "\n";
	}*/
}

int main()
{
	FIN;
	
	freopen("SADI", "r", stdin);
	vector <string> SADI;
	set <string> set_barras;
	vector <BARRA> barras;
	map <string,int> id_to_pos;
	
	leer_SADI(SADI);
	leer_barras(SADI,set_barras,barras,id_to_pos);
	leer_cargas(SADI,set_barras,barras,id_to_pos);
	leer_gen(SADI,set_barras,barras,id_to_pos);
	//leer_lineas(SADI,set_barras);
	
	cout << barras.size() << "\n";
	for(BARRA u : barras)
	{
		cout << u.id << " " << u.name << " " << u.PL << " " << u.Pgen << "\n";
	}
	
    return 0;
}
