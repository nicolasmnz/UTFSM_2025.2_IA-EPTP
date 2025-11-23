#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"
#include <vector>
#include <random>

// Genera vecinos agregando un nodo no visitado en cualquier posición
std::vector<Solution> agregarNodo(const Solution& S,
                                  const Instance& I,
                                  std::mt19937& rng);

// Genera vecinos eliminando un nodo existente (excepto el depósito)
std::vector<Solution> eliminarNodo(const Solution& S,
                                   const Instance& I,
                                   std::mt19937& rng);

// Combina ambas vecindades
std::vector<Solution> generarVecindad(const Solution& S,
                                      const Instance& I,
                                      std::mt19937& rng);