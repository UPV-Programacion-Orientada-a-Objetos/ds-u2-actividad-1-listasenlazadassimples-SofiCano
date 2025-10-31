#ifndef LISTA_GENERAL_H
#define LISTA_GENERAL_H

#include "SensorBase.h"
#include <iostream>

// Nodo para la lista polimorfica
struct NodoSensor {
    SensorBase* sensor;
    NodoSensor* siguiente;
    
    NodoSensor(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

// Lista enlazada para gestion polimorfica de sensores
class ListaGeneral {
private:
    NodoSensor* cabeza;
    int cantidad;
    
public:
    ListaGeneral() : cabeza(nullptr), cantidad(0) {}
    
    ~ListaGeneral() {
        std::cout << "\n--- Liberación de Memoria en Cascada ---" << std::endl;
        
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            NodoSensor* siguiente = actual->siguiente;
            
            delete actual->sensor;
            delete actual;
            
            actual = siguiente;
        }
        
        std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
    }
    
    void insertarSensor(SensorBase* sensor) {
        NodoSensor* nuevoNodo = new NodoSensor(sensor);
        
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            NodoSensor* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        
        cantidad++;
        std::cout << "[Log] Sensor insertado en lista de gestión: " 
                  << sensor->obtenerNombre() << std::endl;
    }
    
    SensorBase* buscarSensor(const char* nombre) const {
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            if (strcmp(actual->sensor->obtenerNombre(), nombre) == 0) {
                return actual->sensor;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
    
    // Ejecuta procesamiento polimórfico de todos los sensores
    void procesarTodosSensores() {
        if (cabeza == nullptr) {
            std::cout << "[Advertencia] No hay sensores registrados." << std::endl;
            return;
        }
        
        std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;
        
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->procesarLectura();
            actual = actual->siguiente;
        }
    }
    
    void imprimirTodosSensores() const {
        if (cabeza == nullptr) {
            std::cout << "[Advertencia] No hay sensores registrados." << std::endl;
            return;
        }
        
        std::cout << "\n--- Lista de Sensores Registrados ---" << std::endl;
        
        NodoSensor* actual = cabeza;
        int contador = 1;
        while (actual != nullptr) {
            std::cout << "\n" << contador << ". ";
            actual->sensor->imprimirInfo();
            actual = actual->siguiente;
            contador++;
        }
    }
    
    int obtenerCantidad() const {
        return cantidad;
    }
    
    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

#endif // LISTA_GENERAL_H
