#include<Bridge.h>
#include<YunServer.h>
#include<YunClient.h>

YunServer server;

int led = 2;
int lectura = 0;
int url = 0;
float vol = 0.0;
int decimal = 0;

void setup() {
  pinMode(led,OUTPUT);
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  YunClient client = server.accept();
  lectura = analogRead(A5);
  vol = map(lectura,0,1023,0,500);
  decimal = int(vol);
  if(client)                                      //http://arduino.local/arduino/
  {
    String comando = client.readStringUntil('/');
    if(comando == "analogYun")                    //http://arduino.local/arduino/analogYun
    {
      url = client.parseInt();
      if(url == 5)                                //http://arduino.local/arduino/analogYun/5
      {
        client.print("el voltaje es: ");
        client.print(int(vol/100));
        client.print(".");
        client.print(decimal%100);
        client.print("V");
      }
    }
    client.stop();
  }
  delay(50);
}
