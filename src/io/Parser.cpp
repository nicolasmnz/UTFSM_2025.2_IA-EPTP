#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Instance leerInstancia(const fs::path& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo: " + ruta.string());
    }
    
    // Leer número de nodos
    int n;
    archivo >> n;
    
    // Leer tiempos de servicio
    vector<Nodo> nodos(n);
    for (int i = 0; i < n; i++) {
        archivo >> nodos[i].tiempo_servicio;
    }
    
    // Leer ventanas de tiempo
    for (int i = 0; i < n; i++) {
        archivo >> nodos[i].inicio_servicio >> nodos[i].fin_servicio;
    }
    
    // Leer matriz de distancias
    vector<vector<int>> distancias(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> distancias[i][j];
        }
    }
    
    archivo.close();
    
    // Leer archivo de usuarios (asumiendo que tiene el mismo nombre base)
    fs::path rutaUsuarios = ruta.parent_path() / "usuarios.txt";
    ifstream archivoUsuarios(rutaUsuarios);
    
    if (!archivoUsuarios.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de usuarios: " + rutaUsuarios.string());
    }
    
    int m;
    archivoUsuarios >> m;
    
    vector<Usuario> usuarios(m);
    for (int k = 0; k < m; k++) {
        archivoUsuarios >> usuarios[k].tiempo_total;
        
        usuarios[k].valor_nodo.resize(n);
        for (int i = 0; i < n; i++) {
            archivoUsuarios >> usuarios[k].valor_nodo[i];
        }
        
        usuarios[k].valor_arcos.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                archivoUsuarios >> usuarios[k].valor_arcos[i][j];
            }
        }
    }
    
    archivoUsuarios.close();
    
    return Instance(n, nodos, distancias, usuarios);
}