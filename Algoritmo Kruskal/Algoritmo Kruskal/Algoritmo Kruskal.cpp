// Algoritmo Kruskal.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include <algorithm>

std::ifstream arquivo;
struct node {
	int id;
	std::vector<int> vizinhos;
	std::vector<int> distancia;
	std::vector<int> arvore;
};
struct aresta {
	int distancia;
	int node1;
	int node2;
};

std::vector<node> vertices;
std::vector<aresta> arestas;
std::vector<int> set;
int  numVertices;

void printar() {
	std::cout << "Set: ";
	for (int i = 0; i < set.size(); i++) {
		std::cout << set[i]<< " ";
	}
	std::cout <<std::endl<< "Vertices: ";
	for (int i = 0; i < vertices.size(); i++) {
		/*std::cout << "Id:" << vertices[i].id<<std::endl;
		for (int j = 0; j < vertices[i].vizinhos.size(); j++) {
			std::cout << " Vizinhos:" << vertices[i].vizinhos[j] << std::endl;
		}
		for (int j = 0; j < vertices[i].distancia.size(); j++) {
			std::cout << " Distancia:" << vertices[i].distancia[j] << std::endl;
		}*/
		for (int j = 0; j < vertices[i].arvore.size(); j++) {
			std::cout << " Arvore:" << vertices[i].arvore[j] << std::endl;
		}
		std::cout << "--------------------------------------------------------------"<<std::endl;
	}
	std::cout << std::endl << "Arestas: "<< std::endl;
	for (int i = 0; i < arestas.size(); i++) {
		std::cout << "Distancia:" << arestas[i].distancia << " node1:" << arestas[i].node1 << " Node2:" << arestas[i].node2 <<std::endl ;
	}
}


bool sortDistancia(const aresta &lhs, const aresta &rhs) {
	return lhs.distancia < rhs.distancia;
}

void make_Set() {
	for (int i = 0; i < numVertices; i++) {
		set.push_back(i);
	}
}

int find_Set(int i) {
	return set[i];
}

void UNION(int a, int b) {
	if (a < b) {
		for (int i = 0; i < vertices[b].arvore.size(); i++) {
			set[vertices[b].arvore[i]] = set[a];
			vertices[a].arvore.push_back(vertices[b].arvore[i]);
		}
		vertices[b].arvore = vertices[a].arvore;
		for (int i = 0; i < vertices[a].arvore.size(); i++) {
			vertices[vertices[a].arvore[i]].arvore = vertices[b].arvore;
		}
	}
	else
		printf("oi");
}

int criaGrafo() {
	std::string arquivoname;
	std::cout << "Kruskal:" << std::endl << "Digite o nome do arquivo(ex. exemplo.txt): ";
	std::cin >> arquivoname;
	arquivo.open(arquivoname);
	if (!arquivo.is_open()) {
		system("pause");
		return -1;
	}
	int i, j, aux;
	std::string stringer, num;
	node no,zero;
	aresta arestAux;
	std::getline(arquivo, stringer);
	numVertices = std::stoi(stringer);
	for (i = 0; i < numVertices; i++) {
		no.id = i;
		no.arvore.push_back(i);
		vertices.push_back(no);
		no = zero;
	}
	int col, linha;
	col = 1;
	linha = 0;
	while (!arquivo.eof()) {
		std::stringstream a;
		std::getline(arquivo, stringer);
		a << stringer;
		aux = col;
		while (a >> num) {
			arestAux.node1 = linha;
			arestAux.node2 = col;
			vertices[linha].vizinhos.push_back(col);
			vertices[col].vizinhos.push_back(linha);
			vertices[linha].distancia.push_back(std::stoi(num));
			vertices[col].distancia.push_back(std::stoi(num));
			arestAux.distancia = std::stoi(num);
			arestas.push_back(arestAux);
			col++;
		}
		linha++;
		aux++;
		col = aux;
	}

}

int main() {
	int i;
	int tamArvoreMin = 0;
	criaGrafo();
	make_Set();
	std::sort(arestas.begin(), arestas.end(), sortDistancia);
	for (i = 0; i < arestas.size(); i++) {
		if (find_Set(arestas[i].node1) != find_Set(arestas[i].node2)) {
			tamArvoreMin += arestas[i].distancia;
			UNION(arestas[i].node1, arestas[i].node2);
		}
	}
	std::cout << tamArvoreMin << std::endl;
	system("pause");

}
