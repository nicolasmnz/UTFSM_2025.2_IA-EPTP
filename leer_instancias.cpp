#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <unordered_map>

namespace fs = std::filesystem;
using namespace std;

struct Nodo {
    int tiempo_servicio;
    // [e_i; l_i]
    int inicio_servicio, fin_servicio;
    // el tiempo de viaje lo hago con una matriz de struct Nodo
}; 

struct Usuario {
    int tiempo_total;
    // int tiempo_actual;
    vector<int> valor_nodo;
    // el valor del arco se da con la matriz
    vector<vector<int>> valor_arcos;
};

void setTiempos_to_Nodo(vector<Nodo>& node, string tiempos) {
    stringstream ss(tiempos);
    string tiempo_servicio;
    
    int i = 0;
    while (ss >> tiempo_servicio) {
        node[i].tiempo_servicio = stoi(tiempo_servicio);
        i++;
    }

    return;
}

void setIntervalo_to_Nodo(vector<Nodo>& node, string intervalos) {
    stringstream ss(intervalos);
    int inicio, fin;

    int i = 0;
    while (ss >> inicio >> fin) {
        node[i].inicio_servicio = inicio;
        node[i].fin_servicio = fin;
        i++;
    }

    return;
}

void setValorNodo_to_Usuarios(vector<Usuario>& user, string valorNodo) {
    stringstream ss(valorNodo);
    int valor;
    
    int i = 0;
    while (ss >> valor) {
        user[i].valor_nodo.push_back(valor);
    } 

    return;
}

vector<vector<int>> set_matriz(ifstream& archivo, int col, int fil) {
    string linea;
    vector<vector<int>> matriz(fil, vector<int>(col));
            
    for (int i = 0; i < fil; ++i) {
        for (int j = 0; j < col; ++j) {
            archivo >> matriz[i][j];
        }
    }

    return matriz;
}

string prefijo_base(const fs::path& nombre_archivo) {
    regex patron(R"(^(.+?)(_.*)?(\.txt)?)");
    smatch match;

    return match[1];
}

void leerarchivo(const fs::path& directorio_nodos, const fs::path& directorio_usuarios) {
    // preparo diccionarios para poder abrirlos en paralelo
    unordered_map<string, fs::path> archivos_nodos;
    unordered_map<string, fs::path> archivos_usuarios;
    for (const auto& entry : fs::directory_iterator(directorio_nodos)) {
        string nombre = entry.path().filename().string();
        string clave = prefijo_base(nombre);
        archivos_nodos[clave] = entry.path();
        
    }
    //preparo variables para procesar archivo--nodos
    vector<Nodo> conj_nodos;
    vector<vector<int>> matriz_distancia;
    vector<Usuario> conj_usuarios; //usuarios
    for (const auto& entry : fs::directory_iterator(directorio_usuarios)) {
        string nombre = entry.path().filename().string();
        string clave = prefijo_base(nombre);
        archivos_usuarios[clave] = entry.path();
    }
    // abrir los archivos en paralelo 
    string linea;
    for (const auto& [clave, path_nodos] : archivos_nodos) {
            fs::path path_usuario = archivos_usuarios[clave];
            //abrir archivos
            ifstream archivo_nodo(path_nodos);
            ifstream archivo_usuario(path_usuario);

            // --- nodos ---
            // reservo espacio para los n nodos
            getline(archivo_nodo, linea);
            int n = stoi(linea);
            conj_nodos.resize(n);
            // leo los tiempos de servicio
            getline(archivo_nodo, linea);
            setTiempos_to_Nodo(conj_nodos, linea);
            // leo los intervalos
            getline(archivo_nodo, linea);
            setIntervalo_to_Nodo(conj_nodos, linea);
            // leo la matriz de distancia
            matriz_distancia = set_matriz(archivo_nodo, n, n);

            // --- usuarios ---
            // reservo espacio para los m usuarios
            getline(archivo_usuario, linea);
            int m = stoi(linea);
            conj_usuarios.resize(m);
            // leo cada usuario
            for (int cant_user = 0; cant_user < m; cant_user++) {
                // leo valorizacion de los nodos
                getline(archivo_usuario, linea);
                setValorNodo_to_Usuarios(conj_usuarios, linea);
                // leo la matriz de valor de arcos
                conj_usuarios[cant_user].valor_arcos = set_matriz(archivo_usuario, m, m);
            }

            // llamada a restricciones 
            // evaluo 
    }
}