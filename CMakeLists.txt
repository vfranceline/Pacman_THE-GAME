# Definindo a versão mínima do CMake e o projeto
cmake_minimum_required(VERSION 3.10)
project(Pacman_THE-GAME)

# Definindo a versão do C++ (C++11 ou superior)
set(CMAKE_CXX_STANDARD 11)

# Encontrar os pacotes SFML (Gráficos, Janela, Sistema)
find_package(SFML 2.5 REQUIRED graphics window system)

# Adicionar todos os arquivos .cpp encontrados na pasta Source
file(GLOB SOURCE_FILES src/*.cpp)

# Criar o executável
add_executable(Pacman_THE_GAME ${SOURCE_FILES})

# Linkar a SFML ao executável
target_link_libraries(Pacman_THE_GAME sfml-graphics sfml-window sfml-system)
