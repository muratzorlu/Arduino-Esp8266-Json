//Arduino kodları
#include <SoftwareSerial.h>
int i=0;
String header;
//Arduino 2(RX) ve 3(TX) pinleri ESP8266 ile haberleşecek
SoftwareSerial esp(2, 3); 
char gelen[7];
void setup()
{
Serial.begin(9600);
Serial.println("Begin");
esp.begin(9600);
pinMode(8, OUTPUT);
}
void loop()
{
//Arduino ile eps8266 seri portttan haberleşiyorlar.
if (esp.available())
{

  header=esp.readStringUntil('\n');
  //Esp8266'dan gelen veriyi kontrol ediyoruz
  if(header.substring(10,11)=="-")
  {
  Serial.println(header.substring(0,10)+'-'+header.substring(11,header.length()));
   ////$0|1|1|1|0-192.168.1.5 şeklinde gelen değerden veri alıyoruz
  gelen[0]=header.charAt(1);
  gelen[1]=header.charAt(3);
  gelen[2]=header.charAt(5);
  gelen[3]=header.charAt(7);
  gelen[4]=header.charAt(9);
  header="";
  }
//25|65|256|100|658| şeklinde Esp8266 ya değer gönderiyoruz. sicaklik|nem|topraknem|servo|ldr
esp.println("25|65|256|100|658");

//Düzelttiğimiz verilere göre ledleri yakıp söndürüyoruz.
if(gelen[0]=='1') digitalWrite(7, HIGH); else digitalWrite(7, LOW);
if(gelen[1]=='1') digitalWrite(8, HIGH); else digitalWrite(8, LOW);
if(gelen[2]=='1') digitalWrite(9, HIGH); else digitalWrite(9, LOW);
if(gelen[3]=='1') digitalWrite(10, HIGH); else digitalWrite(10, LOW);
if(gelen[4]=='1') digitalWrite(11, HIGH); else digitalWrite(11, LOW);
}
}
