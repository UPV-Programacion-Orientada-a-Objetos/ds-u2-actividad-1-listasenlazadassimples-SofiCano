#ifndef LISTA_SENSOR_H
#define LISTA_SENSOR_H

#include <iostream>

// Nodo generico para la lista enlazada
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
    
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

// Lista enlazada simple generica
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;
    int tamano;
    
public:
    ListaSensor() : cabeza(nullptr), tamano(0) {}
    
    ~ListaSensor() {
        std::cout << "  [Destructor ListaSensor] Liberando Lista Interna..." << std::endl;
        liberarTodo();
    }
    
    // Constructor de copia
    ListaSensor(const ListaSensor<T>& otra) : cabeza(nullptr), tamano(0) {
        copiar(otra);
    }
    
    // Operador de asignacion
    ListaSensor<T>& operator=(const ListaSensor<T>& otra) {
        if (this != &otra) {
            liberarTodo();
            copiar(otra);
        }
        return *this;
    }
    
    void insertarAlFinal(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        
        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        
        tamano++;
        std::cout << "[Log] Insertando Nodo<" << typeid(T).name() << "> con valor: " << valor << std::endl;
    }
    
    bool buscar(T valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }
    
    T calcularPromedio() const {
        if (tamano == 0) return T(0);
        
        T suma = T(0);
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            suma += actual->dato;
            actual = actual->siguiente;
        }
        
        return suma / tamano;
    }
    
    T eliminarMinimo() {
        if (cabeza == nullptr) return T(0);
        
        Nodo<T>* actual = cabeza;
        Nodo<T>* minNodo = cabeza;
        Nodo<T>* prevMin = nullptr;
        Nodo<T>* prevActual = nullptr;
        
        while (actual != nullptr) {
            if (actual->dato < minNodo->dato) {
                minNodo = actual;
                prevMin = prevActual;
            }
            prevActual = actual;
            actual = actual->siguiente;
        }
        
        T valorMin = minNodo->dato;
        
        if (prevMin == nullptr) {
            cabeza = cabeza->siguiente;
        } else {
            prevMin->siguiente = minNodo->siguiente;
        }
        
        delete minNodo;
        tamano--;
        
        return valorMin;
    }
    
    int obtenerTamano() const {
        return tamano;
    }
    
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    void imprimir() const {
        Nodo<T>* actual = cabeza;
        std::cout << "    Lecturas: ";
        while (actual != nullptr) {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr) {
                std::cout << " -> ";
            }
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
    
private:
    void liberarTodo() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            std::cout << "    [Log] Nodo<" << typeid(T).name() << "> " << actual->dato << " liberado." << std::endl;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        tamano = 0;
    }
    
    void copiar(const ListaSensor<T>& otra) {
        if (otra.cabeza == nullptr) return;
        
        Nodo<T>* actualOtra = otra.cabeza;
        while (actualOtra != nullptr) {
            insertarAlFinal(actualOtra->dato);
            actualOtra = actualOtra->siguiente;
        }
    }
};

#endif // LISTA_SENSOR_H
