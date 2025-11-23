#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

// Evalúa la solución y, en caso de ser necesario, la repara
// eliminando nodos hasta obtener un tour factible.
bool evaluar(Solution& S,
             const Instance& I,
             const Usuario& u);