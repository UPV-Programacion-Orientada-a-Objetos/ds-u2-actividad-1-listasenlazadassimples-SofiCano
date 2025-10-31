
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(SistemaIoTSensores VERSION 1.0 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración de compilación
if(MSVC)
    # Configuración para Visual Studio en Windows
    add_compile_options(/W4)
else()
    # Configuración para GCC/Clang
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Directorio de archivos de cabecera
include_directories(${PROJECT_SOURCE_DIR}/include)

# Archivos fuente
set(SOURCES
    src/main.cpp
)

# Archivos de cabecera (para que aparezcan en el IDE)
set(HEADERS
    include/ListaSensor.h
    include/SensorBase.h
    include/SensorTemperatura.h
    include/SensorPresion.h
    include/ListaGeneral.h
    include/SerialReader.h
)

# Crear el ejecutable
add_executable(SistemaIoTSensores ${SOURCES} ${HEADERS})

# Configuración específica de Windows para comunicación serial
if(WIN32)
    target_compile_definitions(SistemaIoTSensores PRIVATE _WIN32)
endif()

# Mensaje de información
message(STATUS "Sistema IoT de Sensores - Configuración CMake")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Estándar C++: ${CMAKE_CXX_STANDARD}")

# Instalar el ejecutable
install(TARGETS SistemaIoTSensores DESTINATION bin)

# Target personalizado para generar documentación con Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Configurar Doxygen
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
    # Si existe Doxyfile.in, configurarlo
    if(EXISTS ${DOXYGEN_IN})
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message(STATUS "Doxygen configurado")
    endif()
    
    # Target para generar documentación
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generando documentación con Doxygen"
        VERBATIM
    )
    
    message(STATUS "Target 'docs' disponible para generar documentación")
else()
    message(WARNING "Doxygen no encontrado. La documentación no se generará.")
endif()

# Información de build
message(STATUS "==========================================")
message(STATUS "Para compilar el proyecto:")
message(STATUS "  mkdir build")
message(STATUS "  cd build")
message(STATUS "  cmake ..")
message(STATUS "  cmake --build .")
message(STATUS "==========================================")
message(STATUS "Para generar documentación:")
message(STATUS "  cmake --build . --target docs")
message(STATUS "==========================================")
