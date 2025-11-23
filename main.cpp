#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <filesystem>

#include "include/all.hpp"

#define SEED 12345

using namespace std;
namespace fs = std::filesystem;

// ---------------------------------------------------------
// Procesa una instancia completa (todos los usuarios de esa instancia)
// ---------------------------------------------------------
void procesarInstancia(const std::string& nombreInstancia,
                       const Instance& I,
                       std::mt19937& rng,
                       bool imprimir)
{
    const int maxIter = 60;  // se puede ajustar

    for (int k = 0; k < I.cantidadUsuarios(); ++k)
    {
        const Usuario& u = I.getUsuario(k);

        try {
            auto t0 = std::chrono::high_resolution_clock::now();

            // Solución inicial
            Solution S0 = construirSolucionInicial(I, u, rng);

            // Hill Climbing best–improvement
            Solution Sopt = hillClimbing(I, u, S0, maxIter, rng);

            auto t1 = std::chrono::high_resolution_clock::now();
            double tiempo_ms =
                std::chrono::duration<double, std::milli>(t1 - t0).count();

            // Guardar medición en CSV
            guardarCSV("medicion/medicion.csv",
                       nombreInstancia,
                       k,
                       maxIter,
                       Sopt.valor,
                       tiempo_ms);

            // Opcional: imprimir por pantalla (solo en modo ejemplo)
            if (imprimir)
            {
                cout << "=== Instancia: " << nombreInstancia
                     << " | Usuario: " << k << " ===\n";
                imprimirSolucion(Sopt);
                cout << "Tiempo (ms): " << tiempo_ms << "\n\n";
            }
        }
        catch (const std::exception& e) {
            cerr << "[ERROR] En usuario " << k
                 << " de instancia " << nombreInstancia
                 << ": " << e.what() << "\n";

            // registramos error en CSV
            guardarCSV("medicion/medicion.csv",
                       nombreInstancia,
                       k,
                       -1,   // iteración
                       -1,   // valor
                       0.0); // tiempo
        }
        catch (...) {
            cerr << "[ERROR] En usuario " << k
                 << " de instancia " << nombreInstancia
                 << ": excepción desconocida\n";

            guardarCSV("medicion/medicion.csv",
                       nombreInstancia,
                       k,
                       -1,
                       -1,
                       0.0);
        }
    }
}

// ---------------------------------------------------------
// main
// ---------------------------------------------------------
int main(int argc, char** argv)
{
    // Modo de ejecución:
    //   ./program ejemplo    -> usa data/ejemplo.txt + data/usuarios.txt
    //   ./program instancias -> recorre todas las instancias (por defecto)
    string modo = (argc > 1 ? string(argv[1]) : string("instancias"));

    // Semilla fija para reproducibilidad
    std::mt19937 rng(SEED);

    // Aseguramos que exista carpeta de medición
    fs::create_directories("medicion");

    if (modo == "ejemplo")
    {
        try {
            // Ajusta los nombres si tu ejemplo tiene otros archivos
            Instance inst = Parser::cargarEjemplo(
                "data/ejemplo.txt",
                "data/usuarios.txt"
            );

            procesarInstancia("ejemplo", inst, rng, /*imprimir=*/true);
        }
        catch (const std::exception& e) {
            cerr << "[ERROR] Cargando ejemplo: " << e.what() << "\n";
            guardarCSV("medicion/medicion.csv",
                       "ejemplo",
                       -1,
                       -1,
                       -1,
                       0.0);
        }
        catch (...) {
            cerr << "[ERROR] Cargando ejemplo: excepción desconocida\n";
            guardarCSV("medicion/medicion.csv",
                       "ejemplo",
                       -1,
                       -1,
                       -1,
                       0.0);
        }

        return 0;
    }

    // ----------------- MODO INSTANCIAS -----------------
    string nodosDir = "data/instancias/nodos";
    string usuariosDir = "data/instancias/usuarios";

    // Recorremos todos los .txt en data/instancias/nodos
    for (const auto& entry : fs::directory_iterator(nodosDir))
    {
        if (!entry.is_regular_file())
            continue;

        auto path = entry.path();
        if (path.extension() != ".txt")
            continue;

        string nodosFile = path.string();          // ruta completa al archivo de nodos
        string base = path.stem().string();        // ej: "10_instancia_0"
        string nombreInstancia = base;             // para el CSV

        // Buscar archivo de usuarios que comience con el mismo "base"
        string usuariosFile;
        for (const auto& uentry : fs::directory_iterator(usuariosDir))
        {
            if (!uentry.is_regular_file())
                continue;

            auto upath = uentry.path();
            if (upath.extension() != ".txt")
                continue;

            string ustem = upath.stem().string(); // ej: "10_instancia_0_5us"
            // verificamos que comience con "base"
            if (ustem.rfind(base, 0) == 0)        // prefix match
            {
                usuariosFile = upath.string();
                break;
            }
        }

        if (usuariosFile.empty())
        {
            cerr << "[ERROR] No se encontró archivo de usuarios para base "
                 << base << "\n";

            guardarCSV("medicion/medicion.csv",
                       nombreInstancia,
                       -1,
                       -1,
                       -1,
                       0.0);
            continue;
        }

        try {
            Instance inst = Parser::cargarInstancia(nodosFile, usuariosFile);

            procesarInstancia(nombreInstancia, inst, rng, /*imprimir=*/false);
        }
        catch (const std::exception& e) {
            cerr << "[ERROR] Cargando instancia " << nombreInstancia
                 << ": " << e.what() << "\n";

            guardarCSV("medicion/medicion.csv",
                       nombreInstancia,
                       -1,
                       -1,
                       -1,
                       0.0);
        }
        catch (...) {
            cerr << "[ERROR] Cargando instancia " << nombreInstancia
                 << ": excepción desconocida\n";

            guardarCSV("medicion/medicion.csv",
                       nombreInstancia,
                       -1,
                       -1,
                       -1,
                       0.0);
        }
    }

    return 0;
}
