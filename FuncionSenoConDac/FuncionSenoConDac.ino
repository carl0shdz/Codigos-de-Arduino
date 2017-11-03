#include <Wire.h>//Include the Wire library to talk I2C

#define MCP4725_ADDR 0x60

float angulo = 0.0;
float amplitud = 0.0;
int dato = 0;
int muestras = 20;                    //numero de muestras a graficar de la señal
boolean estado = true;
int regulador = 0;
void setup() {
  pinMode(5, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  estado = !estado;
  digitalWrite(5, estado);
  regulador = map(analogRead(A1), 0, 1023, 1, 100);
  amplitud = 2047 * sin(angulo) + 2047; //Calculo de la amplitud mas offset
  angulo = angulo + ((2 * PI) / muestras);  //aumentamos el angulo
  if (angulo >= 2 * PI) {             //verificamos que el angulo no se pase de 2 pi
    angulo = 0;                       //si lo hace que reinicie el valor del angulo
  }
  dato = int(amplitud);               //convierte el angulo de, decimal a flotante
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(dato >> 4);        // the 8 most significant bits...
  Wire.write((dato & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
  delay(regulador);
}
