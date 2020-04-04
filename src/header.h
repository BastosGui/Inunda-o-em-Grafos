#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <list>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef struct vertice Vertice;

void inundar(vector<Vertice> &grafo, int pivo, int ncores);
void inunda(vector<Vertice> &grafo, int pivo, int corNova, int corEscolhida);

#endif // !HEADER_H
