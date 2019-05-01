#include <ESP8266WiFi.h>
const char* ssid = "WIFI Şifresi";
const char* password = "Parola";
String str1,newstr;
int i=0;
int oto = HIGH;
int sicak = LOW;
int soguk = LOW;
int sulama = LOW;
int cati = LOW;

// http server oluşturuyoruz
WiFiServer server(80);

int val;
void setup() {
  Serial.begin(9600);
  delay(10);
  
  // Wifiye bağlanıyoruz
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Server başlıyor
  server.begin();
  Serial.println("Server started");

  // IP adresi yazırılıyor
  Serial.println(WiFi.localIP());
}

void loop() {
  String str;
  //Arduino'dan gelen bilgileri okuyoruz 
 newstr = Serial.readStringUntil('\n');
 //Eğer gelen varsa str1 değişkeninde akyarıyoruz.
  if (newstr.length()>0) {
	  //Gelen değerin sonundaki alt satır kodunu çıkartıyoruz.
      str1 = newstr.substring(0,newstr.length()-1);
  }
  //$0|1|1|1|0-192.168.1.5 şeklinde değer gönderiyoruz.
  str="$"+String(oto)+"|"+String(sicak)+"|"+String(soguk)+"|"+String(sulama)+"|"+String(cati)+"-"+WiFi.localIP().toString();
Serial.println(str);
  //$0|1|1|1|0-192.168.1.5


  
// Herhangi birinin bağlanıp bağanmadığını kontrol ediyoruz.
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
// İstemciden veri gelene kadar bekliyoruz.
  while(!client.available()){
    delay(1);
  }
  
// İstemciden gelen ilk satırı okuyoruz.
  String req = client.readStringUntil('\r');

  client.flush();
//gelen değerde eğer '?id=oto' ifadesi varsa otomatiği kapatıyor ya da açıyor.
  if (req.indexOf("/?id=oto") != -1)
  {
    oto=!oto;
  }
  else if (req.indexOf("/?id=sicak") != -1)
  {
    sicak=!sicak;
  }else if (req.indexOf("/?id=soguk") != -1)
  {
    soguk=!soguk;
  }else if (req.indexOf("/?id=cati") != -1)
  {
    cati=!cati;
  }else if (req.indexOf("/?id=sulama") != -1)
  {
    sulama=!sulama;
  }
  
  digitalWrite(2, val);
  
  client.flush();
  
//Json değerlerini Server'a yazdırıyoruz.
String Content = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{\"gelen\":\""+String(str1)+"\",\"otomatik\":\""+ String(oto)+"\",\"sicakhava\":\""+ String(sicak)+"\",\"sogukhava\":\""+ String(soguk)+"\",\"sulama\":\""+ String(sulama)+"\",\"cati\":\""+ String(cati)+"\"}\r\n\r\n";

// Server'a bilgileri yazdırıyoruz
  client.print(Content);
  delay(1);
  Serial.println("Client disonnected");
}
