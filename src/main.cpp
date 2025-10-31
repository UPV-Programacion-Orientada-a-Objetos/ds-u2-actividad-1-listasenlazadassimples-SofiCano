#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ListaGeneral.h"
#include "SerialReader.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "  Sistema IoT de Monitoreo Polimórfico" << endl;
    cout << "========================================" << endl;
    cout << "1. Crear Sensor de Temperatura" << endl;
    cout << "2. Crear Sensor de Presión" << endl;
    cout << "3. Registrar Lectura Manual" << endl;
    cout << "4. Iniciar Captura desde Arduino" << endl;
    cout << "5. Ejecutar Procesamiento Polimórfico" << endl;
    cout << "6. Mostrar Información de Sensores" << endl;
    cout << "7. Salir (Liberar Memoria)" << endl;
    cout << "========================================" << endl;
    cout << "Opción: ";
}

bool parsearLineaArduino(const char* linea, char* tipo, char* id, float& valor) {
    char lineaCopia[100];
    strncpy(lineaCopia, linea, 99);
    lineaCopia[99] = '\0';
    
    char* token = strtok(lineaCopia, ",");
    if (token == nullptr) return false;
    strcpy(tipo, token);
    
    token = strtok(nullptr, ",");
    if (token == nullptr) return false;
    strcpy(id, token);
    
    token = strtok(nullptr, ",");
    if (token == nullptr) return false;
    valor = atof(token);
    
    return true;
}

int main() {
    ListaGeneral listaGestion;
    SerialReader serial;
    
    cout << "==================================================" << endl;
    cout << "  SISTEMA DE GESTIÓN POLIMÓRFICA DE SENSORES IoT" << endl;
    cout << "==================================================" << endl;
    cout << "  Universidad: POLITÉCNICA" << endl;
    cout << "  Materia: Estructura de Datos" << endl;
    cout << "  Estudiante: Sofia Cano" << endl;
    cout << "==================================================" << endl;
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                cout << "\n--- Crear Sensor de Temperatura ---" << endl;
                cout << "Ingrese ID del sensor (ej: T-001): ";
                char id[50];
                cin.getline(id, 50);
                
                SensorTemperatura* nuevoTemp = new SensorTemperatura(id);
                listaGestion.insertarSensor(nuevoTemp);
                cout << "[OK] Sensor de temperatura creado e insertado." << endl;
                break;
            }
            
            case 2: {
                cout << "\n--- Crear Sensor de Presión ---" << endl;
                cout << "Ingrese ID del sensor (ej: P-105): ";
                char id[50];
                cin.getline(id, 50);
                
                SensorPresion* nuevoPres = new SensorPresion(id);
                listaGestion.insertarSensor(nuevoPres);
                cout << "[OK] Sensor de presión creado e insertado." << endl;
                break;
            }
            
            case 3: {
                cout << "\n--- Registrar Lectura Manual ---" << endl;
                
                if (listaGestion.estaVacia()) {
                    cout << "[Advertencia] Primero debe crear sensores." << endl;
                    break;
                }
                
                cout << "Ingrese ID del sensor: ";
                char id[50];
                cin.getline(id, 50);
                
                SensorBase* sensor = listaGestion.buscarSensor(id);
                if (sensor == nullptr) {
                    cout << "[Error] Sensor no encontrado." << endl;
                    break;
                }
                
                SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
                if (sensorTemp != nullptr) {
                    cout << "Ingrese valor de temperatura (float): ";
                    float valor;
                    cin >> valor;
                    cin.ignore();
                    sensorTemp->registrarLectura(valor);
                } else {
                    SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
                    if (sensorPres != nullptr) {
                        cout << "Ingrese valor de presión (int): ";
                        int valor;
                        cin >> valor;
                        cin.ignore();
                        sensorPres->registrarLectura(valor);
                    }
                }
                break;
            }
            
            case 4: {
                cout << "\n--- Captura desde Arduino ---" << endl;
                cout << "Ingrese el puerto COM (ej: COM3): ";
                char puerto[10];
                cin.getline(puerto, 10);
                
                if (serial.conectar(puerto)) {
                    cout << "[Info] Esperando datos del Arduino..." << endl;
                    cout << "[Info] Presione Ctrl+C para detener la captura" << endl;
                    cout << "[Info] (Simulación: capturará hasta 10 lecturas)" << endl;
                    
                    int lecturas = 0;
                    const int MAX_LECTURAS = 10;
                    
                    while (lecturas < MAX_LECTURAS && serial.estaConectado()) {
                        char buffer[100];
                        if (serial.leerLinea(buffer, 100)) {
                            cout << "[Arduino] Recibido: " << buffer << endl;
                            
                            char tipo[10], id[50];
                            float valor;
                            
                            if (parsearLineaArduino(buffer, tipo, id, valor)) {
                                // Buscar si el sensor ya existe
                                SensorBase* sensor = listaGestion.buscarSensor(id);
                                
                                if (strcmp(tipo, "TEMP") == 0) {
                                    if (sensor == nullptr) {
                                        SensorTemperatura* nuevoTemp = new SensorTemperatura(id);
                                        listaGestion.insertarSensor(nuevoTemp);
                                        nuevoTemp->registrarLectura(valor);
                                    } else {
                                        SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
                                        if (sensorTemp) sensorTemp->registrarLectura(valor);
                                    }
                                } else if (strcmp(tipo, "PRES") == 0) {
                                    if (sensor == nullptr) {
                                        SensorPresion* nuevoPres = new SensorPresion(id);
                                        listaGestion.insertarSensor(nuevoPres);
                                        nuevoPres->registrarLectura((int)valor);
                                    } else {
                                        SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
                                        if (sensorPres) sensorPres->registrarLectura((int)valor);
                                    }
                                }
                                
                                lecturas++;
                            }
                        }
                    }
                    
                    serial.cerrar();
                    cout << "[Info] Captura finalizada. Total lecturas: " << lecturas << endl;
                } else {
                    cout << "[Error] No se pudo conectar al Arduino." << endl;
                }
                break;
            }
            
            case 5: {
                cout << "\n--- Opción 4: Ejecutar Procesamiento Polimórfico ---" << endl;
                listaGestion.procesarTodosSensores();
                break;
            }
            
            case 6: {
                listaGestion.imprimirTodosSensores();
                break;
            }
            
            case 7: {
                cout << "\n--- Opción 5: Cerrar Sistema (Liberar Memoria) ---" << endl;
                continuar = false;
                break;
            }
            
            default:
                cout << "[Error] Opción no válida." << endl;
                break;
        }
    }
    
    return 0;
}
