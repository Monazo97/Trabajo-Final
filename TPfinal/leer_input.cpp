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

int main()
{
	FIN;
	
	int n = 30000;
	vector <string> barras;
	string aux;
	
	freopen("input", "r", stdin);
	
	//getline(cin,aux);
	//cout << aux << "\n";
	
	forn(i,n)
	{
		string aux;
		getline(cin,aux);
		if(aux.size() < 40) continue;
		string copia = aux.substr(34,5);
		//DBG(copia);
		if(copia == "   4,") barras.pb(aux);
	}
	
	
	for(auto u : barras) cout << u << " "; 
	
    return 0;
}
