#include "../../include/algo/HillClimbing.hpp"
#include "../../include/algo/Neighborhood.hpp"
#include "../../include/algo/Evaluation.hpp"
#include "../../include/algo/Construction.hpp"


#define NUM_RESTARTS 50

static Solution restart(const Instance& I,
                        const Usuario& u,
                        std::mt19937& rng)
{
    Solution S0 = construirSolucionInicial(I, u, rng);
    evaluar(S0, I, u);   
    return S0;
}


Solution hillClimbing(const Instance& I,
                      const Usuario& u,
                      const Solution& S0,
                      int maxIter,
                      mt19937& rng)
{
    // Partimos de la solución inicial y nos aseguramos de que esté evaluada
    Solution S = S0;
    evaluar(S, I, u);

    for (int it = 0; it < maxIter; ++it)
    {
        // Generar vecindad de S (agregar/quitar por ruleta)
        auto vecinos = generarVecindad(S, I, rng);

        bool hayMejora = false;

        // FIRST-IMPROVEMENT:
        // recorre los vecinos y acepta el primero que mejore el valor
        for (auto& V : vecinos)
        {
            if (!evaluar(V, I, u)) continue;  // descarta inviables

            if (V.valor > S.valor)           // mejora estricta
            {
                S = V;                       // aceptamos este vecino
                hayMejora = true;
                break;                       // salimos del for de vecinos
            }
        }
        
        int restartIntento = NUM_RESTARTS;
        if (!hayMejora && restartIntento > 0) {
            S = restart(I, u, rng);
            restartIntento--;
            hayMejora = true;
        }
        if (!hayMejora && restartIntento == 0) 
            break ;  // no hay mejora en esta iteración => terminamos
    }

    return S;
}
