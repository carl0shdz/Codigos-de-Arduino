#include <LiquidCrystal.h>
#include <Keypad.h>             //Incluir la Libreria de la Keypad
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
const byte Filas = 4;          //KeyPad de 4 filas
const byte Cols = 4;           //y 4 columnas
byte Pins_Filas[] = {9, 8, 7, 6};     //Pines Arduino para las filas
byte Pins_Cols[] = { 5, 4, 3, 2};     // Pines Arduinopara las columnas
char Teclas [ Filas ][ Cols ] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//Declaración de variables enteras
int punto = 0;
int i = 1;
float j = 1;
int p = 0;
int d = 0;
int x = 0;
int y = 0;
int accion = 0;
int pulso = 0;
//Declaración de variables flotantes
float Entero1[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float Decimal1[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float numero1 = 0.00000;
float numero2 = 0.00000;
int QueQuiere = 0;
float ope1 = 0.0;
float ope2 = 0.0;
float resultado = 0;
//Declaración de Procesos
void IntroNumero();
void Signo();
//Declaración de objetos
Keypad Teclado = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

void setup() {
  Serial.begin(9600);     //inicia el monitor Serial
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  pulso = Teclado.getKey();
  switch (accion) {
    case 0:
      IntroNumero();
      break;
    case 1:
      IntroNumero();
      break;
    case 2:
      Signo();
      break;
    default:
      accion = 0;
      break;
  }
}
void IntroNumero() {
  if (pulso == 42) {
    lcd.setCursor(x, 0);
    lcd.print(".");
    x++;
    punto = 1;
  }
  if (pulso != 0 && (pulso - 48) < 10 && (pulso - 48) >= 0 && punto == 0) {
    Entero1[p] = (pulso - 48);
    lcd.setCursor(x, 0);
    lcd.print(pulso - 48);
    x++;
    Serial.println(p);
    Serial.println(Entero1[p]);
    p++;
  }
  if (pulso != 0 && (pulso - 48) < 10 && (pulso - 48) >= 0 && punto == 1) {
    Decimal1[d] = (pulso - 48);
    lcd.setCursor(x, 0);
    lcd.print(pulso - 48);
    x++;
    Serial.println(d);
    Serial.println(Decimal1[d]);
    d++;
  }
  if ((pulso != 0 && (pulso - 48) < 21 && (pulso - 48) > 16 && punto == 1 && accion == 0) || (pulso != 0 && pulso == 35 && punto == 1 && accion == 1)) {
    if (accion == 0) {
      if (pulso == 65) {
        QueQuiere = 1;
        lcd.setCursor(x, 0);
        lcd.print("+");
        x++;
      }
      else if (pulso == 66) {
        QueQuiere = 2;
        lcd.setCursor(x, 0);
        lcd.print("-");
        x++;
      }
      else if (pulso == 67) {
        QueQuiere = 3;
        lcd.setCursor(x, 0);
        lcd.print("x");
        x++;
      }
      else if (pulso == 68) {
        QueQuiere = 4;
        lcd.setCursor(x, 0);
        lcd.print("/");
        x++;
      }
    }
    punto = 2;
    do {
      p--;
      numero1 = numero1 + (Entero1[p] * i);
      i = i * 10;
    } while (p > 0);
    i = 1;
    do {
      d--;
      numero2 = numero2 + (Decimal1[d] * j);
      j = j * 10;
    } while (d > 0);
    numero2 = numero2 / j;
    Serial.println(numero2);
    j = 1;
    p = 0;
    d = 0;
  }
  if (punto == 2 && accion == 0) {
    ope1 = numero1 + numero2;
    accion = 1;
    numero1 = 0;
    numero2 = 0;
    punto = 0;
    Serial.println("primero");
    Serial.println(ope1);
  }
  else if (punto == 2 && accion == 1) {
    ope2 = numero1 + numero2;
    accion = 2;
    numero1 = 0;
    numero2 = 0;
    punto = 0;
    Serial.println("segundo");
    Serial.println(ope2);
  }
}
void Signo() {
  switch (QueQuiere) {
    case 1:
      resultado = (ope1 + ope2);
      break;
    case 2:
      resultado = (ope1 - ope2);
      break;
    case 3:
      resultado = (ope1 * ope2);
      break;
    case 4:
      resultado = (ope1 / ope2);
      break;
    default:
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print(resultado);
  delay(5000);
  lcd.clear();
  x = 0;
  accion = 0;
}
