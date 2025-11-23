#include "../../include/io/Output.hpp"
#include <iostream>
#include <fstream>

using std::string;

void imprimirSolucion(const Solution& S)
{
    std::cout << "Tour: ";
    for (int v : S.tour) std::cout << v << " ";
    std::cout << "\nValor: " << S.valor
              << "\nTiempo total: " << S.R << "\n";
}

void guardarCSV(const string& file,
                const string& instancia,
                int usuario,
                int iteracion,
                int valor,
                double tiempo_ms)
{
    std::ofstream f(file, std::ios::app);
    if (!f) return;

    f << instancia << ","
      << usuario << ","
      << iteracion << ","
      << valor << ","
      << tiempo_ms << "\n";
}