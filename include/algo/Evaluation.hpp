#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

// Recalcula tau, R y valor en S.
// Retorna true si S es factible (ventanas y T_k), false si no.
bool evaluar(Solution& S,
             const Instance& I,
             const Usuario& u);