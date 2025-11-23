#pragma once

#include "../model/Instance.hpp"
#include "../model/Solution.hpp"

#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void print      (const Solution& S,
                 const Instance& I,
                 const Usuario& u,
                 int idUsuario);
                 
void write     (const Solution& S,
                 const Instance& I,
                 const Usuario& u,
                 int idUsuario,
                 const fs::path& carpetaSalida);
