#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

#include <random>
#include <algorithm>

using namespace std;


vector<Solution> agregarNodo(const Solution& S,
                             const Instance& I,
                             mt19937& rng);
            
vector<Solution> eliminarNodo(const Solution& S,
                              const Instance& I,
                              mt19937& rng);

vector<Solution> twoOpt(const Solution& S, const Instance& I);

vector<Solution> generarVecindad(const Solution& S,
                                 const Instance& I,
                                 mt19937& rng);
