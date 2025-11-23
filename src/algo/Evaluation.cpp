#include "../../include/all.hpp"

#include <algorithm>

using namespace std;

double evaluar(const Solution& S, const Instance& I, const Usuario& u) {
    if (S.tour.size() < 2) return 0.0;
    
    double valorTotal = 0.0;
    
    // Sumar valorización de nodos
    for (size_t i = 0; i < S.tour.size(); i++) {
        int nodo = S.tour[i];
        valorTotal += I.valorNodo(nodo, S.usuario);
    }
    
    // Sumar valorización de arcos
    for (size_t i = 0; i < S.tour.size() - 1; i++) {
        int from = S.tour[i];
        int to = S.tour[i + 1];
        valorTotal += I.valorArco(from, to, S.usuario);
    }
    
    // Arco de retorno al nodo inicial
    int lastNode = S.tour.back();
    valorTotal += I.valorArco(lastNode, 0, S.usuario);
    
    return valorTotal;
}

bool recalcularCronograma(Solution& S, const Instance& I, const Usuario& u) {
    if (S.tour.empty()) return false;
    
    S.tau.resize(S.tour.size());
    int tiempoActual = 0;
    
    // Nodo inicial (siempre nodo 0)
    if (S.tour[0] != 0) return false;
    
    S.tau[0] = 0;
    
    // Calcular tiempos para los demás nodos
    for (size_t i = 1; i < S.tour.size(); i++) {
        int nodoAnterior = S.tour[i - 1];
        int nodoActual = S.tour[i];
        
        // Tiempo de viaje
        tiempoActual += I.distancia(nodoAnterior, nodoActual);
        
        // Tiempo de espera si llegamos antes de la ventana
        int inicioVentana = I.inicioVentana(nodoActual);
        if (tiempoActual < inicioVentana) {
            tiempoActual = inicioVentana;
        }
        
        // Verificar si estamos dentro de la ventana de tiempo
        int finVentana = I.finVentana(nodoActual);
        if (tiempoActual > finVentana) {
            return false;
        }
        
        S.tau[i] = tiempoActual;
        
        // Agregar tiempo de servicio
        tiempoActual += I.tiempoServicio(nodoActual);
    }
    
    // Agregar tiempo de retorno al nodo inicial
    int ultimoNodo = S.tour.back();
    tiempoActual += I.distancia(ultimoNodo, 0);
    
    S.R = tiempoActual;
    
    // Verificar tiempo total disponible
    return S.R <= I.tiempoMaximo(S.usuario);
}