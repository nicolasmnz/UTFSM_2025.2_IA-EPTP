#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

#include <random>

using namespace std;

vector<Solution> generarVecindad(const Solution& S,
                                 const Instance& I,
                                 const Usuario& u,
                                 mt19937& rng);
