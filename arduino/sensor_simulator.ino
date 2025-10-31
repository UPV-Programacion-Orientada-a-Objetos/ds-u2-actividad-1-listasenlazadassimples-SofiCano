// Simulador de sensores para Arduino
// Este codigo debe compilarse y cargarse en Arduino IDE, no en VSCode

const unsigned long INTERVALO_ENVIO = 2000;

unsigned long tiempoAnterior = 0;

const char* sensorTemperatura1 = "T-001";
const char* sensorTemperatura2 = "T-002";
const char* sensorPresion1 = "P-105";
const char* sensorPresion2 = "P-106";

int contador = 0;

void setup() {
    Serial.begin(9600);
    
    while (!Serial) {
    ;
    }
    
    Serial.println("INICIO,SISTEMA,SENSORES_IOT");
    delay(500);
    randomSeed(analogRead(0));
}

void loop() {
    unsigned long tiempoActual = millis();
    
    if (tiempoActual - tiempoAnterior >= INTERVALO_ENVIO) {
    tiempoAnterior = tiempoActual;
    contador++;
    
    float temp1 = 20.0 + random(0, 300) / 10.0;
    Serial.print("TEMP,");
    Serial.print(sensorTemperatura1);
    Serial.print(",");
    Serial.println(temp1);
    delay(100);
    
    float temp2 = 15.0 + random(0, 300) / 10.0;
    Serial.print("TEMP,");
    Serial.print(sensorTemperatura2);
    Serial.print(",");
    Serial.println(temp2);
    delay(100);
    
    int pres1 = 70 + random(0, 40);
    Serial.print("PRES,");
    Serial.print(sensorPresion1);
    Serial.print(",");
    Serial.println(pres1);
    delay(100);
    
    int pres2 = 80 + random(0, 40);
    Serial.print("PRES,");
    Serial.print(sensorPresion2);
    Serial.print(",");
    Serial.println(pres2);
    delay(100);
    
    if (contador % 10 == 0) {
        Serial.print("INFO,SISTEMA,CICLOS_");
        Serial.println(contador);
    }
}
