#include "../../include/algo/Evaluation.hpp"
#include <algorithm> // std::max

using std::vector;

// ---------------------------------------------------------
// Evaluación estricta (SIN reparación).
// Devuelve true si el tour es factible tal cual viene.
// ---------------------------------------------------------
static bool evaluarEstricto(Solution& S,
                            const Instance& I,
                            const Usuario& u)
{
    if (S.tour.empty()) return false;

    int m = static_cast<int>(S.tour.size());
    S.tau.assign(m, 0);

    int t = 0;
    int valor = 0;

    // asumimos tour[0] es depósito (0)
    S.tau[0] = 0;

    for (int k = 1; k < m; ++k) {
        int i = S.tour[k - 1];
        int j = S.tour[k];

        // viajar de i a j
        t += I.distancia(i, j);

        // ventana de tiempo de j
        int e_j = I.inicioVentana(j);
        int l_j = I.finVentana(j);

        // si llegamos antes, esperamos
        t = std::max(t, e_j);

        // violación de ventana o de presupuesto de tiempo
        if (t > l_j) return false;
        if (t > u.tiempo_total) return false;

        // registramos inicio de servicio
        S.tau[k] = t;

        // tiempo de servicio
        t += I.tiempoServicio(j);

        // beneficio por nodo y arco (el depósito suele tener 0, así que no molesta)
        valor += u.valor_nodo[j];
        valor += u.valor_arcos[i][j];
    }

    S.R = t;
    S.valor = valor;
    return true;
}

// ---------------------------------------------------------
// Evaluación con REPARACIÓN.
// Si el tour no es factible, va eliminando el último cliente
// (penúltima posición) hasta que lo sea. Si nada sirve, deja
// un tour depósito->depósito con valor 0.
// ---------------------------------------------------------
bool evaluar(Solution& S,
             const Instance& I,
             const Usuario& u)
{
    // 1) Intento con el tour completo
    if (evaluarEstricto(S, I, u))
        return true;

    // 2) Reparación: eliminamos nodos internos desde el final
    //    y reintentamos evaluación estricta
    while (S.tour.size() > 2) {
        int penultimo = static_cast<int>(S.tour.size()) - 2; // último cliente antes del depósito
        if (penultimo <= 0) break; // solo queda el depósito

        S.tour.erase(S.tour.begin() + penultimo);

        if (evaluarEstricto(S, I, u))
            return true;
    }

    // 3) Si no logramos nada factible con clientes, dejamos el tour mínimo
    S.tour.clear();
    S.tour.push_back(0); // depósito
    S.tour.push_back(0); // regreso al depósito
    S.tau.assign(2, 0);
    S.R = 0;
    S.valor = 0;

    // Desde el punto de vista del algoritmo, esto es "factible"
    // (aunque de calidad 0), así que devolvemos true.
    return true;
}
