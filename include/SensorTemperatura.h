#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"
#include <iostream>
#include <iomanip>

// Sensor de temperatura con lecturas float
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;
    
public:
    SensorTemperatura(const char* id) : SensorBase(id) {
        std::cout << "[Log] Sensor de Temperatura '" << nombre << "' creado." << std::endl;
    }
    
    ~SensorTemperatura() {
        std::cout << "  [Destructor Sensor " << nombre << "] Tipo: Temperatura" << std::endl;
    }
    
    void registrarLectura(float valor) {
        historial.insertarAlFinal(valor);
        std::cout << "[Log] Lectura registrada en " << nombre << ": " << valor << "°C" << std::endl;
    }
    
    // Procesa las lecturas: elimina la minima y calcula promedio
    void procesarLectura() override {
        std::cout << "-> Procesando Sensor " << nombre << "..." << std::endl;
        
        if (historial.estaVacia()) {
            std::cout << "[Sensor Temp] No hay lecturas para procesar." << std::endl;
            return;
        }
        
        if (historial.obtenerTamano() == 1) {
            float promedio = historial.calcularPromedio();
            std::cout << "[Sensor Temp] Promedio calculado sobre 1 lectura (" 
                      << std::fixed << std::setprecision(1) << promedio << ")." << std::endl;
        } else {
            float minimo = historial.eliminarMinimo();
            float promedio = historial.calcularPromedio();
            
            std::cout << "[" << nombre << "] (Temperatura): Lectura más baja (" 
                      << std::fixed << std::setprecision(1) << minimo 
                      << ") eliminada. Promedio restante: " 
                      << promedio << "." << std::endl;
        }
    }
    
    void imprimirInfo() const override {
        std::cout << "\n--- Información del Sensor ---" << std::endl;
        std::cout << "  ID: " << nombre << std::endl;
        std::cout << "  Tipo: Temperatura (float)" << std::endl;
        std::cout << "  Lecturas almacenadas: " << historial.obtenerTamano() << std::endl;
        
        if (!historial.estaVacia()) {
            historial.imprimir();
        }
    }
};

#endif // SENSOR_TEMPERATURA_H
