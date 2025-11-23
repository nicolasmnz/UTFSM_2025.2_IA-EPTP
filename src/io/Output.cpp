#include "Output.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void print(const Solution& S, const Instance& I, const Usuario& u, int idUsuario) {
    cout << "Usuario " << idUsuario << ":" << endl;
    cout << "Valor del tour: " << S.valor << endl;
    cout << "Tiempo disponible: " << I.tiempoMaximo(idUsuario);
    cout << ", Tiempo empleado: " << S.R << endl;
    cout << "Tour: ";
    for (size_t i = 0; i < S.tour.size(); i++) {
        cout << S.tour[i] + 1; // Mostrar números comenzando desde 1
        if (i < S.tour.size() - 1) cout << " ";
    }
    cout << endl << endl;
}

void write(const Solution& S, const Instance& I, const Usuario& u, int idUsuario, const fs::path& carpetaSalida) {
    // Crear directorio si no existe
    fs::create_directories(carpetaSalida);
    
    fs::path archivoSalida = carpetaSalida / ("usuario_" + to_string(idUsuario) + ".txt");
    ofstream archivo(archivoSalida);
    
    if (archivo.is_open()) {
        archivo << static_cast<int>(S.valor) << endl;
        archivo << I.tiempoMaximo(idUsuario) << " " << S.R << endl;
        for (size_t i = 0; i < S.tour.size(); i++) {
            archivo << S.tour[i] + 1; // Mostrar números comenzando desde 1
            if (i < S.tour.size() - 1) archivo << " ";
        }
        archivo << endl;
        archivo.close();
    }
}