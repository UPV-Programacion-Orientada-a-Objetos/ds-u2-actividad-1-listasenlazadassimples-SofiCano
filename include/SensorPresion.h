#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"
#include <iostream>
#include <iomanip>

// Sensor de presion con lecturas int
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial;
    
public:
    SensorPresion(const char* id) : SensorBase(id) {
        std::cout << "[Log] Sensor de Presión '" << nombre << "' creado." << std::endl;
    }
    
    ~SensorPresion() {
        std::cout << "  [Destructor Sensor " << nombre << "] Tipo: Presion" << std::endl;
    }
    
    void registrarLectura(int valor) {
        historial.insertarAlFinal(valor);
        std::cout << "[Log] Lectura registrada en " << nombre << ": " << valor << " Pa" << std::endl;
    }
    
    // Procesa las lecturas: calcula el promedio
    void procesarLectura() override {
        std::cout << "-> Procesando Sensor " << nombre << "..." << std::endl;
        
        if (historial.estaVacia()) {
            std::cout << "[Sensor Presion] No hay lecturas para procesar." << std::endl;
            return;
        }
        
        int promedio = historial.calcularPromedio();
        int cantidad = historial.obtenerTamano();
        
        std::cout << "[" << nombre << "] (Presion): Promedio de lecturas: " 
                  << std::fixed << std::setprecision(1) << (float)promedio 
                  << " (" << cantidad << " lecturas)." << std::endl;
    }
    
    void imprimirInfo() const override {
        std::cout << "\n--- Información del Sensor ---" << std::endl;
        std::cout << "  ID: " << nombre << std::endl;
        std::cout << "  Tipo: Presión (int)" << std::endl;
        std::cout << "  Lecturas almacenadas: " << historial.obtenerTamano() << std::endl;
        
        if (!historial.estaVacia()) {
            historial.imprimir();
        }
    }
};

#endif // SENSOR_PRESION_H
