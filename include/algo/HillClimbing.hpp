#pragma once
#include "../model/Solution.hpp"
#include "../model/Instance.hpp"
#include <random>

Solution hillClimbing(const Solution& S0,
                      const Instance& I,
                      int maxIter,
                      std::mt19937& rng);
