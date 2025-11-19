#pragma once

#include <vector>

using namespace std;

struct Solution
{
    vector<int> tour;       // nodos en orden
    vector<int> tau;        // tiempo de inicio efectivo por nodo
    int R;                  // tiempo total del tour
    double valor;           // valor de la funcion de evaluacion
};