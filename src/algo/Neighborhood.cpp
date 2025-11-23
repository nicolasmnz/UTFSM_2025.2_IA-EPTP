#include "../../include/all.hpp"

#include <algorithm>
#include <random>

using namespace std;

vector<Solution> agregarNodo(const Solution& S, const Instance& I, mt19937& rng) {
    vector<Solution> vecinos;
    int n = I.n();
    
    // Generar lista de nodos no visitados
    vector<int> nodosNoVisitados;
    for (int i = 1; i < n; i++) {
        if (find(S.tour.begin(), S.tour.end(), i) == S.tour.end()) {
            nodosNoVisitados.push_back(i);
        }
    }
    
    shuffle(nodosNoVisitados.begin(), nodosNoVisitados.end(), rng);
    
    // Probar insertar cada nodo no visitado en cada posición posible
    for (int nodo : nodosNoVisitados) {
        for (size_t pos = 1; pos <= S.tour.size(); pos++) {
            Solution nuevo = S;
            nuevo.tour.insert(nuevo.tour.begin() + pos, nodo);
            
            if (recalcularCronograma(nuevo, I, I.usuarios()[S.usuario])) {
                nuevo.valor = evaluar(nuevo, I, I.usuarios()[S.usuario]);
                vecinos.push_back(nuevo);
            }
        }
    }
    
    return vecinos;
}

vector<Solution> eliminarNodo(const Solution& S, const Instance& I, mt19937& rng) {
    vector<Solution> vecinos;
    
    // No podemos eliminar el primer nodo (nodo 1/depósito)
    if (S.tour.size() <= 2) return vecinos;
    
    // Probar eliminar cada nodo (excepto el primero)
    for (size_t i = 1; i < S.tour.size(); i++) {
        Solution nuevo = S;
        nuevo.tour.erase(nuevo.tour.begin() + i);
        
        if (recalcularCronograma(nuevo, I, I.usuarios()[S.usuario])) {
            nuevo.valor = evaluar(nuevo, I, I.usuarios()[S.usuario]);
            vecinos.push_back(nuevo);
        }
    }
    
    return vecinos;
}

vector<Solution> twoOpt(const Solution& S, const Instance& I) {
    vector<Solution> vecinos;
    
    if (S.tour.size() < 4) return vecinos; // Necesitamos al menos 3 nodos + depósito
    
    // Aplicar 2-opt a todos los pares posibles
    for (size_t i = 1; i < S.tour.size() - 2; i++) {
        for (size_t j = i + 1; j < S.tour.size() - 1; j++) {
            Solution nuevo = S;
            reverse(nuevo.tour.begin() + i, nuevo.tour.begin() + j + 1);
            
            if (recalcularCronograma(nuevo, I, I.usuarios()[S.usuario])) {
                nuevo.valor = evaluar(nuevo, I, I.usuarios()[S.usuario]);
                vecinos.push_back(nuevo);
            }
        }
    }
    
    return vecinos;
}

vector<Solution> generarVecindad(const Solution& S, const Instance& I, mt19937& rng) {
    vector<Solution> vecindadCompleta;
    
    // Combinar todos los tipos de movimientos
    vector<Solution> agregar = agregarNodo(S, I, rng);
    vector<Solution> eliminar = eliminarNodo(S, I, rng);
    vector<Solution> twoOptVecinos = twoOpt(S, I);
    
    vecindadCompleta.insert(vecindadCompleta.end(), agregar.begin(), agregar.end());
    vecindadCompleta.insert(vecindadCompleta.end(), eliminar.begin(), eliminar.end());
    vecindadCompleta.insert(vecindadCompleta.end(), twoOptVecinos.begin(), twoOptVecinos.end());
    
    return vecindadCompleta;
}