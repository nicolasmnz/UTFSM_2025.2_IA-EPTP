#pragma once

#include "../model/Solution.hpp"
#include <string>

// Imprime solución por stdout (para debug)
void imprimirSolucion(const Solution& S);

// Agrega una fila a un CSV de medición: instancia, usuario, iteración, valor, tiempo(ms)
void guardarCSV(const std::string& file,
                const std::string& instancia,
                int usuario,
                int iteracion,
                int valor,
                double tiempo_ms);