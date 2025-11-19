#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

double evaluar(const Solution& S,
               const Instance& I,
               const Usuario& u);

bool recalcularCronograma(Solution& S,
                          const Instance& I,
                          const Usuario& u);