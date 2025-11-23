#pragma once

#include "../model/Solution.hpp"
#include "../../include/model/Instance.hpp"

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

// Guarda la salida final para un usuario en un .txt:
void guardarSalidaUsuario(const std::string& carpeta,
                          const std::string& instancia,
                          int id_usuario,
                          const Usuario& usuario,
                          const Solution& S);