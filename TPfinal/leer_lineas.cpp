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


struct barra
{
	string num, nombre;
};

vector <barra> barras_SADI; 
map <string,string> mapa;

void leer_barras(set <string> &barras, multiset <pair<string,string> > &lineas)
{
	forn(i,20005)
	{
		string aux;
		getline(cin,aux);
		cout << aux << endl;
		if(aux.size() < 40) continue;
		string copia = aux.substr(34,5);
		//DBG(copia);
		if(copia == "   4,")
		{
			string b = aux.substr(0,6);
			barras.insert(b);
			string c = aux.substr(8,12);
			barras_SADI.pb({b,c});
			mapa[b]=c;
		}
		
		string copia1 = aux.substr(0,6);
		string copia2 = aux.substr(7,6);
		if(esta(copia1,barras)==true && esta(copia2,barras)==true)
		{
			lineas.insert({copia1,copia2});
			forn(j,aux.size())
			{
				cout << j << " " << aux[j] << "\n";
			}
			return;
		}
	}
	
	for(auto u : barras_SADI) cout << u.num << " " << u.nombre << "\n";
	
	cout << "\n\n"; RAYA; cout << "\n\n"; 
	for(auto u : lineas) 
	{
		cout << u.first << " - " << u.second << "\n";
		cout << mapa[u.first] << " - " << mapa[u.second] << "\n";
	}
	
	cout << "\n\n"; RAYA; cout << "\n\n"; 
	
	cout << barras.size() << "\n";
	cout << lineas.size() << "\n";
}



int main()
{
	FIN;
	freopen("input", "r", stdin);
	
	set <string> barras;
	multiset <pair<string,string> > lineas;
	leer_barras(barras,lineas);
	
	
	
	
    return 0;
}
