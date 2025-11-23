#pragma once

#include <vector>

using namespace std;

struct Nodo
{
    int tiempo_servicio;                // s_i
    int inicio_servicio;                // e_i (ventana de tiempo inicio)
    int fin_servicio;                   // l_i (ventana de tiempo fin)
};

struct Usuario
{
    int tiempo_total;                   // T
    vector<int> valor_nodo;             // s_i  beneficio por visitar nodo i
    vector<vector<int>> valor_arcos;    // c_ij beneficio por arco
};

class Instance
{
private:
    int n_;                              // numero total de nodos
    vector<Nodo> nodos_;                 // informacion de cada nodo del grafo
    vector<vector<int>> distancias_;     // matriz d[i][j]
    vector<Usuario> usuarios_;           // información de cada usuario
public:
    // Constructor por defecto:
    Instance() = default; 
    // Constructor personalizado:
    Instance(int n_, 
            const vector<Nodo>& nodos_,
            const vector<vector<int>>& distancias_, 
            const vector<Usuario>& usuarios_)
        : n_(n_), nodos_(nodos_), distancias_(distancias_), usuarios_(usuarios_) {} 
    
    // --- Consultas básicas ---
    int n() const { return n_; }

    int cantidadUsuarios() const { return static_cast<int>(usuarios_.size()); }

    bool valido(int i) const {
        return i >= 0 && i < n_;
    }

    // --- Distancias ---
    int distancia(int i, int j) const {
        return distancias_[i][j];
    }

    // --- Info de nodos ---
    int tiempoServicio(int i) const {
        return nodos_[i].tiempo_servicio;
    }

    int inicioVentana(int i) const {
        return nodos_[i].inicio_servicio;
    }

    int finVentana(int i) const {
        return nodos_[i].fin_servicio;
    }

    // --- Info de usuario k ---
    int tiempoMaximo(int k) const {
        return usuarios_[k].tiempo_total;
    }

    int valorNodo(int i, int k) const {
        return usuarios_[k].valor_nodo[i];
    }

    int valorArco(int i, int j, int k) const {
        return usuarios_[k].valor_arcos[i][j];
    }

    // --- validar si un nodo esta disponible ---
    bool estaEnVentana(int i, int t) const {
        return t >= nodos_[i].inicio_servicio && t <= nodos_[i].fin_servicio;
    }

    // --- Vectores completos ---
    const vector<Nodo>& nodos() const { return nodos_; }

    const vector<std::vector<int>>& distancias() const { return distancias_; }

    const vector<Usuario>& usuarios() const { return usuarios_; }


};
