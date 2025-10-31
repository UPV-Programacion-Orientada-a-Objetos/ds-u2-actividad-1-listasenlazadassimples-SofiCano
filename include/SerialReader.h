#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <cstring>

// Clase para comunicacion serial con Arduino
class SerialReader {
private:
#ifdef _WIN32
    HANDLE hSerial;
#endif
    bool conectado;
    
public:
    SerialReader() : conectado(false) {
#ifdef _WIN32
        hSerial = INVALID_HANDLE_VALUE;
#endif
    }
    
    ~SerialReader() {
        cerrar();
    }
    
    bool conectar(const char* puerto) {
#ifdef _WIN32
        char nombreCompleto[20];
        snprintf(nombreCompleto, sizeof(nombreCompleto), "\\\\.\\%s", puerto);
        
        hSerial = CreateFileA(
            nombreCompleto,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
        
        if (hSerial == INVALID_HANDLE_VALUE) {
            std::cerr << "[Error] No se pudo abrir el puerto " << puerto << std::endl;
            return false;
        }
        
        DCB dcbSerialParams = {0};
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        
        if (!GetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "[Error] No se pudo obtener el estado del puerto" << std::endl;
            CloseHandle(hSerial);
            return false;
        }
        
        // Configuracion: 9600 baudios, 8 bits, sin paridad, 1 bit de parada
        dcbSerialParams.BaudRate = CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;
        
        if (!SetCommState(hSerial, &dcbSerialParams)) {
            std::cerr << "[Error] No se pudo configurar el puerto" << std::endl;
            CloseHandle(hSerial);
            return false;
        }
        
        // Configurar timeouts
        COMMTIMEOUTS timeouts = {0};
        timeouts.ReadIntervalTimeout = 50;
        timeouts.ReadTotalTimeoutConstant = 50;
        timeouts.ReadTotalTimeoutMultiplier = 10;
        timeouts.WriteTotalTimeoutConstant = 50;
        timeouts.WriteTotalTimeoutMultiplier = 10;
        
        if (!SetCommTimeouts(hSerial, &timeouts)) {
            std::cerr << "[Error] No se pudieron configurar los timeouts" << std::endl;
            CloseHandle(hSerial);
            return false;
        }
        
        conectado = true;
        std::cout << "[OK] Conectado al puerto " << puerto << std::endl;
        
        Sleep(2000);
        
        return true;
#else
        std::cerr << "[Error] Comunicación serial solo disponible en Windows" << std::endl;
        return false;
#endif
    }
    
    bool leerLinea(char* buffer, int tamano) {
#ifdef _WIN32
        if (!conectado || hSerial == INVALID_HANDLE_VALUE) {
            return false;
        }
        
        DWORD bytesLeidos;
        char c;
        int indice = 0;
        
        while (indice < tamano - 1) {
            if (ReadFile(hSerial, &c, 1, &bytesLeidos, NULL) && bytesLeidos > 0) {
                if (c == '\n') {
                    buffer[indice] = '\0';
                    return indice > 0;
                }
                if (c != '\r') {
                    buffer[indice++] = c;
                }
            } else {
                break;
            }
        }
        
        buffer[indice] = '\0';
        return indice > 0;
#else
        return false;
#endif
    }
    
    void cerrar() {
#ifdef _WIN32
        if (conectado && hSerial != INVALID_HANDLE_VALUE) {
            CloseHandle(hSerial);
            std::cout << "[Info] Puerto serial cerrado" << std::endl;
        }
        conectado = false;
        hSerial = INVALID_HANDLE_VALUE;
#endif
    }
    
    bool estaConectado() const {
        return conectado;
    }
};

#endif // SERIAL_READER_H
