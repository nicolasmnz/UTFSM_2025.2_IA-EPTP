#include "../../include/algo/Neighborhood.hpp"
#include <algorithm>

using std::vector;

// ------------------------ AGREGAR NODO ------------------------
vector<Solution> agregarNodo(const Solution& S,
                             const Instance& I,
                             std::mt19937& rng)
{
    vector<Solution> vecinos;

    // nodos no usados (1..n-1)
    vector<int> no_usados;
    for (int v = 1; v < I.n(); ++v) {
        if (std::find(S.tour.begin(), S.tour.end(), v) == S.tour.end())
            no_usados.push_back(v);
    }
    if (no_usados.empty()) return vecinos;

    std::uniform_int_distribution<int> dist(0, (int)no_usados.size() - 1);
    int nodoNuevo = no_usados[dist(rng)];

    // generar vecinos insertando nodoNuevo en todas las posiciones internas
    int m = (int)S.tour.size();
    // evitamos sobreescribir la posición 0 y la última si son depósitos
    for (int pos = 1; pos < m; ++pos) {
        Solution V = S;
        V.tour.insert(V.tour.begin() + pos, nodoNuevo);
        vecinos.push_back(V);
    }
    return vecinos;
}

// ------------------------ ELIMINAR NODO ------------------------
vector<Solution> eliminarNodo(const Solution& S,
                              const Instance& /*I*/,
                              std::mt19937& rng)
{
    vector<Solution> vecinos;

    int m = (int)S.tour.size();
    if (m <= 2) return vecinos; // solo depósito->depósito

    // elegimos una posición interna aleatoria (no el depósito inicial ni final)
    std::uniform_int_distribution<int> dist(1, m - 2);
    int pos = dist(rng);

    Solution V = S;
    V.tour.erase(V.tour.begin() + pos);
    vecinos.push_back(V);

    return vecinos;
}

// ------------------------ COMBINAR VECINDAD ------------------------
vector<Solution> generarVecindad(const Solution& S,
                                 const Instance& I,
                                 std::mt19937& rng)
{
    vector<Solution> N;

    auto A = agregarNodo(S, I, rng);
    auto E = eliminarNodo(S, I, rng);

    N.reserve(A.size() + E.size());
    N.insert(N.end(), A.begin(), A.end());
    N.insert(N.end(), E.begin(), E.end());

    return N;
}
