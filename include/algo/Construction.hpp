#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

#include <random>

using namespace std;

Solution construirSolucionInicial(const Instance& I,
                                  const Usuario& u,
                                  mt19937& rng);