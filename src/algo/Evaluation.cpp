#include "../../include/algo/Evaluation.hpp"
#include <algorithm> // std::max
#include <limits>

bool evaluar(Solution& S,
             const Instance& I,
             const Usuario& u)
{
    if (S.tour.empty()) return false;

    int m = static_cast<int>(S.tour.size());
    S.tau.assign(m, 0);
    int t = 0;
    int valor = 0;

    // asumimos tour[0] es depósito
    S.tau[0] = 0;

    for (int k = 1; k < m; ++k) {
        int i = S.tour[k - 1];
        int j = S.tour[k];

        // viajar de i a j
        t += I.distancia(i, j);

        // si es nodo real, aplicar ventana y servicio
        int e_j = I.inicioVentana(j);
        int l_j = I.finVentana(j);
        t = std::max(t, e_j);    // espera si llega antes

        if (t > l_j) {
            // ventana violada
            S.valor = std::numeric_limits<int>::min();
            return false;
        }

        if (t > u.tiempo_total) {
            // excede presupuesto
            S.valor = std::numeric_limits<int>::min();
            return false;
        }

        S.tau[k] = t;

        // aplicar tiempo de servicio
        t += I.tiempoServicio(j);

        // sumar beneficio (si j != depósito, en tu modelo el depósito suele tener 0)
        valor += u.valor_nodo[j];
        valor += u.valor_arcos[i][j];
    }

    // cierre total
    S.R = t;
    S.valor = valor;
    return true;
}
