#include "header.h"

struct vertice {
	int cor = 0;
	vector<int> adjacencias;
	bool pivo = false;
	bool jaVisitado = false;
};

int main(){
	FILE *instancia;
	if ((instancia = fopen("10.txt", "r")) == NULL) {
		cout << "Arquivo nao aberto" << endl;
		return 0;
	}
	int operacoes=0;
	int nvertices, narestas, ncores, pivo;
	fscanf(instancia, "%d %d %d %d", &nvertices, &narestas, &ncores, &pivo);
	vector<Vertice> grafo;
	Vertice aux;
	//Define os vertices
	for (int i = 0; i < nvertices; i++) {
		fscanf(instancia, "%d", &aux.cor);
		grafo.push_back(aux);
	}
	pivo -= 1;
	grafo[pivo].pivo = true;
	int v1, v2;
	//Define as arestas
	for (int j = 0; j < narestas; j++){
		fscanf(instancia, "%d %d", &v1, &v2);
		grafo[v1-1].adjacencias.push_back(v2-1);
		grafo[v2-1].adjacencias.push_back(v1-1);
	}
	fclose(instancia);
	bool terminou = false;
	duration<double> time_span2;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	int auxiliar;
	//Se vertices adjacentes ao pivo forem da mesma cor que ele, já se tornam pivo
	for (int i = 0; i < grafo[pivo].adjacencias.size(); i++) {
		auxiliar = grafo[pivo].adjacencias[i];
		if (grafo[auxiliar].cor == grafo[pivo].cor)
			grafo[auxiliar].pivo = true;
	}
	while (!terminou) {
		terminou = true;
		inundar(grafo, pivo, ncores);
		for (int k = 0; k < nvertices; k++) {
			if (grafo[k].cor != grafo[pivo].cor)
				terminou = false;
		}
		operacoes++;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
	cout << "Operacoes necessarias: " << operacoes << "  Tempo necessario: " << time_span.count() << endl;
	/*for (int i = 0; i < nvertices; i++)
		cout << grafo[i].cor << "  ";*/
	return 0;
}

void inundar(vector<Vertice> &grafo, int pivo, int ncores) {
	//Vetor para a contagem de ocorrencia das cores
	vector<int> coresVer;
	for (int i = 0; i < ncores; i++)
		coresVer.push_back(0);

	//Torna os vertices de mesma cor do pivo e adjacentes a ele, pivos
	for (int k = 0; k < grafo.size(); k++) {
		if (grafo[k].pivo) {
			int aux;
			for (int l = 0; l < grafo[k].adjacencias.size(); l++) {
				aux = grafo[k].adjacencias[l];
				if (grafo[aux].cor == grafo[k].cor) {
					grafo[aux].pivo = true;
					grafo[aux].jaVisitado = true;
				}
				/*else if (!grafo[aux].jaVisitado) {
					coresVer[(grafo[aux].cor) - 1]++;
					grafo[aux].jaVisitado = true;
				}*/
			}
		}
	}
	//Conta a cor mais frequente ao redor do pivo
	for (int k = 0; k < grafo.size(); k++) {
		if (grafo[k].pivo) {
			int aux;
			for (int l = 0; l < grafo[k].adjacencias.size(); l++) {
				aux = grafo[k].adjacencias[l];
				if (!grafo[aux].jaVisitado) {
					coresVer[(grafo[aux].cor) - 1]++;
					grafo[aux].jaVisitado = true;
				}
			}
		}
	}
	/*for (int i = 0; i < coresVer.size(); i++) {
		cout << "cor: " << i + 1 << "  qtd: " << coresVer[i] << endl;
	}*/

	for (int j = 0; j < grafo.size(); j++) {
		grafo[j].jaVisitado = false;
	}

	int mais=1;

	for (int c = 0; c < coresVer.size(); c++) {
		if (coresVer[mais - 1] <= coresVer[c]) {
			mais = c + 1;
		}
	}

	int aux;
	grafo[pivo].jaVisitado = true;
	for (int l = 0; l < grafo[pivo].adjacencias.size(); l++) {
		aux = grafo[pivo].adjacencias[l];
		if (grafo[aux].cor == mais) {
			grafo[aux].pivo = true;
		}
		if (grafo[aux].pivo && !grafo[aux].jaVisitado) {
			inunda(grafo, aux, grafo[pivo].cor,mais);
		}
		grafo[aux].jaVisitado = true;
	}

	for (int j = 0; j < grafo.size(); j++) {
		grafo[j].jaVisitado = false;
	}
}

void inunda(vector<Vertice> &grafo, int pivo,int corNova, int corEscolhida) {
	int aux;
	grafo[pivo].jaVisitado = true;
	for (int l = 0; l < grafo[pivo].adjacencias.size(); l++) {
		aux = grafo[pivo].adjacencias[l];
		if (grafo[aux].cor == corEscolhida && !grafo[aux].jaVisitado) {
			grafo[aux].pivo = true;
			grafo[aux].jaVisitado = true;
			inunda(grafo, aux, corNova, corEscolhida);
		}
		else if (grafo[aux].pivo && !grafo[aux].jaVisitado) {
			grafo[aux].jaVisitado = true;
			inunda(grafo, aux, corNova, corEscolhida);
		}
	}
	grafo[pivo].cor = corNova;
}