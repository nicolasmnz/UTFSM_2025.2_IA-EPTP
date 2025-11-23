#include "../../include/io/Parser.hpp"
#include <fstream>
#include <stdexcept>

using std::string;
using std::vector;

// ---------------------------------------------------------
// Cargar ejemplo: simplemente delega al cargador general
// ---------------------------------------------------------
Instance Parser::cargarEjemplo(const string& nodosFile,
                               const string& usuariosFile)
{
    return cargarInstancia(nodosFile, usuariosFile);
}

// ---------------------------------------------------------
// Formatos:
//
// nodosFile:
//   n
//   (1 línea)            s_0 s_1 ... s_{n-1}               // tiempos de servicio
//   (1 línea o varias)   e_0 l_0 e_1 l_1 ... e_{n-1} l_{n-1}   // ventanas
//   (n líneas)           matriz de distancias n x n
//
// usuariosFile:
//   U
//   para cada usuario k:
//       tiempo_total
//       n enteros: valor_nodo[i]
//       n x n enteros: valor_arcos[i][j]
// ---------------------------------------------------------
Instance Parser::cargarInstancia(const string& nodosFile,
                                 const string& usuariosFile)
{
    // ------------ LEER NODOS ------------
    std::ifstream fn(nodosFile);
    if (!fn) throw std::runtime_error("No se pudo abrir " + nodosFile);

    int n;
    fn >> n;
    if (!fn) throw std::runtime_error("Error leyendo n en " + nodosFile);

    // tiempos de servicio en una sola línea
    vector<int> tiempos_servicio(n);
    for (int i = 0; i < n; ++i) {
        fn >> tiempos_servicio[i];
    }

    vector<Nodo> nodos(n);

    // ventanas de tiempo: pares (e_i, l_i) para cada nodo
    for (int i = 0; i < n; ++i) {
        int e, l;
        fn >> e >> l;
        nodos[i].tiempo_servicio = tiempos_servicio[i];
        nodos[i].inicio_servicio = e;
        nodos[i].fin_servicio    = l;
    }

    // matriz de distancias n x n
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fn >> dist[i][j];
        }
    }

    fn.close();

    // ------------ LEER USUARIOS ------------
    std::ifstream fu(usuariosFile);
    if (!fu) throw std::runtime_error("No se pudo abrir " + usuariosFile);

    int U;
    fu >> U;
    if (!fu) throw std::runtime_error("Error leyendo U en " + usuariosFile);

    vector<Usuario> usuarios(U);

    for (int k = 0; k < U; ++k) {
        // tiempo total disponible
        fu >> usuarios[k].tiempo_total;

        // valores de nodos
        usuarios[k].valor_nodo.resize(n);
        for (int i = 0; i < n; ++i) {
            fu >> usuarios[k].valor_nodo[i];
        }

        // matriz de valores de arcos
        usuarios[k].valor_arcos.assign(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                fu >> usuarios[k].valor_arcos[i][j];
            }
        }
    }

    fu.close();

    return Instance(n, nodos, dist, usuarios);
}
