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

struct LINEA
{
	string a, b, Pmax;
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
				map <string,int> &id_to_pos, map <string,string> &num_to_name)
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
      forn(i,12) {
        if(c[i] == ' ') c[i]='_';
        if(c[i] >= '0' && c[i] <= '9') c[i] = '_';
      }
			num_to_name[b] = c;
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

void leer_lineas(vector <string> &SADI, set <string> &set_barras, map<string,int> &id_to_pos,
				vector <LINEA> &lineas, vector <BARRA> &gen_extra)
{
	int pos = 0;
	string aux = "0 / END OF GENERATOR DATA, BEGIN BRANCH DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0')
	{
		//DBG(SADI[pos]);
		string copia1 = SADI[pos].substr(0,6);
		string copia2 = SADI[pos].substr(7,6);
		string copia3 = SADI[pos].substr(97,8);
		if(esta(copia1,set_barras)==true && esta(copia2,set_barras)==true)
		{
			lineas.pb({copia1,copia2,copia3});
			//DBG(copia1);
		}
		if(esta(copia1,set_barras)==true && esta(copia2,set_barras)==false)
		{
			string ini = "  0000";
			string PL = "     0.000"; 
			gen_extra.pb({copia2,copia1,copia3,PL});
			//DBG(copia1);
		}
		if(esta(copia1,set_barras)==false && esta(copia2,set_barras)==true)
		{
			string ini = "  0000";
			string PL = "     0.000"; 
			gen_extra.pb({copia1,copia2,copia3,PL});
			//DBG(copia1);
		}
		
		pos++;
	}
	
}

int main()
{
	FIN;
	
	freopen("SADI", "r", stdin);
  freopen("SADI_REMIX", "w", stdout);
	vector <string> SADI;
	set <string> set_barras;
	vector <BARRA> barras;
	map <string,int> id_to_pos;
	map <string,string> num_to_name;
	vector <LINEA> lineas;
	vector <BARRA> gen_extra;
	
	leer_SADI(SADI);
	leer_barras(SADI,set_barras,barras,id_to_pos,num_to_name);
	leer_cargas(SADI,set_barras,barras,id_to_pos);
	leer_gen(SADI,set_barras,barras,id_to_pos);
	leer_lineas(SADI,set_barras,id_to_pos,lineas,gen_extra);
	
	
	cout << barras.size() << "\n";
	for(BARRA u : barras)
	{
		//cout << u.id << " " << u.name << " " << u.PL << " " << u.Pgen << "\n";
    cout << u.name << " " << u.PL << " " << u.Pgen << " SI\n";
	}
	cout << lineas.size() << "\n";
	for(LINEA u : lineas)
	{
		//~ cout << num_to_name[u.a] << " " << num_to_name[u.b] << " " << u.Pmax << "\n";
    cout << num_to_name[u.a] << " " << num_to_name[u.b] << " " << u.Pmax << " SI\n";
	}
	cout << gen_extra.size() << "\n";
	for(BARRA u : gen_extra)
	{
		//~ cout << num_to_name[u.id] << " " << num_to_name[u.name] << " " << u.Pgen << "\n";
    cout << num_to_name[u.name] << " " << u.Pgen << "\n";
	}
	
    return 0;
}
