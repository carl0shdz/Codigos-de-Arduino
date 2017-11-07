import processing.serial.*;

Serial puerto;

int EjeAnterior = 0;
int Eje = 0;
int Valor = 0;
int i = 10;
void setup () {
  size(1100, 600);
  background(255);
  String NombrePuerto = "/dev/ttyUSB0";
  println(NombrePuerto);
  puerto = new Serial(this, NombrePuerto, 9600);
  fill(170, 0, 4);
  rect(10, 200, 600, 300);
  textSize(30);
  text("ELectrocardiograma", 400, 80);
}

void draw () {
  if (puerto.available() > 0) {
    String texto = puerto.readStringUntil('\n');
    if (texto != null) {
      Valor = int(trim(texto));
    }
    Eje = int(map(Valor, 0, 1023, 500, 200));
    line(i, EjeAnterior, i+1, Eje);
    EjeAnterior = Eje;
    i++;
    if (i == 609) {
      i = 10;
      background(255);
      fill(170, 0, 4);
      rect(10, 200, 600, 300);
      textSize(30);
      text("Electrocardiograma", 400, 80);
    }
  }
  delay(10);
}