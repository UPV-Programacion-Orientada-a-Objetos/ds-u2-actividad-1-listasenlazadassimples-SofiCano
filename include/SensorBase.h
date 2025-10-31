#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <iostream>
#include <cstring>

// Clase base abstracta para todos los sensores
class SensorBase {
protected:
    char nombre[50];
    
public:
    SensorBase(const char* id) {
        strncpy(nombre, id, 49);
        nombre[49] = '\0';
    }
    
    // Destructor virtual para polimorfismo
    virtual ~SensorBase() {
        std::cout << "[Destructor General] Liberando Sensor: " << nombre << std::endl;
    }
    
    // Metodos virtuales puros
    virtual void procesarLectura() = 0;
    virtual void imprimirInfo() const = 0;
    
    const char* obtenerNombre() const {
        return nombre;
    }
};

#endif // SENSOR_BASE_H
