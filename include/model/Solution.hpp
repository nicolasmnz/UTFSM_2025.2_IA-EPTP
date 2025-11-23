#pragma once

#include <vector>
#include <limits>

struct Solution
{
    // nodos del tour en orden, incluyendo depósito al inicio y al final
    std::vector<int> tour;

    // tiempos de inicio de servicio en cada posición del tour
    std::vector<int> tau;

    // tiempo total del tour (momento de regreso al depósito)
    int R = 0;

    // valor de la función objetivo (beneficio nodos + arcos)
    int valor = std::numeric_limits<int>::min();

    Solution() = default;

    void limpiar() {
        tour.clear();
        tau.clear();
        R = 0;
        valor = std::numeric_limits<int>::min();
    }
};