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

struct BARRA {
	string id, name, Pgen, PL; 
};

struct LINEA {
	string a, b, Pmax, state;
};

bool compare(BARRA &a, BARRA &b) {
  return a.name < b.name;
}

void leer_SADI(vector <string> &SADI) {
	forn(i,20000) {
		string aux;
		getline(cin,aux);
		SADI.pb(aux);
	}
	//for(string u : SADI) cout << u << "\n";
}

vector <string> parsear(string &s) {
  vector <string> ans;
  string cur;
  for(char u : s) {
    if(u == ',') ans.pb(cur), cur = "";
    else cur += u;
  }
  ans.pb(cur);
  //~ for(string u : ans) cout << u << " "; cout << "\n";
  return ans;
}

void leer_barras(vector <string> &SADI, set <string> &set_barras, vector <BARRA> &barras,
				map <string,int> &id_to_pos, map <string,string> &num_to_name, vector <LINEA> &lineas)
{
	size_t pos = 0;
	string aux = "0 / END OF SYSTEM-WIDE DATA, BEGIN BUS DATA";
	string start = "     0.000";
	while(SADI[(size_t)pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[(size_t)pos][0] != '0') {
		string copia = SADI[pos].substr(34,5);
		if(copia == "   4,") {
			string b = SADI[pos].substr(0,6);
      if(b == "  3376") {pos++; continue;}
			set_barras.insert(b);
			string c = SADI[pos].substr(8,12);
      forn(i,12) {
        if(c[(size_t)i] == ' ') c[(size_t)i]='_';
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
	size_t pos = 0;
	string aux = "0 / END OF BUS DATA, BEGIN LOAD DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0') {
		string b = SADI[pos].substr(0,6);
		if(esta(b,set_barras)) {
			string c = SADI[pos].substr(27,10);
			int index = id_to_pos[b];
			barras[(size_t)index].PL = c;
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
	size_t pos = 0;
	string aux = "0 / END OF FIXED SHUNT DATA, BEGIN GENERATOR DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0') {
		string b = SADI[pos].substr(0,6);
		if(esta(b,set_barras)) {
			string c = SADI[pos].substr(12,10);
			int index = id_to_pos[b];
			barras[(size_t)index].Pgen = c;
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
	size_t pos = 0;
	string aux = "0 / END OF GENERATOR DATA, BEGIN BRANCH DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0') {
		//DBG(SADI[pos]);
    vector <string> parseo = parsear(SADI[pos]);
    string P_MAX = max(max(parseo[7],parseo[8]),parseo[9]);
    
		if(esta(parseo[0],set_barras)==true && esta(parseo[1],set_barras)==true) {
			//~ DBG(parseo[0]); DBG(parseo[1]); DBG(parseo[7]); DBG(parseo[8]); DBG(parseo[9]); RAYA;
      lineas.pb({parseo[0],parseo[1],P_MAX,parseo[23]});
			//DBG(copia1);
		}
		if(esta(parseo[0],set_barras)==true && esta(parseo[1],set_barras)==false){
			string ini = "  0000";
			string PL = "     0.000"; 
			gen_extra.pb({parseo[1],parseo[0],P_MAX,PL});
			//DBG(copia1);
		}
		if(esta(parseo[0],set_barras)==false && esta(parseo[1],set_barras)==true){
			string ini = "  0000";
			string PL = "     0.000"; 
			gen_extra.pb({parseo[0],parseo[1],P_MAX,PL});
			//DBG(copia1);
		}
		
		pos++;
	}
	
}

void leer_switching(vector <string> &SADI, set <string> &set_barras, map<string,int> &id_to_pos,
				vector <LINEA> &lineas, vector <BARRA> &gen_extra)
{
	size_t pos = 0;
	string aux = "0 / END OF BRANCH DATA, BEGIN SYSTEM";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[pos][0] != '0') {
		//DBG(SADI[pos]);
    vector <string> parseo = parsear(SADI[pos]);
    string P_MAX = "100000";
		if(esta(parseo[0],set_barras)==true && esta(parseo[1],set_barras)==true) {
			//~ DBG(parseo[0]); DBG(parseo[1]); DBG(parseo[7]); DBG(parseo[8]); DBG(parseo[9]); RAYA;
      //~ DBG(parseo[0]); DBG(parseo[1]); RAYA;
      lineas.pb({parseo[0],parseo[1],P_MAX,"1"});
			//DBG(copia1);
		}
		pos++;
	}
	
}

//~ void leer_trafos(vector <string> &SADI, set <string> &set_barras, map <string,int> &id_to_pos,
      //~ map <string,string> &num_to_name, vector <LINEA> &lineas) 
//~ {
  //~ size_t pos = 0;
	//~ string aux = "0 / END OF SYSTEM SWITCHING DEVICE DATA, BEGIN TRANSFORMER DATA";
	//~ while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos++;
	//~ while(SADI[pos].substr(0,3) != "0 /") {
		//~ //DBG(SADI[pos]);
		//~ string copia1 = SADI[pos].substr(0,6);
		//~ string copia2 = SADI[pos].substr(7,6);
    //~ string copia3 = "100000";
		//~ if(esta(copia1,set_barras)==true && esta(copia2,set_barras)==true){
			//~ lineas.pb({copia1,copia2,copia3});
			//~ //DBG(copia1);
		//~ }
		
		//~ pos++;
	//~ }
        
//~ }

string int_to_string(int &id) {
  string ans; int copia = id;
  while(copia) {
    ans += char(copia%10 + '0');
    copia /= 10;
  } 
  id++;
  reverse(all(ans));
  return ans;
}

void leer_trafos(vector <string> &SADI, set <string> &set_barras, map <string,int> &id_to_pos,
      map <string,string> &num_to_name, vector <LINEA> &lineas, vector <BARRA> &barras) 
{
  int index = 100000;
  size_t pos = 0;
	string aux = "0 / END OF SYSTEM SWITCHING DEVICE DATA, BEGIN TRANSFORMER DATA";
	while(SADI[pos].substr(0,aux.size()) != aux) pos++; pos += 6;
  while(SADI[pos].substr(0,3) != "0 /") {
		//DBG(SADI[pos]);
		vector <string> parseo1 = parsear(SADI[pos]);
    
    if(parseo1[2] != "     0") {
      if(!esta(parseo1[0],set_barras) || !esta(parseo1[1],set_barras) ||
          !esta(parseo1[2],set_barras)) { pos += 5; continue; }
     
      vector <string> parseo2 = parsear(SADI[pos+2]);
      vector <string> parseo3 = parsear(SADI[pos+3]);
      vector <string> parseo4 = parsear(SADI[pos+4]);
      string next = int_to_string(index);
      barras.pb({next,"TRAFO_3","0","0"});
      
      //~ DBG(index);
      //~ DBG(parseo2[3]);
      //~ DBG(parseo3[3]);
      //~ DBG(parseo4[3]);
      
      lineas.pb({parseo1[0],next,parseo2[3],"1"});
      lineas.pb({parseo1[1],next,parseo3[3],"1"});
      lineas.pb({parseo1[2],next,parseo4[3],"1"});
      
      pos += 5;
    }
    else {
      if(!esta(parseo1[0],set_barras) || !esta(parseo1[1],set_barras)) {
        pos +=4; continue; }
      //~ DBG(parseo1[0]);
      //~ DBG(parseo1[1]); RAYA;
      vector <string> parseo2 = parsear(SADI[pos+2]);
      string P_MAX = parseo2[3];
      lineas.pb({parseo1[0],parseo1[1],P_MAX,"1"});
      pos += 4;
    }
	}
        
}

void leer_interruptores(vector <string> &SADI, set <string> &set_barras, map <string,int> &id_to_pos,
      map <string,string> &num_to_name, vector <LINEA> &lineas)
{
  int pos = 0;
	string aux = "0 / END OF BRANCH DATA, BEGIN SYSTEM SWITCHING DEVICE DATA";
	while(SADI[(size_t)pos].substr(0,aux.size()) != aux) pos++; pos++;
	while(SADI[(size_t)pos].substr(0,3) != "0 /") {
		//DBG(SADI[pos]);
		string copia1 = SADI[(size_t)pos].substr(0,6);
		string copia2 = SADI[(size_t)pos].substr(7,6);
    string copia3 = "100000";
		if(esta(copia1,set_barras)==true && esta(copia2,set_barras)==true) {
			lineas.pb({copia1,copia2,copia3,"1"});
			//DBG(copia1);
		}
		
		pos++;
	}
  
}

int main()
{
	FIN;
	
	freopen("SADI.txt", "r", stdin);
  freopen("SADI_REMIX_MAX_MIN", "w", stdout);
  vector <string> SADI;
  
	set <string> set_barras;
	vector <BARRA> barras;
	map <string,int> id_to_pos;
	map <string,string> num_to_name;
	vector <LINEA> lineas;
	vector <BARRA> gen_extra;
	
	leer_SADI(SADI);
	leer_barras(SADI,set_barras,barras,id_to_pos,num_to_name,lineas);
	leer_cargas(SADI,set_barras,barras,id_to_pos);
	leer_gen(SADI,set_barras,barras,id_to_pos);
	leer_lineas(SADI,set_barras,id_to_pos,lineas,gen_extra);
  leer_switching(SADI,set_barras,id_to_pos,lineas,gen_extra);
  leer_trafos(SADI,set_barras,id_to_pos,num_to_name,lineas,barras); 
  leer_interruptores(SADI,set_barras,id_to_pos,num_to_name,lineas);
	
	
	cout << barras.size() << "\n";
	for(BARRA u : barras) {
		//cout << u.id << " " << u.name << " " << u.PL << " " << u.Pgen << "\n";
    cout << u.id << " " << u.name << " " << u.PL << " " << u.Pgen << " SI\n";
	}
	cout << lineas.size() << "\n";
	for(LINEA u : lineas) {
		//~ cout << num_to_name[u.a] << " " << num_to_name[u.b] << " " << u.Pmax << "\n";
    cout << u.a << " " << u.b << " " << u.Pmax << " " << "1\n";
	}
	cout << gen_extra.size() << "\n";
	for(BARRA u : gen_extra) {
		//~ cout << num_to_name[u.id] << " " << num_to_name[u.name] << " " << u.Pgen << "\n";
    cout << u.name << " " << u.Pgen << "\n";
	}
	
  return 0;
}
