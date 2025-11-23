#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "include/all.hpp"

using namespace std;

namespace fs = std::filesystem;


int main(int argc, char* argv[]) {
    // Parámetros por defecto
    string rutaInstancia = "data/instancias/ejemplo/nodos.txt"; //revisar
    fs::path carpetaSalida = "medicion/";
    
    int semilla = 1234;
    int maxIter = 1000;
    int maxRestarts = 10;
    
    // Leer parámetros de línea de comandos (opcional)
    if (argc > 1) rutaInstancia = argv[1];
    if (argc > 2) carpetaSalida = argv[2];
    if (argc > 3) semilla = stoi(argv[3]);
    
    // Iniciar medición de tiempo
    auto inicio = chrono::high_resolution_clock::now();
    
    try {
        // 1. Cargar instancia
        cout << "Cargando instancia desde: " << rutaInstancia << endl;
        Instance I = leerInstancia(rutaInstancia);
        cout << "Instancia cargada: " << I.n() << " nodos, " << I.cantidadUsuarios() << " usuarios" << endl;
        
        // 2. Preparar generador de números aleatorios
        mt19937 rng(semilla);
        
        // 3. Para cada usuario, resolver EPTP
        for (int k = 0; k < I.cantidadUsuarios(); k++) {
            cout << "\n=== Procesando usuario " << k + 1 << " ===" << endl;
            
            const Usuario& u = I.usuarios()[k];
            
            // 3.1 Ejecutar Hill Climbing
            Solution S = hillClimbingFirstImprovement(I, u, rng, maxIter, maxRestarts);
            S.usuario = k; // Asignar el índice correcto del usuario
            
            // 3.2 Re-evaluar para asegurar consistencia
            S.valor = evaluar(S, I, u);
            
            // 3.3 Imprimir y guardar resultados
            print(S, I, u, k);
            write(S, I, u, k, carpetaSalida);
        }
        
        // Finalizar medición de tiempo
        auto fin = chrono::high_resolution_clock::now();
        auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
        
        // Guardar medición en CSV
        ofstream archivoTiempo(carpetaSalida / "tiempos.csv"); // revisar

        if (archivoTiempo.is_open()) {
            archivoTiempo << "Instancia,Tiempo(ms),Semilla" << endl;
            archivoTiempo << rutaInstancia << "," << duracion.count() << "," << semilla << endl;
            archivoTiempo.close();
        }
        
        cout << "\n=== Ejecución completada ===" << endl;
        cout << "Tiempo total: " << duracion.count() << " ms" << endl;
        cout << "Resultados guardados en: " << carpetaSalida << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}



    // 1. Leer parámetros (ruta instancia, carpeta salida, semillas, etc.)
    
    // (empezar medicion)
    // 2. Cargar instancia
    

    // 3. Para cada usuario, resolver EPTP
    
        

        // 3.1 Ejecutar Hill Climbing (que por dentro hará:
        // construirSolucionInicial -> hillClimbingFirstImprovement -> usar vecindad)

        // 3.2 Evaluar (por seguridad, o recalcular valor)
        

        // 3.3 Imprimir por pantalla + guardar en txt

    
    // terminar medicion
    
