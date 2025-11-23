#pragma once

#include "../model/Instance.hpp"
#include <string>

class Parser
{
public:
    // Carga un ejemplo simple (data/ejemplo.txt, data/usuarios.txt)
    static Instance cargarEjemplo(const std::string& nodosFile,
                                  const std::string& usuariosFile);

    // Carga una instancia general: archivo de nodos + archivo de usuarios
    static Instance cargarInstancia(const std::string& nodosFile,
                                    const std::string& usuariosFile);
};