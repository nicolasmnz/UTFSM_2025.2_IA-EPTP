#include "../../include/all.hpp"

#include <random>
#include <algorithm>
#include <vector>

using namespace std;

Solution construirSolucionInicial(const Instance& I, const Usuario& u, mt19937& rng) {
    Solution S;
    S.usuario = 0; // Se asignará correctamente en el main
    S.tour = {0}; // Siempre comenzar en el nodo 1 (índice 0)
    S.tau = {0};
    S.R = 0;
    S.valor = 0;
    
    int n = I.n();
    vector<bool> visitado(n, false);
    visitado[0] = true;
    
    // Construir solución greedy basada en valorización
    bool mejora = true;
    while (mejora) {
        mejora = false;
        double mejorValor = -1e9;
        int mejorNodo = -1;
        int mejorPos = -1;
        
        // Probar insertar cada nodo no visitado en cada posición
        for (int i = 1; i < n; i++) {
            if (visitado[i]) continue;
            
            for (size_t pos = 1; pos <= S.tour.size(); pos++) {
                Solution temp = S;
                temp.tour.insert(temp.tour.begin() + pos, i);
                
                if (recalcularCronograma(temp, I, u)) {
                    double valorTemp = evaluar(temp, I, u);
                    if (valorTemp > mejorValor) {
                        mejorValor = valorTemp;
                        mejorNodo = i;
                        mejorPos = pos;
                        mejora = true;
                    }
                }
            }
        }
        
        if (mejora) {
            S.tour.insert(S.tour.begin() + mejorPos, mejorNodo);
            recalcularCronograma(S, I, u);
            S.valor = evaluar(S, I, u);
            visitado[mejorNodo] = true;
        }
    }
    
    return S;
}