#include <bits/stdc++.h>
using namespace std;
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);

typedef long long ll;
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define forr(i, a, b) for(size_t i = (a); i < (size_t) (b); i++)
#define forn(i, n) forr(i, 0, n)
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define DBG(x) cerr << #x << " = " << (x) << endl
#define DBGV(v,n) forn(i,n) cout << v[i] << " "; cout << endl
#define esta(x,c) ((c).find(x) != (c).end())
#define RAYA cerr << "===============================" << endl
#define MAXN 700
#define INF 1e9

int sumidero;
int demanda = 0, gen_max = 0, gen_y_ext = 0, cap_lineas = 0;
int total_barras;

struct LINEA
{
	string inicio, fin;
	int p_max;
	string estado;
};

struct BARRA
{
	string nombre, id;
	int generacion, PL;
	string estado;	
};

void leer_barras(vector <BARRA> &barra)
{
	int n;
	cin >> n;
  total_barras = n;
	forn(i,n)
	{
		string nombre, id, estado;
    double aux1, aux2;
		int generacion, PL;
		cin >> nombre >> id >> aux1 >> aux2 >> estado;
    PL = (int)(floor(aux1));
    generacion = (int)(floor(aux2));
		barra.pb({nombre,id,generacion,PL,estado});
	}
  sumidero = (int)(barra.size()+5);
  //~ cout << barra.size() << "\n";
  for(BARRA u : barra) {
    //~ cout << u.nombre << " " << u.generacion << " " << u.PL << "\n";
    demanda += u.PL;
    gen_max += u.generacion;
    gen_y_ext += u.generacion;
  }
}

void leer_lineas(vector <LINEA> &linea)
{
	//~ cout << "HOLA\n";
  int n;
	cin >> n;
	forn(i,n)
	{
		string inicio, fin, estado;
		int p_max; double aux;
		cin >> inicio >> fin >> aux >> estado;
    if(estado == "1") estado = "SI";
    else estado = "NO";
    if(inicio == "3376" || fin == "3376") {
      cout << inicio << " " << fin << " " << aux << "\n";
    }
    p_max = (int)(floor(aux));
		linea.pb({inicio,fin,p_max,estado});
    if(p_max < 100000) cap_lineas += p_max;
	}
}

void leer_externo(vector <BARRA> &barra, map <string,int> &barra_a_num) 
{
  int n;
  cin >> n;
  forn(i,n) {
    string nombre; double aux;
    cin >> nombre >> aux;
    int pmax = (int)(floor(aux));
    int pos = barra_a_num[nombre] - 1;
    barra[(size_t)pos].generacion += pmax;
    gen_y_ext += pmax;
  }
  
}

void mapear(map<string,int> &barra_a_num, map <int,string> &num_a_barra,
			vector <BARRA> &barra)
{
	int ind = 1;
	forr(i,1,barra.size()) {
    BARRA u = barra[i];
		barra_a_num[u.nombre] = ind;
		num_a_barra[ind] = u.nombre;
		ind++;
	}
	
	//~ cout << "Listado de barras\n";
	//~ for(auto u : num_a_barra) cout << u.first << " " << u.second << endl;
	//~ cout << endl;
}

void crear_grafo(vector <vector<int>> &grafo, vector <BARRA> &barra,
				 vector <LINEA> &linea, vector <vector<int>> &capacidad,
				 map <string,int> &barra_a_num)
{
	for(auto u : barra) {
		int x = barra_a_num[u.nombre];
    if(x == 0) continue;
    assert(x != 0);
		if(u.estado == "SI") {
      grafo[0].pb(x); 
      grafo[(size_t)x].pb(sumidero);
    }
		if(u.estado == "SI") {
      capacidad[0][(size_t)x] += u.generacion;
      capacidad[(size_t)x][(size_t)sumidero] += u.PL;
    }
	}
	for(auto u : linea) {
		int x = barra_a_num[u.inicio];
		int y = barra_a_num[u.fin];
    assert(x != 0); assert(y != 0);
		grafo[(size_t)x].pb(y);
		grafo[(size_t)y].pb(x);
		if(u.estado == "SI") capacidad[(size_t)x][(size_t)y] += u.p_max;
		if(u.estado == "SI") capacidad[(size_t)y][(size_t)x] += u.p_max;
	}
}


int bfs(int s, int t, vector<int> &parent, vector <vector<int>> &grafo,
		vector <vector<int>> &capacidad) 
{
    fill(parent.begin(), parent.end(), -1);
    parent[(size_t) s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while(!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int next : grafo[(size_t)cur]) {
            if(parent[(size_t)next] == -1 
            && capacidad[(size_t)cur][(size_t)next]) 
            {
                parent[(size_t)next] = cur;
                int new_flow = min(flow,capacidad[(size_t)cur][(size_t)next]);
                if(next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, vector <vector<int>> grafo, 
			vector <vector<int>> &capacidad) 
{
    int flow = 0;
    vector<int> parent(MAXN);
    int new_flow;

    while ((new_flow = bfs(s,t,parent,grafo,capacidad))!=0) 
    {
        flow += new_flow;
        int cur = t;
        while (cur != s) 
        {
            int prev = parent[(size_t)cur];
            capacidad[(size_t)prev][(size_t)cur] -= new_flow;
            capacidad[(size_t)cur][(size_t)prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void run(vector <vector<int>> &grafo, vector <vector<int>> &capacidad,
		 map <int,string> num_a_barra)
{
	cout << "Max Flow = " << maxflow(0,sumidero,grafo,capacidad) << "\n";
  cout << "Demanda = " << demanda << "\n";
  cout << "Generacion Disponible = " << gen_max << "\n";
  cout << "Maxima Demanda = " << gen_y_ext << "\n";
  cout << "Capacidad Lineas = " << cap_lineas << "\n";
  
  //~ freopen("Test.tsv","r",stdin);
	//~ int q;
	//~ cin >> q;
	//~ cout << "Carga máxima\n";
	//~ forn(i,q)
	//~ {
		//~ int test;
		//~ cin >> test;
		//~ cout << num_a_barra[test] << " " << maxflow(0,test,grafo,capacidad) << endl;  
	//~ }
	//~ cout << endl;
	//~ fclose(stdin);
}

vector <bool> seen(MAXN,false);
int check = 0;

void DFS(int v, vector <vector <int> > &grafo) {
  //~ DBG(v);
  seen[v] = true; check++;
  for(int u : grafo[v]) {
    if(!seen[u]) DFS(u,grafo);
  }
}

int main()
{
	FIN;
	freopen("SADI_REMIX_MAX_MIN", "r",stdin);
	vector <BARRA> barra(1);
	vector <LINEA> linea;
	leer_barras(barra);
	leer_lineas(linea);
	map <string,int> barra_a_num;
	map <int,string> num_a_barra;
	mapear(barra_a_num,num_a_barra,barra);
	leer_externo(barra,barra_a_num);
  
	vector <vector<int>> capacidad(MAXN,vector<int>(MAXN,0));
	vector <vector<int>> grafo(MAXN);
	crear_grafo(grafo,barra,linea,capacidad,barra_a_num);
	
  
  fclose(stdin);
	run(grafo,capacidad,num_a_barra);
	
  int maximum = 0;
  forr(i,1,barra.size()) {
    maximum += capacidad[i][sumidero];
    if(capacidad[i][sumidero]) {
      cout << barra[i].nombre << ") " << barra[i].id << " " << maximum << "\n";
      for(int u : grafo[i]) cout << u << " "; cout << "\n";
    }
  }
  
  
  DBG(maximum);
  
  
	
  return 0;
}
