# ================== CONFIGURACIÓN BÁSICA ==================
CXX      = g++
CXXFLAGS = -std=gnu++17 -O2 -Wall -Wextra -Iinclude

# Nombre del ejecutable
TARGET = eptp

# ================== FUENTES ==================
SRCS = \
    main.cpp \
    src/algo/Construction.cpp \
    src/algo/Evaluation.cpp \
    src/algo/HillClimbing.cpp \
    src/algo/Neighborhood.cpp \
    src/io/Parser.cpp \
    src/io/Output.cpp

OBJS = $(SRCS:.cpp=.o)

# ================== REGLAS PRINCIPALES ==================
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

# Regla genérica: cómo compilar cualquier .cpp -> .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ================== ATAJOS DE EJECUCIÓN ==================

# Ejecutar sobre TODAS las instancias
run: $(TARGET)
	./$(TARGET)

# Ejecutar el modo ejemplo (usa data/ejemplo.txt, data/usuarios.txt)
ejemplo: $(TARGET)
	./$(TARGET) ejemplo

# ================== LIMPIEZA ==================
clean:
	rm -f $(OBJS) $(TARGET)