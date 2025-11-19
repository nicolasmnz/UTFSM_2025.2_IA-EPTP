#pragma once

#include "../model/Instance.hpp"
#include <filesystem>

namespace fs = std::filesystem;;

Instance leerInstancia(const fs::path& ruta);