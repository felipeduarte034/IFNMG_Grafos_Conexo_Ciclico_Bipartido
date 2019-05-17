#include <iostream>
#include <vector>
#include <string>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define RED 2
#define BLUE 1

/**
 * BRANCO - nodo ainda não encontrado
 * CINZA  - nodo encontrado
 * PRETO  - todos os vizinhos verificados
 */

//Conexo Desconexo
//Ciclico Aciclico
//Bipartido Nao-bipartido

//N --> vertices de 0 até N-1 [0,N)
//M --> m linhas

using namespace std;

class Grafo
{
public:
	int n;					 //quantidade de nodos no grafo
	vector<vector<int>> adj; //lista de adjacentes

	//nodo [0] --> [1] [4]
	//nodo [1] --> [0] [5]

	Grafo(int quant_vertices)
	{
		n = quant_vertices;
		for (int i = 0; i < quant_vertices; i++)
			adj.push_back(vector<int>());
	}
	void criarAresta(int x, int y)
	{
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	void printAdj()
	{
		int counter=0;
		for(vector<int> v : adj)
		{
			cout << counter++ << ": ";
			for(int x : v)
			{
				cout << x << ", ";
			}
			cout << endl;
		}
	}
};
class Info
{
public:
	int x;
	int y;
	Info(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

bool DFS(Grafo *g, int v, vector<int> &cor, int pai) //busca em profundidade
{
	if(cor[v]==BRANCO)
		cor[v] = CINZA;
	//cout << "\nv: "<<v;
	for (int i = 0; i < g->adj[v].size(); ++i)
	{
		int w = g->adj[v][i];
		//cout<<"  w: "<<w<<"";
		if (cor[w] == BRANCO)
		{
			//cout << " BRANCO# ";
			return DFS(g, w, cor, v);
		}
		else if (cor[w] == CINZA)
		{
			//cout << " CINZA ";
			//cout << "(pai:"<<pai<<")";
			if(w==pai)
				continue;
			else
			{
				//cout << "$";
				return true;
			}
		}
	}
	cor[v] = PRETO;
	return false;
}

bool isConexo(Grafo *g, int s) //busca em largura
{
	vector<int> fila(g->n);
	vector<int> cor(g->n, 0);
	int ini, fim;
	ini = fim = 0;
	cor[s] = 1;
	fila[fim++] = s;
	while (ini < fim)
	{
		int v = fila[ini++];
		//cout << "ini: "<<ini<<"  -  fim: "<<fim<<endl;
		//cout << "v: "<<v<<"  ";
		for (int i = 0; i < g->adj[v].size(); ++i)
		{
			int w = g->adj[v][i];
			//cout << "w: " << w<<",";
			/*switch (cor[w])
			{
				case BRANCO:
					cout << "BRANCO" << " ";
					break;
				case CINZA:
					cout << "CINZA" << " ";
					break;
				case PRETO:
					cout << "PRETO" << " ";
					break;
			}*/
			if (cor[w] == BRANCO)
			{
				//cout << "# ";
				cor[w] = CINZA;
				fila[fim++] = w;
			}
		}
		//cout << endl;
		cor[v] = PRETO;
	}
	//cout << "ini: "<<ini<<"  -  fim: "<<fim<<endl;
	return (fim == g->n); //o valor de fim é igual ao tamanho
}
bool isCiclico(Grafo *g, int s) //DFS - busca em profudindade
{
	vector<int> cor(g->n, 0);
	bool resp = DFS(g,s,cor,s);
	//cout << endl;
	return resp;
}
bool isBipartido(Grafo *g, int s)
{
	//branco   = 0
	//azul     = 1
	//vermelho = 2
	//branco = não visitado
	//red e blue = grupos opostos
	vector<int> fila(g->n);
	vector<int> cor(g->n, BRANCO);
	int ini, fim;
	ini = fim = 0;
	cor[s] = BLUE;
	fila[fim++] = s;
	while (ini < fim)
	{
		//cout << "\nini:"<<ini<<" - fim:"<<fim<<"  ";
		int v = fila[ini++];
		//cout << "v: "<<v<<"  ";
		for (int i = 0; i < g->adj[v].size(); ++i)
		{
			int w = g->adj[v][i];
			//cout << "(w:" << w<<")=";
			/*switch (cor[w])
			{
				case BRANCO:
					cout << "BRANCO" << " ";
					break;
				case BLUE:
					cout << "BLUE" << " ";
					break;
				case RED:
					cout << "RED" << " ";
					break;
			}*/
			if (cor[w] == BRANCO)
			{
				cor[w] = 3 - cor[v];
				//cout << "cor[w]=" << cor[w] << " ";
				fila[fim++] = w;
			}
			else if (cor[w] == cor[v])
			{
				//cout << "(cor[w]: " << cor[w] << " == cor[v]: " << cor[v] << ")\n";
				return false;
			}
		}
	}
	return true;
}

Info *DecodificaInstrucao(string line)
{
	int x = 0;
	int y = 0;

	size_t pos = line.find(" ");
	x = atoi(line.substr(0, pos).c_str());
	y = atoi(line.substr(pos).c_str());

	return new Info(x, y);
}

int main(int argc, char const *argv[])
{
	char line[50];
	int counter = 0;
	Grafo *g;
	Info *info = NULL;

	while (scanf("%[^\n]\n", line) == 1)
	{
		//cout << line << endl;
		counter++;
		if (counter == 1)
		{
			info = DecodificaInstrucao(line);
			g = new Grafo(info->x);
			continue;
		}
		info = DecodificaInstrucao(line);
		g->criarAresta(info->x, info->y);
	}

	cout << (isConexo(g,0) ? "Conexo" : "Desconexo") << endl;
	cout << (isCiclico(g,0) ? "Ciclico" : "Aciclico") << endl;
	cout << (isBipartido(g,0) ? "Bipartido" : "Nao-bipartido") << endl;

	//g->printAdj();

	return 0;
}
