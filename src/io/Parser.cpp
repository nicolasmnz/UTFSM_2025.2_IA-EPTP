#include "../../include/io/Parser.hpp"
#include <fstream>
#include <stdexcept>

using std::string;
using std::vector;

Instance Parser::cargarEjemplo(const string& nodosFile,
                               const string& usuariosFile)
{
    return cargarInstancia(nodosFile, usuariosFile);
}

// Formato asumido:
//
// nodosFile:
//   n
//   (n líneas): tiempo_servicio inicio_servicio fin_servicio
//   (n x n enteros): matriz de distancias
//
// usuariosFile:
//   U
//   para cada usuario u:
//       tiempo_total
//       n enteros: valor_nodo[i]
//       n x n enteros: valor_arcos[i][j]
//
Instance Parser::cargarInstancia(const string& nodosFile,
                                 const string& usuariosFile)
{
    std::ifstream fn(nodosFile);
    if (!fn) throw std::runtime_error("No se pudo abrir " + nodosFile);

    int n;
    fn >> n;
    if (!fn) throw std::runtime_error("Error leyendo n en " + nodosFile);

    vector<Nodo> nodos(n);
    for (int i = 0; i < n; ++i) {
        fn >> nodos[i].tiempo_servicio
           >> nodos[i].inicio_servicio
           >> nodos[i].fin_servicio;
    }

    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fn >> dist[i][j];

    fn.close();

    std::ifstream fu(usuariosFile);
    if (!fu) throw std::runtime_error("No se pudo abrir " + usuariosFile);

    int U;
    fu >> U;
    if (!fu) throw std::runtime_error("Error leyendo U en " + usuariosFile);

    vector<Usuario> usuarios(U);

    for (int k = 0; k < U; ++k) {
        fu >> usuarios[k].tiempo_total;

        usuarios[k].valor_nodo.resize(n);
        for (int i = 0; i < n; ++i)
            fu >> usuarios[k].valor_nodo[i];

        usuarios[k].valor_arcos.assign(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                fu >> usuarios[k].valor_arcos[i][j];
    }

    fu.close();

    return Instance(n, nodos, dist, usuarios);
}
