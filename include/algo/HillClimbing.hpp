#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

#include <random>
#include <algorithm>

using namespace std;

Solution hillClimbingFirstImprovement(const Instance& I,
                                     const Usuario& u,
                                     mt19937& rng,
                                     int maxIter,
                                     int maxRestarts);
