#include "../../include/all.hpp"

#include <random>
#include <algorithm>

using namespace std;

Solution hillClimbingFirstImprovement(const Instance& I, const Usuario& u, mt19937& rng, int maxIter, int maxRestarts) {
    Solution mejorSolucion;
    double mejorValor = -1e9;
    
    for (int restart = 0; restart < maxRestarts; restart++) {
        // Construir solución inicial
        Solution current = construirSolucionInicial(I, u, rng);
        current.usuario = 0; // Se asignará correctamente
        
        bool mejora = true;
        int iter = 0;
        
        while (mejora && iter < maxIter) {
            mejora = false;
            
            // Generar vecindad
            vector<Solution> vecindad = generarVecindad(current, I, rng);
            
            // Buscar primera mejora
            for (const auto& vecino : vecindad) {
                if (vecino.valor > current.valor) {
                    current = vecino;
                    mejora = true;
                    break;
                }
            }
            
            iter++;
        }
        
        // Actualizar mejor solución global
        if (current.valor > mejorValor) {
            mejorSolucion = current;
            mejorValor = current.valor;
        }
    }
    
    return mejorSolucion;
}