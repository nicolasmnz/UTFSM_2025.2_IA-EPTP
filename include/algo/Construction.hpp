#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"
#include <random>

// Construye una solución inicial factible (si es posible)
// para un usuario específico u_k.
Solution construirSolucionInicial(const Instance& I,
                                  const Usuario& u,
                                  std::mt19937& rng);
