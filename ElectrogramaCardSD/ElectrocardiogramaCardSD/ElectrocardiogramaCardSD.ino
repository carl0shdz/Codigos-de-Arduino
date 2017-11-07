//Inicia las librerias
#include <SPI.h>
#include <SD.h>

//Selecciona el chipSelect
const int chipSelect = 8;

//Variables para guardar el Delta de tiempo
unsigned long ValorI = 0;
unsigned long ValorF = 0;
//Variable para calcular el periodo de los latidos
float Periodo = 0;
//Banderas Booleanas
boolean Estado = false;
boolean EstadoBoton = false;
//Boton y su lectura
int Boton = 5;
int LecturaBoton = 0;

int Contador = 0;

void setup() {
  //Declara el pin de Boton como entrada
  pinMode(Boton, INPUT);
  //Inicia la Comunicación Serial
  Serial.begin(9600);
  while (!Serial) {}
  //Mensaje de inicialización
  Serial.println("Inicialización de tarjeta SD...\n");
  //ChipSelect predeterminado configurado como salida aunque no se utilice
  pinMode(10, OUTPUT);
  //Chip Select Como salida
  pinMode(chipSelect, OUTPUT);
  // Verifica si existe memoria SD, sino retorna al inicio del codigo
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  //Mensaje de inicialización de la SD card completado
  Serial.println("card initialized.");
  //Configuración para detección de derivaciones LO +
  pinMode(2, INPUT);
  //Configuración para detección de derivaciones LO -
  pinMode(3, INPUT);
  //Inicia el contador interno de arduino a contar en mili segundos
  millis();
}

void loop() {
  //Configuración de boton para captura de frecuencia cardiaca
  LecturaBoton = digitalRead(Boton);
  if (LecturaBoton == 1) {
    EstadoBoton = true;
    do {
      LecturaBoton = digitalRead(Boton);
    } while (LecturaBoton == 1);
  }


  if ((digitalRead(2) == 1) || (digitalRead(3) == 1)) {       //Verifica si existe señal cardiaca
    //Serial.println("!");                                      //Si no existe señal cardiaca envia un dato constante
  }
  else {
    if  (analogRead(A0) > 600 &&  Estado == false) {          //Cuando se da la onda Q por primera ves captura el tiempo relativo
      Estado = true;
      ValorI = millis();
    }
    if (analogRead(A0) > 600 &&  Estado == true) {            //Cuando se da la onda Q por segunda ves captura el tiempo relativo
      Estado = false;
      ValorF = millis();
      Periodo = ValorF - ValorI;                              //Calcula el periodo de un latido

      if (Periodo != 0 && EstadoBoton == true) {             //Si se presiono el boton y tambien hay Periodo de la señal cardiaca disponible que entre al if
        EstadoBoton = false;
        Contador++;                                          //Aumenta el contador de los ID de los pacientes

        String dataString = "Id: ";                          //Se forma la cadena que se pretende escribir en la memoria SD
        dataString += String(Contador);
        dataString += (" Frecuencia: ");
        dataString += String(1 / Periodo);
        dataString += ("Hz");
        File datoFile = SD.open("dat.txt", FILE_WRITE);     //Se crea o abre el archivo dat.TXT para escritura dentro de la SD card
        if (datoFile) {                                     //Verifica si el objeto datoFile es verdadero lo que indica si exite el archivo
          //Serial.println(dataString);
          datoFile.println(dataString);                     //Escribe la cadena en la SD
          datoFile.close();
        }
        else {
          //Serial.println("error opening dataheart.txt");
        }
      }
    }
    Serial.println(analogRead(A0));
  }
  delay(10);
}
