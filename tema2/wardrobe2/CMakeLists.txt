cmake_minimum_required(VERSION 3.16)
project(wardrobe)

# Folosim C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setează directorul pentru executabile
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Directorul unde sunt fișierele .hpp
include_directories(include)

# Adaugă executabilul și fișierele sursă
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ClothingItem.cpp
    src/Wardrobe.cpp
)
