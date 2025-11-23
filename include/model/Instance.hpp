#pragma once

#include <vector>

struct Nodo
{
    int tiempo_servicio;   // s_i
    int inicio_servicio;   // e_i
    int fin_servicio;      // l_i
};

struct Usuario
{
    int tiempo_total;                         // T_k
    std::vector<int> valor_nodo;             // s_i^k
    std::vector<std::vector<int>> valor_arcos; // c_ij^k
};

class Instance
{
private:
    int n_;                                  // número de nodos
    std::vector<Nodo> nodos_;                // info de cada nodo
    std::vector<std::vector<int>> dist_;     // dist_[i][j] = tiempo viaje
    std::vector<Usuario> usuarios_;          // info por usuario

public:
    Instance() = default;

    Instance(int n,
             const std::vector<Nodo>& nodos,
             const std::vector<std::vector<int>>& dist,
             const std::vector<Usuario>& usuarios)
        : n_(n), nodos_(nodos), dist_(dist), usuarios_(usuarios) {}

    // --- Consultas básicas ---
    int n() const { return n_; }

    int cantidadUsuarios() const {
        return static_cast<int>(usuarios_.size());
    }

    const Usuario& getUsuario(int k) const {
        return usuarios_[k];
    }

    // --- Distancias ---
    int distancia(int i, int j) const {
        return dist_[i][j];
    }

    // --- Info nodos ---
    int tiempoServicio(int i) const {
        return nodos_[i].tiempo_servicio;
    }

    int inicioVentana(int i) const {
        return nodos_[i].inicio_servicio;
    }

    int finVentana(int i) const {
        return nodos_[i].fin_servicio;
    }

    // acceso a estructura cruda (si la necesitas)
    const std::vector<Nodo>& nodos() const { return nodos_; }
    const std::vector<std::vector<int>>& distancias() const { return dist_; }
    const std::vector<Usuario>& usuarios() const { return usuarios_; }
};
