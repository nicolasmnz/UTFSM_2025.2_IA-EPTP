#include <iostream>
#include <random>
#include <string>

#include "../include/all.hpp"

using namespace std;

int main() {
    // 1. Leer parámetros (ruta instancia, carpeta salida, semillas, etc.)
    

    // 2. Cargar instancia
    

    // 3. Para cada usuario, resolver EPTP
    
        

        // 3.1 Ejecutar Hill Climbing (que por dentro hará:
        // construirSolucionInicial -> hillClimbingBestImprovement -> usar vecindad)

        // 3.2 Evaluar (por seguridad, o recalcular valor)
        

        // 3.3 Imprimir por pantalla + guardar en txt
        
    

    return 0;
}

/*
 Instance inst = Parser::cargar("instancia.txt");

    mt19937 rng(1234);

    for (int k = 0; k < inst.cantidadUsuarios(); k++) {

        Solution S0(k); // solución para usuario k
        S0 = generarSolucionInicial(inst, k, rng);

        Solution Sopt = hillClimbing(S0, inst, rng);

        imprimirSalida(Sopt);
        guardarSalida(Sopt, "usuario_" + to_string(k) + ".txt");
*/
