#pragma once

#include <vector>

using namespace std;

struct Nodo
{
    int tiempo_servicio;                // s_i
    int inicio_servicio;                // e_i (ventana de tiempo inicio)
    int fin_servicio;                   // l_i (ventana de tiempo fin)
};

struct Usuario
{
    int tiempo_total;                   // T
    vector<int> valor_nodo;             // s_i  beneficio por visitar nodo i
    vector<vector<int>> valor_arcos;    // c_ij beneficio por arco
};

struct Instance
{
    int n;                              // numero total de nodos
    vector<Nodo> nodos;                 // informacion de cada nodo del grafo
    vector<vector<int>> distancias;     // matriz d[i][j]
    vector<Usuario> usuarios;           // información de cada usuario
};
