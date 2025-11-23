#include "../../include/algo/Construction.hpp"
#include "../../include/algo/Evaluation.hpp"

#include <algorithm>

using std::vector;

// Intento simple: partir en depósito (0), barajar nodos y agregar
// mientras se mantenga la factibilidad. Si un nodo rompe tiempo/ventanas,
// se omite.
Solution construirSolucionInicial(const Instance& I,
                                  const Usuario& u,
                                  std::mt19937& rng)
{
    Solution S;
    S.limpiar();
    int depot = 0;

    // tour inicial: solo depósito
    S.tour.push_back(depot);

    // candidatos = nodos 1..n-1
    vector<int> candidatos;
    candidatos.reserve(I.n() - 1);
    for (int i = 1; i < I.n(); ++i)
        candidatos.push_back(i);

    std::shuffle(candidatos.begin(), candidatos.end(), rng);

    // vamos probando agregar al final
    for (int v : candidatos) {
        Solution tmp = S;
        tmp.tour.push_back(v);
        tmp.tour.push_back(depot); // cerrar tour para evaluar

        if (evaluar(tmp, I, u)) {
            // si es factible, lo aceptamos como nuevo S
            S = tmp;
            // quitar el último depósito para seguir agregando
            S.tour.pop_back();
        }
    }

    // al final cerramos con el depósito
    if (S.tour.back() != depot)
        S.tour.push_back(depot);

    // evaluamos solución final
    evaluar(S, I, u);
    return S;
}
