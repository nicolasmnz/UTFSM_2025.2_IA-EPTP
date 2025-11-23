#include "../../include/io/Output.hpp"
#include "../../include/model/Instance.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

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

void guardarSalidaUsuario(const std::string& carpeta,
                          const std::string& instancia,
                          int id_usuario,
                          const Usuario& usuario,
                          const Solution& S)
{
    // tiempo disponible del usuario
    int tiempoTotalDisponible = usuario.tiempo_total;
    // Nos aseguramos de que la carpeta exista
    std::filesystem::create_directories(carpeta);

    // Nombre del archivo, por ejemplo: data/resultados/10_instancia_0_u0.txt
    string filename = carpeta + "/" + instancia + "_u" + std::to_string(id_usuario) + ".txt";

    std::ofstream f(filename);
    if (!f) return;

    // 1) valor del tour
    f << S.valor << "\n";

    // 2) tiempo total disponible y tiempo total usado
    f << tiempoTotalDisponible << " " << S.R << "\n";

    // 3) nodos del tour (evitando depósito 0 duplicado al inicio/fin)
    int start = 0;
    int end   = static_cast<int>(S.tour.size());

    if (!S.tour.empty() && S.tour.front() == 0) start = 1;
    if (end > start && S.tour.back() == 0) --end;

    for (int i = start; i < end; ++i)
    {
        f << S.tour[i];
        if (i + 1 < end) f << " ";
    }
    f << "\n";
}