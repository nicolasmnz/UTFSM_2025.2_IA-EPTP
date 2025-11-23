#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"
#include <random>

using namespace std;

// Hill Climbing *first-improvement* para un usuario dado.
Solution hillClimbing(const Instance& I,
                      const Usuario& u,
                      const Solution& S0,
                      int maxIter,
                      mt19937& rng);